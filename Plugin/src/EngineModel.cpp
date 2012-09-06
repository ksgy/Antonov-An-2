#include "EngineModel.h"
#include <iostream>
#include <ctime>


EngineModel::EngineModel(){
	
	XPLMDebugString("An2 - EngineModel Constructor");

	XPlaneData = new XpData();

	cht 				= XPlaneData->amb();
	oiltemp				= XPlaneData->amb();
	targetCHT			= XPlaneData->amb();
	targetOilT			= XPlaneData->amb();
	nonNormalCounter 	= 1200; //4 * 60 * 5 = 1/flcb * sec * min

	XPlaneData->setCHT(cht);
    XPlaneData->setOilTemp(oiltemp);

	readData();
}

EngineModel::~EngineModel(){
	delete XPlaneData;
}

const float EngineModel::baseCHT 		= 120;
const float EngineModel::min_CHT 		= 120;
const float EngineModel::max_CHT 		= 245;
const float EngineModel::max_5min_rpm	= 230;


void EngineModel::run(){
	
	XPLMDebugString("An2 - EngineModel Run");

	readData();
	checkTemp();
	//debug();
	checkFail();
	setOilTemp();
}

void EngineModel::readData() {
	
	XPLMDebugString("An2 - EngineModel ReadData");

	amb		= XPlaneData->amb();
	cht 	= XPlaneData->cht();
	oiltemp = XPlaneData->oilTemp();
	running = XPlaneData->engRun();
	rpm		= XPlaneData->rpm();
	cowl	= XPlaneData->cowl();
	ias		= XPlaneData->ias();
	mpr		= XPlaneData->mpr();
	prop	= XPlaneData->prop();


}

void EngineModel::checkTemp() {
	
	XPLMDebugString("An2 - EngineModel CheckTemp");

	/*
	targetCHT =  baseCHT + rpm*2.5+ diffAMB/3 - cowl*80 - ias*0.12 - prop*5;
	var ch = (rpm/2+1)*0.02 + 1/(cowl+1)*0.2 + 1/(ias+1)*0.01 + amb*0.01;


	for(var i=0; i<$('#mins').val()*60;i++){

		if(cht<targetCHT) {
			if(cht>targetCHT*0.75 && cht<targetCHT*0.9)
				cht+=0.35*ch;
			else if(cht>targetCHT*0.9) {
				cht+=0.15*ch;
			} else {
				cht+=ch*0.8;
			}

		} else {
			if(targetCHT>cht*0.75 && targetCHT<cht*0.9)
				cht-=0.35*ch;
			else if(targetCHT>cht*0.9) {
				cht-=0.15*ch;
			} else {
				cht-=ch*0.8;
			}
		}

	*/


	float diffAMB = amb - 15;


	if (running == 1) {
		targetCHT = baseCHT + rpm*2.8+ diffAMB/3 - cowl*125 - ias*0.18 - prop/3;
	} else {
		targetCHT = amb ;
	}

	float ch = ((rpm/2.5)*0.02 + 1/(cowl+1)*0.2 + 1/(ias+1)*0.01 + amb*0.01)*0.17;

	if(cht<targetCHT) {
			if(cht>targetCHT*0.75 && cht<targetCHT*0.9)
				cht=cht+0.35*ch;
			else if(cht>targetCHT*0.9) {
				cht=cht+0.15*ch;
			} else {
				cht=cht+ch*0.8;
			}

		} else {
			if(targetCHT>cht*0.75 && targetCHT<cht*0.9)
				cht=cht-0.35*ch;
			else if(targetCHT>cht*0.9) {
				cht=cht-0.15*ch;
			} else {
				cht=cht-ch*0.8;
			}
		}


	XPlaneData->setCHT(cht);

}

void EngineModel::checkFail() {
	
	XPLMDebugString("An2 - EngineModel CheckFail");

	// Check if engine is not pre-heated
	if(running == 1) {
		if((cht < min_CHT-20 && XPlaneData->engRPM() > 135) || 		// 1300
		   (cht < min_CHT && XPlaneData->engRPM() > 168)) { 		// 1500
			failEngine(0); // seize;
		}
	}

	// If over max cht
	if(cht > max_CHT) {
		failEngine(1); // fire
	}

	// if using engine in non-normal way
	if(XPlaneData->engRPM() > max_5min_rpm || cht > max_CHT-45 || XPlaneData->mpr() >= 33) {
		if(nonNormalCounter > -20) {
			nonNormalCounter--;
		}
	} else if(nonNormalCounter < 1200) {
		nonNormalCounter++;
	}

	// If non-normal conditions over 5 mins
	if(nonNormalCounter <= 0) {
		failEngine(1); // fire
	}

	// after 4 mins start fuel problems
	if(nonNormalCounter <= 240) {
		failEngine(2); // fuel
	}

	// solve fuel problems
	if(nonNormalCounter > 240 && nonNormalCounter < 260) {
		repairEngine(2);
	}
}


void EngineModel::failEngine(int type) {
	switch (type) {

		case 0 : XPLMSetDatai(DR_ENGFAIL_SEIZE,6); break;
		case 1 : XPLMSetDatai(DR_ENGFAIL_FIRE,6); break;
		case 2 :
			XPLMSetDatai(DR_O_FF,1);
			float fuelFlow = 0.003;
			//fuelFlow = XPlaneData->Randf(0.003,0.0079);
			//XPLMSetDatavf(XPLMFindDataRef("sim/flightmodel/engine/ENGN_FF_"), &fuelFlow, 0, 1);
			XPLMSetDatavf(DR_FF, &fuelFlow, 0, 1);
			break;

	}
}

void EngineModel::repairEngine(int type) {
	switch (type) {

		case 0 : XPLMSetDatai(DR_ENGFAIL_SEIZE,0); break;
		case 1 : XPLMSetDatai(DR_ENGFAIL_FIRE,0); break;
		case 2 : XPLMSetDatai(DR_O_FF,0); break;

	}
}

void EngineModel::setOilTemp() {

	if(running == 1) {

		if(cht < 30) {
			targetOilT = cht;
		}

		if(cht > 30 && cht < 120) {
			targetOilT = 50+20-XPlaneData->carb()*40;
		}

		if(cht > 120 && cht < 150) {
			targetOilT = 60+30-XPlaneData->carb()*50;
		}

		if(cht > 150 && cht < 215) {
			targetOilT = 75+30-XPlaneData->carb()*40;
		}

		if(cht > 215 && cht < 245) {
			targetOilT = 85+20-XPlaneData->carb()*40;
		}

		if(cht > 245) {
			targetOilT = 100+30-XPlaneData->carb()*30;
		}


	} else {
		targetOilT = amb;
	}

	if(oiltemp < targetOilT) {
		oiltemp += ((targetOilT - oiltemp)/200)*0.5;
	} else {
		oiltemp -= ((oiltemp - targetOilT)/2500)*0.5;
	}


	XPlaneData->setOilTemp(oiltemp);


}


void EngineModel::debug(){

	using namespace std;
	//float _ff;

	cout << "\n\n\nTCHT:\t "    << targetCHT;
	cout << "\nCCHT:\t "    << cht;
	cout << "\nRPM:\t "     << rpm;
    cout << "\nERPM:\t "    << XPlaneData->engRPM();
    cout << "\nAMB:\t "     << amb;
    cout << "\nRUN:\t "     << running;
    cout << "\nCWL:\t "     << cowl;
    cout << "\nIAS:\t "     << ias;
    cout << "\nMPR:\t "     << mpr;
    cout << "\nNNC:\t "     << nonNormalCounter;
    cout << "\nAPU:\t "     << XPlaneData->apuSW();
    cout << "\nOIL:\t "    << XPlaneData->oilTemp();
    cout << "\nTOIL:\t "    << targetOilT;
    //XPLMGetDatavf(XPLMFindDataRef("sim/cockpit2/engine/indicators/fuel_flow_kg_sec"), &_ff, 0, 1);
    //cout << "\nFF:\t "     << _ff;
    cout << "\nGyro:\t "     << XPlaneData->getGyro().pitch << "\t\t" << XPlaneData->getGyro().roll;
    cout << "\nGyroO:\t "     << XPlaneData->getOrigGyro().pitch << "\t\t" << XPlaneData->getOrigGyro().roll;
    cout << "\n\n";

}


bool EngineModel::paused(){
    return XPlaneData->paused();
}



/*void EngineModel::setProperties(){
	float amb = XPLMGetDataf(ds_ambtemp);
	float rpm[MAX_NUMBER_ENGINES];
	float cowl[MAX_NUMBER_ENGINES];
	float ias = XPLMGetDataf(ds_IAS) * 1.852;
	const float baseCHT = 120.0;
	const float diffAMB = amb - 15;

	XPLMSetDatavf(ds_RPM, rpm, 0, MAX_NUMBER_ENGINES);
	XPLMGetDatavf(ds_Cowl, cowl, 0, MAX_NUMBER_ENGINES);
}*/
