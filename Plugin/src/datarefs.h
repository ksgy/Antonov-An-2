/*
 * datarefs.h
 *
 *  Created on: 2009.08.27.
 *      Author: ksgy
 */

#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"

#ifndef DATAREFS_H_

#define DATAREFS_H_

XPLMDataRef DR_IAS = XPLMFindDataRef("sim/cockpit2/gauges/indicators/airspeed_kts_pilot");
XPLMDataRef DR_ENGROT = XPLMFindDataRef("sim/flightmodel2/engines/engine_rotation_speed_rad_sec");
XPLMDataRef DR_THRO = XPLMFindDataRef("sim/flightmodel/engine/ENGN_thro");
XPLMDataRef DR_ENGRUN = XPLMFindDataRef("sim/flightmodel/engine/ENGN_running");
XPLMDataRef DR_APU = XPLMFindDataRef("sim/cockpit/engine/APU_switch");
XPLMDataRef DR_AMBTEMP = XPLMFindDataRef("sim/weather/temperature_ambient_c");
XPLMDataRef DR_COWL = XPLMFindDataRef("sim/cockpit2/engine/actuators/cowl_flap_ratio");
XPLMDataRef DR_CARB = XPLMFindDataRef("sim/flightmodel/engine/ENGN_heat");
XPLMDataRef DR_MPR = XPLMFindDataRef("sim/cockpit2/engine/indicators/MPR_in_hg");
XPLMDataRef DR_PAUSED = XPLMFindDataRef("sim/time/paused");
XPLMDataRef DR_ORIG_PITCH = XPLMFindDataRef("sim/cockpit2/gauges/indicators/pitch_electric_deg_pilot");
XPLMDataRef DR_ORIG_ROLL = XPLMFindDataRef("sim/cockpit2/gauges/indicators/roll_electric_deg_pilot");
XPLMDataRef DR_ORIG_YAW = XPLMFindDataRef("sim/cockpit2/gauges/indicators/heading_electric_deg_mag_pilot");
XPLMDataRef DR_AVIONICS = XPLMFindDataRef("sim/cockpit/electrical/avionics_on");
XPLMDataRef DR_ENGFAIL_SEIZE = XPLMFindDataRef("sim/operation/failures/rel_seize_0");
XPLMDataRef DR_ENGFAIL_FIRE = XPLMFindDataRef("sim/operation/failures/rel_engfir0");
XPLMDataRef DR_O_FF = XPLMFindDataRef("sim/operation/override/override_fuel_flow");
XPLMDataRef DR_FF = XPLMFindDataRef("sim/flightmodel/engine/ENGN_FF_");
XPLMDataRef DR_ARREST = XPLMFindDataRef("sim/cockpit2/switches/camera_power_on");
XPLMDataRef DR_PROP = XPLMFindDataRef("sim/cockpit2/engine/actuators/prop_pitch_deg");
XPLMDataRef DR_EQUALIZER = XPLMFindDataRef("sim/cockpit2/switches/custom_slider_on");
XPLMDataRef DR_BATTERY = XPLMFindDataRef("sim/cockpit/electrical/battery_on");

#endif /* DATAREFS_H_ */
