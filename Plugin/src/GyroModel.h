/*
 * GyroModel.h
 *
 *  Created on: Jan 28, 2010
 *      Author: ksgy
 */

#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"
#include "XpData.h"


#ifndef GYROMODEL_H_
#define GYROMODEL_H_

class GyroModel {
	public:
		GyroModel();
		virtual ~GyroModel();

		void run();

		float pitch;
		float roll;
		float yaw;

	private:

		const static float GYRO_MAX_RPM = 3600;

		XpData * XPlaneData;
		gyroType xplaneGyro; // original xplane gyro pos
		gyroType finalGyro; // actual instrument output
		gyroType cageGyro; // holder of last caged pos


		float gyroRPM;
		bool caged;

		void cage();
		void addDeviation();
		void addYawDeviation();
		void checkGyroRPM();
		void setEQOff();


};

#endif /* GYROMODEL_H_ */
