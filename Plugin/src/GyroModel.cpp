/*
 * GyroModel.cpp
 *
 *  Created on: Jan 28, 2010
 *      Author: ksgy
 */

#include "GyroModel.h"
#include <iostream>
#include <math.h>


GyroModel::GyroModel() {
	XPlaneData = new XpData();
	gyroRPM = GYRO_MAX_RPM; // invert rpm to be easier handle the deviation by rpm

	gyroType g;
	g.pitch = -90.0;
	g.roll = -90.0;
	g.yaw = -35.0;

	//xplaneGyro = XPlaneData->getOrigGyro();
	xplaneGyro = g;
	finalGyro = XPlaneData->getGyro();
	cageGyro = XPlaneData->getGyro();

	caged = false;

}

GyroModel::~GyroModel() {
	delete XPlaneData;
}


void GyroModel::run() {

	checkGyroRPM();

	xplaneGyro = XPlaneData->getOrigGyro();
	
	if(XPlaneData->arrest() > 0) {
		addDeviation();
	} else {
		cage();
	}
	addYawDeviation();


	finalGyro.pitch = xplaneGyro.pitch - cageGyro.pitch;
	finalGyro.roll = xplaneGyro.roll - cageGyro.roll;
	finalGyro.yaw = xplaneGyro.yaw - cageGyro.yaw;

	if(finalGyro.roll>90) {finalGyro.roll = 90; }
	if(finalGyro.pitch>60) {finalGyro.pitch = 60; }

	if(finalGyro.roll<-90) {finalGyro.roll = -90; }
	if(finalGyro.pitch<-60) {finalGyro.pitch = -60; }


	XPlaneData->setGyro(finalGyro);

	setEQOff();

}

void GyroModel::cage() {

	if(!caged) {
		cageGyro.roll <= xplaneGyro.roll ? cageGyro.roll+=1 : cageGyro.roll-=1;
		if (fabs(cageGyro.roll-xplaneGyro.roll) < 1) {
			cageGyro.roll = xplaneGyro.roll;
			cageGyro.pitch <= xplaneGyro.pitch  ? cageGyro.pitch+=1 : cageGyro.pitch-=1;
			if (fabs(cageGyro.pitch-xplaneGyro.pitch) < 1) {
				cageGyro.pitch = xplaneGyro.pitch;
				caged=true;
			}
		}
	} else {
		cageGyro.pitch = xplaneGyro.pitch;
		cageGyro.roll = xplaneGyro.roll;
	}


}

void GyroModel::addDeviation() {

	caged = false;

	float deviation;
	deviation = (gyroRPM+1)*0.000013888875; // 2 ora alatt 3 fok = 7200mp
	if(cageGyro.pitch < 60) {
		cageGyro.pitch = cageGyro.pitch+deviation;
	}
	if(cageGyro.roll < 90) {
		cageGyro.roll = cageGyro.roll+deviation;
	}


}

void GyroModel::addYawDeviation() {
	cageGyro.yaw = cageGyro.yaw+0.000111111; // 15p alatt 3 fok
	XPLMSetDataf(XPLMFindDataRef("sim/cockpit2/radios/actuators/nav2_obs_deg_mag_pilot"),XPLMGetDataf(XPLMFindDataRef("sim/cockpit2/radios/actuators/nav2_obs_deg_mag_pilot"))+0.000055555); // 30p alatt 3 fok
}


void GyroModel::checkGyroRPM() {

	if(XPlaneData->avionics() == 1 && gyroRPM > 0) { // TODO replace to inverter, add battery
		gyroRPM--;
	} else {
		if(gyroRPM < GYRO_MAX_RPM) {
			gyroRPM++;
		}
	}

}


void GyroModel::setEQOff(){




	if(XPlaneData->equalizer()==1) {
		float nav1=XPLMGetDataf(XPLMFindDataRef("sim/cockpit2/radios/actuators/nav1_obs_deg_mag_pilot"));
		float nav2=XPLMGetDataf(XPLMFindDataRef("sim/cockpit2/radios/actuators/nav2_obs_deg_mag_pilot"));

		if(nav2<nav1){
			XPLMSetDataf(XPLMFindDataRef("sim/cockpit2/radios/actuators/nav2_obs_deg_mag_pilot"),XPLMGetDataf(XPLMFindDataRef("sim/cockpit2/radios/actuators/nav2_obs_deg_mag_pilot"))+0.5);
		} else {
			XPLMSetDataf(XPLMFindDataRef("sim/cockpit2/radios/actuators/nav2_obs_deg_mag_pilot"),XPLMGetDataf(XPLMFindDataRef("sim/cockpit2/radios/actuators/nav2_obs_deg_mag_pilot"))-0.5);
		}

		if(round(nav2)==round(nav1)) {
			XPlaneData->setEqualizerOff();
		}
	}

}


float round(float number) {
	return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}
