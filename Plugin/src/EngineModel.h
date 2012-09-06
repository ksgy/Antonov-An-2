/*
 * EngineModel.h
 *
 *  Created on: 2009.08.19.
 *      Author: ksgy
 */
#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"
#include "XpData.h"


#ifndef ENGINEMODEL_H_
#define ENGINEMODEL_H_



class EngineModel {

	public:

		EngineModel();
		virtual ~EngineModel();
		void run();
        bool paused();

		float				rpm;


	private:
		float				amb;
		float				cht;
		float				oiltemp;
		int					running;
		float				cowl;
		float				ias;
		float				mpr;
		float 				prop;

		float				targetCHT;
		float				targetOilT;
		float				nonNormalCounter;

		static const float 	baseCHT;
		static const float 	min_CHT; // minimum required cht temp to apply full throttle
		static const float 	max_CHT; // max cht, where engine fires immediately
		static const float 	max_5min_rpm; // max rpm for 5 minutes, then fire the engine

		XpData * 			XPlaneData;

		void	readData();
		void	checkTemp();
		void 	debug();
		void	checkFail();
		void	failEngine(int type);
		void	repairEngine(int type);
		void	setOilTemp();




};


#endif /* ENGINEMODEL_H_ */
