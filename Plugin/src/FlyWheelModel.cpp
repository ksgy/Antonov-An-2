/*
 * FlyWheel.cpp
 *
 *  Created on: 2009.09.26.
 *      Author: ksgy
 */

#include "FlyWheelModel.h"

FlyWheelModel::FlyWheelModel() {
	
	XPLMDebugString("An2 - FlywheelModel Construct");
	
	
	XPlaneData = new XpData();
	apu_RPM = 0;
	smoke = true;
	XPLMCommandKeyStroke(xplm_key_smoke);
}

FlyWheelModel::~FlyWheelModel() {
	delete XPlaneData;
}

void FlyWheelModel::run() {
	
	XPLMDebugString("An2 - FlywheelModel Run");
	

	switch (XPlaneData->apuSW()) {
			case 0 :
				// spin down the apu
				apu_RPM=apu_RPM-1.5;

				// if apu is down, release the eng starter - if spinned up more the more chance gave to start the engine
				if( apu_RPM<0 ) {
					apu_RPM = 0;
					XPLMCommandButtonRelease(xplm_joy_start_0);
				}

				// start
				if( apu_RPM > 0 && XPlaneData->engRun() == 0 && XPlaneData->engRPM() < 10  ) {
					XPLMCommandButtonPress(xplm_joy_start_0); // press start button if apu is spinned up
				}

				// if rpm high enough
				if( XPlaneData->engRPM() > 35 ) // rmp: 780
				apu_RPM = -1;
				break;

			case 2:
				apu_RPM++;
				break;
	}

	if(apu_RPM == 0) {
		XPLMSetDatai(XPLMFindDataRef("sim/operation/failures/rel_startr0"),6);
	} else {
		XPLMSetDatai(XPLMFindDataRef("sim/operation/failures/rel_startr0"),0);
	}


	/* smoke off */
	if(XPlaneData->rpm() > 30 && smoke==true ) {
		smoke = false;
		XPLMCommandKeyStroke(xplm_key_smoke);
	}

	/* smoke on */
	if(XPlaneData->rpm() < 1 && XPlaneData->engRun() == 0 && apu_RPM == 0 && smoke == false) {
		smoke = true;
		XPLMCommandKeyStroke(xplm_key_smoke);
	}


}
