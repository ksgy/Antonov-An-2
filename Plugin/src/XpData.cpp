/*
 * XpData.cpp
 *
 *  Created on: 2009.09.07.
 *      Author: ksgy
 */

#include "XPLMDataAccess.h"
#include "XpData.h"
#include <cstdlib>
#include <iostream>



XpData::XpData() {

}

XpData::~XpData() {}

float XpData::ias() {
	return XPLMGetDataf(DR_IAS);
}

float XpData::engRPM() {
	float _rpm;
	XPLMGetDatavf(DR_ENGROT, &_rpm, 0, 1);
	return _rpm;
}


float XpData::rpm() {
	float _rpm;
	float _rrpm;
	float _thro;
	XPLMGetDatavf(DR_ENGROT, &_rpm, 0, 1);
	_rrpm = _rpm * 100 / 230;
	XPLMGetDatavf(DR_THRO, &_thro, 0, 1);
	int _run;
	XPLMGetDatavi(DR_ENGRUN, &_run, 0, 1);

	return _run * (_thro*0.45 + _rrpm*0.80);

}

float XpData::prop() {
	float _pp;
	XPLMGetDatavf(DR_PROP, &_pp, 0, 1);
	return _pp*0.02222;
}

float XpData::cht() {
	return XPLMGetDataf(ChtTempDataRef);
}

int XpData::apuSW(){
	return XPLMGetDatai(DR_APU);
}

int XpData::engRun() {
	int _run;
	XPLMGetDatavi(DR_ENGRUN, &_run, 0, 1);
	return _run;
}

float XpData::amb(){
	return XPLMGetDataf(DR_AMBTEMP);
}

float XpData::cowl() {
	float _cowl;
	XPLMGetDatavf(DR_COWL, &_cowl, 0, 1);
	return _cowl;
}

float XpData::carb() {
	float _carb;
	XPLMGetDatavf(DR_CARB, &_carb, 0, 1);
	return _carb;
}

float XpData::mpr(){
	float _mpr;
	XPLMGetDatavf(DR_MPR, &_mpr, 0, 1);
	return _mpr;
}

bool XpData::paused(){
    if(XPLMGetDatai(DR_PAUSED) > 0) {
        return true;
    } else {
        return false;
    }
}

void XpData::setCHT(float cht){
	XPLMSetDataf(ChtTempDataRef, cht);
}

void XpData::setOilTemp(float temp) {
	XPLMSetDataf(OilTempDataRef, temp);
}

float XpData::oilTemp() {
	return XPLMGetDataf(OilTempDataRef);
}


void XpData::setGyro(gyroType gyro) {

	XPLMSetDataf(GyroPitchDataRef, gyro.pitch);
	XPLMSetDataf(GyroRollDataRef, gyro.roll);
	XPLMSetDataf(GyroYawDataRef, gyro.yaw);

}

gyroType XpData::getGyro() { // thx lobz

	gyroType gyro;

	gyro.pitch = XPLMGetDataf(GyroPitchDataRef);
	gyro.roll = XPLMGetDataf(GyroRollDataRef);
	gyro.yaw = XPLMGetDataf(GyroYawDataRef);
	return gyro;

}

gyroType XpData::getOrigGyro() {

	gyroType gyro;

	gyro.pitch = XPLMGetDataf(DR_ORIG_PITCH);
	gyro.roll = XPLMGetDataf(DR_ORIG_ROLL);
	gyro.yaw = XPLMGetDataf(DR_ORIG_YAW);
	return gyro;

}

int XpData::avionics() {
	return XPLMGetDatai(DR_AVIONICS);
}

int XpData::battery() {
	return XPLMGetDatai(DR_BATTERY);
}


int XpData::arrest() {
	return XPLMGetDatai(DR_ARREST);
}

int XpData::equalizer() {
	int _eq;
	XPLMGetDatavi(DR_EQUALIZER, &_eq, 0, 1);
	return _eq;
}

void XpData::setEqualizerOff(){
	int IntVals[24];
	IntVals[0] = 0;
	XPLMSetDatavi(DR_EQUALIZER, IntVals, 0, 1);
}


/* ----------------- */

float XpData::Randf(int min, int max){
	return ( 0.1f + (float)rand()/0x7fff )* (max-min) + min;
}

/*
XPLMDataRef ds_GS = XPLMFindDataRef("sim/flightmodel/position/groundspeed");
XPLMDataRef ds_RPM = XPLMFindDataRef("sim/flightmodel2/engines/engine_rotation_speed_rad_sec");
//XPLMDataRef ds_CHT = XPLMFindDataRef("sim/flightmodel/engine/ENGN_CHT_c");
XPLMDataRef ds_CHT = XPLMFindDataRef("sim/flightmodel/engine/ENGN_ITT_c");
XPLMDataRef ds_APUSwitch = XPLMFindDataRef("sim/cockpit/engine/APU_switch");
XPLMDataRef ds_EngineRunning = XPLMFindDataRef("sim/flightmodel/engine/ENGN_running");
XPLMDataRef ds_ambtemp = XPLMFindDataRef("sim/weather/temperature_ambient_c");
XPLMDataRef ds_Cowl = XPLMFindDataRef("sim/cockpit2/engine/actuators/cowl_flap_ratio");
XPLMDataRef ds_IAS = XPLMFindDataRef("sim/cockpit2/gauges/indicators/airspeed_kts_pilot");
XPLMDataRef ds_PROP = XPLMFindDataRef("sim/flightmodel2/engines/engine_rotation_speed_rad_sec");*/
