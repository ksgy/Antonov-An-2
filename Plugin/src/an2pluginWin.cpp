#include <math.h>
#include "XPLMPlugin.h"
#include "XPLMUtilities.h"
#include "XPLMProcessing.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "XPLMPlanes.h"
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "datarefs.h"
#include "XpData.h"
#include "EngineModel.h"
#include "FlyWheelModel.h"
#include "GyroModel.h"

#define MAX_NUMBER_ENGINES 1

EngineModel * An2Engine = NULL;
FlyWheelModel * An2FlyWheel = NULL;
GyroModel * An2Gyro = NULL;

XPLMDataRef OilTempDataRef = NULL;
XPLMDataRef ChtTempDataRef = NULL;

XPLMDataRef GyroPitchDataRef = NULL;
XPLMDataRef GyroRollDataRef = NULL;
XPLMDataRef GyroYawDataRef = NULL;

float elapsedAll = 0;

float oilTempValue;
float chtTempValue;

float gyroPitchValue;
float gyroRollValue;
float gyroYawValue;

float GetOilTempDataRefCB(void* inRefcon);
float GetChtTempDataRefCB(void* inRefcon);

float GetGyroPitchDataRefCB(void* inRefcon);
float GetGyroRollDataRefCB(void* inRefcon);
float GetGyroYawDataRefCB(void* inRefcon);

void SetChtTempDataRefCB(void* inRefcon, float outValue);
void SetOilTempDataRefCB(void* inRefcon, float outValue);

void SetGyroPitchDataRefCB(void* inRefcon, float outValue);
void SetGyroRollDataRefCB(void* inRefcon, float outValue);
void SetGyroYawDataRefCB(void* inRefcon, float outValue);

XPLMDebugString("An2 - Begin of plugin load");

float FLCallback(float elapsedME, float elapsedSim, int counter, void * refcon);

float An2StartCallback(float elapsedME, float elapsedSim, int counter, void * refcon);

XPLMWindowID	gWindow = NULL;
int				gClicked = 0;

void MyHandleKeyCallback(
                                   XPLMWindowID         inWindowID,
                                   char                 inKey,
                                   XPLMKeyFlags         inFlags,
                                   char                 inVirtualKey,
                                   void *               inRefcon,
                                   int                  losingFocus);

int MyHandleMouseClickCallback(
                                   XPLMWindowID         inWindowID,
                                   int                  x,
                                   int                  y,
                                   XPLMMouseStatus      inMouse,
                                   void *               inRefcon);

PLUGIN_API int XPluginStart(	char *		outName,
								char *		outSig,
								char *		outDesc)
{

	XPLMDebugString("An2 - PluginStart/begin");
	OilTempDataRef = XPLMRegisterDataAccessor("ksgy-an2/OilTemp", xplmType_Float, 1, NULL, NULL, GetOilTempDataRefCB, SetOilTempDataRefCB, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	ChtTempDataRef = XPLMRegisterDataAccessor("ksgy-an2/ChtTemp", xplmType_Float, 1, NULL, NULL, GetChtTempDataRefCB, SetChtTempDataRefCB, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

	GyroPitchDataRef = XPLMRegisterDataAccessor("ksgy-an2/GyroPitch", xplmType_Float, 1, NULL, NULL, GetGyroPitchDataRefCB, SetGyroPitchDataRefCB, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	GyroRollDataRef = XPLMRegisterDataAccessor("ksgy-an2/GyroRoll", xplmType_Float, 1, NULL, NULL, GetGyroRollDataRefCB, SetGyroRollDataRefCB, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	GyroYawDataRef = XPLMRegisterDataAccessor("ksgy-an2/GyroYaw", xplmType_Float, 1, NULL, NULL, GetGyroYawDataRefCB, SetGyroYawDataRefCB, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

	OilTempDataRef = XPLMFindDataRef ("ksgy-an2/OilTemp");
	ChtTempDataRef = XPLMFindDataRef ("ksgy-an2/ChtTemp");

	GyroPitchDataRef = XPLMFindDataRef ("ksgy-an2/GyroPitch");
	GyroRollDataRef = XPLMFindDataRef ("ksgy-an2/GyroRoll");
	GyroYawDataRef = XPLMFindDataRef ("ksgy-an2/GyroYaw");

	XPLMSetDataf(OilTempDataRef, 0.0);
	XPLMSetDataf(ChtTempDataRef, 0.0);

	XPLMSetDataf(GyroPitchDataRef, -60);
	XPLMSetDataf(GyroRollDataRef, 90);
	XPLMSetDataf(GyroYawDataRef, 0.0);


	strcpy(outName, "Antonov An-2 Plugin");
	strcpy(outSig, "hu.an2.ksgy");
	strcpy(outDesc, "Helper plugin for Antonov An-2.");
	
	XPLMDebugString("An2 - Registering An2StartCallback");

	XPLMRegisterFlightLoopCallback(An2StartCallback, 1.0, NULL);
	
	XPLMDebugString("An2 - Registered An2StartCallback");


	return 1;
}


PLUGIN_API void	XPluginStop(void) {
	XPLMUnregisterFlightLoopCallback(FLCallback, NULL);

	XPLMUnregisterFlightLoopCallback(An2StartCallback, NULL);

	XPLMUnregisterDataAccessor(GyroPitchDataRef);
	XPLMUnregisterDataAccessor(GyroRollDataRef);
	XPLMUnregisterDataAccessor(GyroYawDataRef);

	XPLMUnregisterDataAccessor(OilTempDataRef);
	XPLMUnregisterDataAccessor(ChtTempDataRef);

	delete An2Engine;
	delete An2FlyWheel;
	delete An2Gyro;
}


PLUGIN_API void XPluginDisable(void) {
	XPLMUnregisterFlightLoopCallback(FLCallback, NULL);

	XPLMUnregisterFlightLoopCallback(An2StartCallback, NULL);

	XPLMUnregisterDataAccessor(GyroPitchDataRef);
	XPLMUnregisterDataAccessor(GyroRollDataRef);
	XPLMUnregisterDataAccessor(GyroYawDataRef);

	XPLMUnregisterDataAccessor(OilTempDataRef);
	XPLMUnregisterDataAccessor(ChtTempDataRef);
}

PLUGIN_API int XPluginEnable(void) {
	return 1;
}


PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho, long inMessage, void* inParam){
}



float	FLCallback(float elapsedMe, float elapsedSim, int counter, void * refcon) {

	elapsedAll+=elapsedMe;

	if (!An2Engine->paused() && elapsedAll >= 0.25) {
		XPLMDebugString("An2 - Engine + Flywheel Run call");
    	An2Engine->run();
    	An2FlyWheel->run();
    	elapsedAll=0;
    }

    An2Gyro->run();
    XPLMDebugString("An2 - Gyro call");

    return 0.03333; // ~30fps
}





float	An2StartCallback(float elapsedMe, float elapsedSim, int counter, void * refcon) {
	XPLMDebugString("An2 - An2StartCallback");
	XPLMDebugString("An2 - Creating Models");
	An2Engine = new EngineModel();
	An2FlyWheel = new FlyWheelModel();
	An2Gyro = new GyroModel();
	
	XPLMDebugString("An2 - Registering FLCB");

	XPLMRegisterFlightLoopCallback(FLCallback, 1.0, NULL);
	
	XPLMDebugString("An2 - Registered FLCB");
    return 0;
}


void MyHandleKeyCallback(
                                   XPLMWindowID         inWindowID,
                                   char                 inKey,
                                   XPLMKeyFlags         inFlags,
                                   char                 inVirtualKey,
                                   void *               inRefcon,
                                   int                  losingFocus){
}

int MyHandleMouseClickCallback(
                                   XPLMWindowID         inWindowID,
                                   int                  x,
                                   int                  y,
                                   XPLMMouseStatus      inMouse,
                                   void *               inRefcon){
	return 1;
}


float GetChtTempDataRefCB(void* inRefcon) { return chtTempValue; }
float GetOilTempDataRefCB(void* inRefcon) { return oilTempValue; }

float GetGyroPitchDataRefCB(void* inRefcon) { return gyroPitchValue; }
float GetGyroRollDataRefCB(void* inRefcon) { return gyroRollValue; }
float GetGyroYawDataRefCB(void* inRefcon) { return gyroYawValue; }

void SetChtTempDataRefCB(void* inRefcon, float inValue) { chtTempValue = inValue; }
void SetOilTempDataRefCB(void* inRefcon, float inValue) { oilTempValue = inValue; }

void SetGyroPitchDataRefCB(void* inRefcon, float inValue) { gyroPitchValue = inValue; }
void SetGyroRollDataRefCB(void* inRefcon, float inValue) { gyroRollValue = inValue; }
void SetGyroYawDataRefCB(void* inRefcon, float inValue) { gyroYawValue = inValue; }

