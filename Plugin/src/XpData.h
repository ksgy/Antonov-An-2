/*
 * XpData.h
 *
 *  Created on: 2009.09.07.
 *      Author: ksgy
 */

extern XPLMDataRef DR_IAS;
extern XPLMDataRef DR_ENGROT;
extern XPLMDataRef DR_THRO;
extern XPLMDataRef DR_ENGRUN;
extern XPLMDataRef ChtTempDataRef;
extern XPLMDataRef DR_APU;
extern XPLMDataRef DR_AMBTEMP;
extern XPLMDataRef DR_COWL;
extern XPLMDataRef DR_CARB;
extern XPLMDataRef DR_MPR;
extern XPLMDataRef DR_PAUSED;
extern XPLMDataRef OilTempDataRef;
extern XPLMDataRef GyroPitchDataRef;
extern XPLMDataRef GyroRollDataRef;
extern XPLMDataRef GyroYawDataRef;
extern XPLMDataRef DR_ORIG_PITCH;
extern XPLMDataRef DR_ORIG_ROLL;
extern XPLMDataRef DR_ORIG_YAW;
extern XPLMDataRef DR_AVIONICS;
extern XPLMDataRef DR_ENGFAIL_SEIZE;
extern XPLMDataRef DR_ENGFAIL_FIRE;
extern XPLMDataRef DR_O_FF;
extern XPLMDataRef DR_FF;
extern XPLMDataRef DR_ARREST;
extern XPLMDataRef DR_PROP;
extern XPLMDataRef DR_EQUALIZER;
extern XPLMDataRef DR_BATTERY;


#ifndef DATAREFS_H_
#endif


#ifndef XPDATA_H_
#define XPDATA_H_


struct gyroType {
	float pitch;
	float roll;
	float yaw;
};


class XpData {
	public:
		XpData();
		virtual ~XpData();

		float	ias();
		float	rpm();
		float	prop();
		float	engRPM();
		float	cht();
		int		apuSW();
		int		engRun();
		float	amb();
		float	cowl();
		float	carb();
		float	mpr();
        bool    paused();
        float	Randf(int min, int max);
        float	oilTemp();
        int		avionics();
        int 	arrest();
        int 	equalizer();
        int 	battery();
        float	yokePitch();


        gyroType getGyro();
        gyroType getOrigGyro();


		void 	setCHT(float cht);
		void	setOilTemp(float temp);
		void 	setGyro(struct gyroType);
		void	setEqualizerOff();
};

#endif /* XPDATA_H_ */


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
