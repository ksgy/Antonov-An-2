/*
 * GeneralModel.h
 *
 *  Created on: Mar 20, 2010
 *      Author: ksgy
 */

#include "XPLMDataAccess.h"
#include "XpData.h"
#include "XPLMUtilities.h"

#ifndef GENERALMODEL_H_
#define GENERALMODEL_H_

class GeneralModel {
	public:
		GeneralModel();
		virtual ~GeneralModel();

		void run();

	private:
		XpData *	XPlaneData;

};

#endif /* GENERALMODEL_H_ */
