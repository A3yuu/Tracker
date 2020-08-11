#include "openvr.h"
using namespace vr;
int main()
{
	IVRSystem* vr_pointer = NULL;
	EVRInitError eError = VRInitError_None;
	vr_pointer = VR_Init(&eError, VRApplication_Background);
	if (eError != VRInitError_None)
	{
		printf("Error: %s \n", VR_GetVRInitErrorAsEnglishDescription(eError));
		return -1;
	}
	TrackedDevicePose_t trackedDevicePose;
	while (true) {
		vr_pointer->GetDeviceToAbsoluteTrackingPose(TrackingUniverseStanding, 0, &trackedDevicePose, 1);
		for (int i = 0;i < 3;i++) {
			for (int j = 0;j < 4;j++) {
				printf("%.2f",trackedDevicePose.mDeviceToAbsoluteTracking.m[i][j]);
			}
		}
		printf("\n");
	}
}
