
#include <string.h>
#include <windows.h>
#include <openvr_driver.h>

#include "com.h"

using namespace std;

#define HMD_DLL_EXPORT extern "C" __declspec(dllexport)
#define HMD_DLL_IMPORT extern "C" __declspec(dllimport)

inline vr::HmdQuaternion_t HmdQuaternion_Init(double w, double x, double y, double z)
{
    vr::HmdQuaternion_t quat;
    quat.w = w;
    quat.x = x;
    quat.y = y;
    quat.z = z;
    return quat;
}

SharedMemory com;

class A3Tracker : public vr::ITrackedDeviceServerDriver
{
    vr::TrackedDeviceIndex_t m_unObjectId;
    vr::PropertyContainerHandle_t m_ulPropertyContainer;
public:
    int32_t ControllerIndex;
    string m_SerialNumber;
    string m_InputProfilePath;
    string m_ControllerType;
    A3Tracker()
    {
        m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
        m_ulPropertyContainer = vr::k_ulInvalidPropertyContainer;
        m_SerialNumber = "";
        m_InputProfilePath = "";
        m_ControllerType = "";
        ControllerIndex = 0;
    }
    virtual ~A3Tracker() {};
    virtual vr::EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId)
    {

        m_unObjectId = unObjectId;
        m_ulPropertyContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(m_unObjectId);

        vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_ControllerType_String, m_ControllerType.c_str());

        vr::VRProperties()->SetInt32Property(m_ulPropertyContainer, vr::Prop_DeviceClass_Int32, vr::TrackedDeviceClass_GenericTracker);

        vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_SerialNumber_String, m_SerialNumber.c_str());

        vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_InputProfilePath_String, m_InputProfilePath.c_str());

        return vr::VRInitError_None;
    }

    virtual void Deactivate() {
        m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
    }

    virtual void EnterStandby() {}

    void* GetComponent(const char* pchComponentNameAndVersion) {
        return NULL;
    }

    virtual void PowerOff() {}

    virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) {
        if (unResponseBufferSize >= 1)
            pchResponseBuffer[0] = 0;
    }

    virtual vr::DriverPose_t GetPose()
    {
        vr::DriverPose_t pose = { 0 };
        pose.poseIsValid = true;
        pose.result = vr::TrackingResult_Running_OK;
        pose.deviceIsConnected = true;

        pose.qWorldFromDriverRotation = HmdQuaternion_Init(1, 0, 0, 0);
        pose.qDriverFromHeadRotation = HmdQuaternion_Init(1, 0, 0, 0);

        pose.vecPosition[0] = com.data[ControllerIndex * 7 + 0];
        pose.vecPosition[1] = com.data[ControllerIndex * 7 + 1];
        pose.vecPosition[2] = com.data[ControllerIndex * 7 + 2];
        pose.qRotation.x = com.data[ControllerIndex * 7 + 3];
        pose.qRotation.y = com.data[ControllerIndex * 7 + 4];
        pose.qRotation.z = com.data[ControllerIndex * 7 + 5];
        pose.qRotation.w = com.data[ControllerIndex * 7 + 6];

        return pose;
    }

    void RunFrame() {
        if (m_unObjectId != vr::k_unTrackedDeviceIndexInvalid) {
            vr::VRServerDriverHost()->TrackedDevicePoseUpdated(m_unObjectId, GetPose(), sizeof(vr::DriverPose_t));
        }
    }

    void ProcessEvent(const vr::VREvent_t& vrEvent) {}

    string GetSerialNumber() const {
        return m_SerialNumber;
    }

};

class A3TrackerProvider : public vr::IServerTrackedDeviceProvider
{
public:
    virtual vr::EVRInitError Init(vr::IVRDriverContext* pDriverContext) {

        VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
        
        m_pHip = new A3Tracker();
        m_pHip->m_SerialNumber = "A3Tracker_Hip";
        m_pHip->m_InputProfilePath = "{htc}/input/tracker/vive_tracker_waist_profile.json";
        m_pHip->m_ControllerType = "vive_tracker_waist";
        m_pHip->ControllerIndex = 0;
        vr::VRServerDriverHost()->TrackedDeviceAdded(m_pHip->GetSerialNumber().c_str(), vr::TrackedDeviceClass_GenericTracker, m_pHip);
        
        m_pLeft = new A3Tracker();
        m_pLeft->m_SerialNumber = "A3Tracker_Left";
        m_pLeft->m_InputProfilePath = "{htc}/input/tracker/vive_tracker_left_foot_profile.json";
        m_pLeft->m_ControllerType = "vive_tracker_left_foot";
        m_pLeft->ControllerIndex = 1;
        vr::VRServerDriverHost()->TrackedDeviceAdded(m_pLeft->GetSerialNumber().c_str(), vr::TrackedDeviceClass_GenericTracker, m_pLeft);

        m_pRight = new A3Tracker();
        m_pRight->m_SerialNumber = "A3Tracker_Right";
        m_pRight->m_InputProfilePath = "{htc}/input/tracker/vive_tracker_right_foot_profile.json";
        m_pRight->m_ControllerType = "vive_tracker_right_foot";
        m_pRight->ControllerIndex = 2;
        vr::VRServerDriverHost()->TrackedDeviceAdded(m_pRight->GetSerialNumber().c_str(), vr::TrackedDeviceClass_GenericTracker, m_pRight);

        return vr::VRInitError_None;
    }
    virtual void Cleanup() {
        delete m_pHip;
        m_pHip = NULL;
        delete m_pLeft;
        m_pLeft = NULL;
        delete m_pRight;
        m_pRight = NULL;
    }
    virtual const char* const* GetInterfaceVersions() {
        return vr::k_InterfaceVersions;
    }
    virtual void RunFrame() {
        com.Update();
        if (m_pHip) {
            m_pHip->RunFrame();
        }
        if (m_pLeft) {
            m_pLeft->RunFrame();
        }
        if (m_pRight) {
            m_pRight->RunFrame();
        }
    }
    virtual bool ShouldBlockStandbyMode() {
        return false;
    }
    virtual void EnterStandby() {}
    virtual void LeaveStandby() {}

private:
    vr::EVRInitError eError = vr::VRInitError_None;
    vr::TrackedDevicePose_t trackedDevicePose;
    A3Tracker* m_pHip = nullptr;
    A3Tracker* m_pLeft = nullptr;
    A3Tracker* m_pRight = nullptr;
};

A3TrackerProvider g_a3TrackerNull;

HMD_DLL_EXPORT void* HmdDriverFactory(const char* pInterfaceName, int* pReturnCode)
{
    if (0 == strcmp(vr::IServerTrackedDeviceProvider_Version, pInterfaceName)) {
        return &g_a3TrackerNull;
    }

    if (pReturnCode) {
        *pReturnCode = vr::VRInitError_Init_InterfaceNotFound;
    }

    return NULL;
}

