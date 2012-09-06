/*
 * FlyWheelModel.h
 *
 *  Created on: 2009.09.26.
 *      Author: ksgy
 */

#include "XPLMDataAccess.h"
#include "XpData.h"
#include "XPLMUtilities.h"

#ifndef FLYWHEELMODEL_H_
#define FLYWHEELMODEL_H_

class FlyWheelModel {
	public:
		FlyWheelModel();
		virtual ~FlyWheelModel();

		void run();

	private:
		XpData *	XPlaneData;
		float 		apu_RPM;
		bool		smoke;
};

#endif /* FLYWHEELMODEL_H_ */
