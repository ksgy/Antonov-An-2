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
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "datarefs.h"
#include "XpData.h"
#include "EngineModel.h"
#include "FlyWheelModel.h"
#include "GyroModel.h"
// #include "GeneralModel.h"


#define MAX_NUMBER_ENGINES 1


EngineModel * An2Engine = NULL;
FlyWheelModel * An2FlyWheel = NULL;
GyroModel * An2Gyro = NULL;
// GeneralModel * An2General = NULL;

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

	XPLMSetDataf(GyroPitchDataRef, -60.0);
	XPLMSetDataf(GyroRollDataRef, 90.0);
	XPLMSetDataf(GyroYawDataRef, 0.0);


	strcpy(outName, "Antonov An-2 Plugin");
	strcpy(outSig, "hu.an2.ksgy");
	strcpy(outDesc, "Helper plugin for Antonov An-2.");

	XPLMRegisterFlightLoopCallback(An2StartCallback, 1.0, NULL);


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
	// delete An2General;
}


PLUGIN_API void XPluginDisable(void) {
	XPLMUnregisterFlightLoopCallback(FLCallback, NULL);

	XPLMUnregisterFlightLoopCallback(An2StartCallback, NULL);

	XPLMUnregisterDataAccessor(GyroPitchDataRef);
	XPLMUnregisterDataAccessor(GyroRollDataRef);
	XPLMUnregisterDataAccessor(GyroYawDataRef);

	XPLMUnregisterDataAccessor(OilTempDataRef);
	XPLMUnregisterDataAccessor(ChtTempDataRef);

	/*delete An2Engine;
	delete An2FlyWheel;
	delete An2Gyro;
	delete An2General;*/
}

PLUGIN_API int XPluginEnable(void) {
	return 1;
}


PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho, long inMessage, void* inParam){
}



float	FLCallback(float elapsedMe, float elapsedSim, int counter, void * refcon) {

	elapsedAll+=elapsedMe;

	if (!An2Engine->paused() && elapsedAll >= 0.25) {
    	An2Engine->run();
    	An2FlyWheel->run();
    	elapsedAll=0;
    }

    An2Gyro->run();
    //An2General->run();

    return 0.03333; // ~30fps
}





float	An2StartCallback(float elapsedMe, float elapsedSim, int counter, void * refcon) {
	An2Engine = new EngineModel();
	An2FlyWheel = new FlyWheelModel();
	An2Gyro = new GyroModel();
	//An2General = new GeneralModel();

	XPLMRegisterFlightLoopCallback(FLCallback, 1.0, NULL);
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

