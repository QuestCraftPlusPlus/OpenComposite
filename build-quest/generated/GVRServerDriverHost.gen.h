#pragma once
#include "BaseCommon.h"
#include "interfaces/driver_IVRServerDriverHost_005.h"
#include "Reimpl/BaseServerDriverHost.h"
class CVRServerDriverHost_005 : public vr::driver_IVRServerDriverHost_005::IVRServerDriverHost, public CVRCommon {
private:
	const std::shared_ptr<BaseServerDriverHost> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRServerDriverHost_005();
	// Interface methods:
	bool TrackedDeviceAdded(const char* pchDeviceSerialNumber, vr::ETrackedDeviceClass eDeviceClass, vr::driver_ITrackedDeviceServerDriver_005::ITrackedDeviceServerDriver* pDriver) override;
	void TrackedDevicePoseUpdated(uint32_t unWhichDevice, const vr::driver_ITrackedDeviceServerDriver_005::DriverPose_t& newPose, uint32_t unPoseStructSize) override;
	void VsyncEvent(double vsyncTimeOffsetSeconds) override;
	void VendorSpecificEvent(uint32_t unWhichDevice, vr::EVREventType eventType, const vr::VREvent_Data_t& eventData, double eventTimeOffset) override;
	bool IsExiting() override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	void GetRawTrackedDevicePoses(float fPredictedSecondsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void TrackedDeviceDisplayTransformUpdated(uint32_t unWhichDevice, vr::HmdMatrix34_t eyeToHeadLeft, vr::HmdMatrix34_t eyeToHeadRight) override;
};
