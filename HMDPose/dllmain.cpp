#ifdef _WIN32
#define UNITYCALLCONV __stdcall
#define UNITYEXPORT __declspec(dllexport)
#else
#define UNITYCALLCONV
#define UNITYEXPORT
#endif

#include "openvr.h"
using namespace vr;

IVRSystem* vr_pointer = NULL;
TrackedDevicePose_t trackedDevicePose;

extern "C" {
	UNITYEXPORT int UNITYCALLCONV init() {
		EVRInitError eError = VRInitError_None;
		vr_pointer = VR_Init(&eError, VRApplication_Background);
		if (eError != VRInitError_None)
		{
			return -1;
		}
		return 0;
	}
	UNITYEXPORT void UNITYCALLCONV update() {
		vr_pointer->GetDeviceToAbsoluteTrackingPose(TrackingUniverseRawAndUncalibrated, 0, &trackedDevicePose, 1);
	}
	UNITYEXPORT float UNITYCALLCONV get(int i, int j) {
		return trackedDevicePose.mDeviceToAbsoluteTracking.m[i][j];
	}
}