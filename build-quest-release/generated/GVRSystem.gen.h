#pragma once
#include "BaseCommon.h"
#include "interfaces/IVRSystem_009.h"
#include "interfaces/IVRSystem_011.h"
#include "interfaces/IVRSystem_012.h"
#include "interfaces/IVRSystem_014.h"
#include "interfaces/IVRSystem_015.h"
#include "interfaces/IVRSystem_016.h"
#include "interfaces/IVRSystem_017.h"
#include "interfaces/IVRSystem_019.h"
#include "interfaces/IVRSystem_020.h"
#include "interfaces/IVRSystem_021.h"
#include "interfaces/IVRSystem_022.h"
#include "Reimpl/BaseSystem.h"
class CVRSystem_009 : public vr::IVRSystem_009::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_009();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void ResetSeatedZeroPose() override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool CaptureInputFocus() override;
	void ReleaseInputFocus() override;
	bool IsInputFocusCapturedByAnotherProcess() override;
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	void AcknowledgeQuit_UserPrompt() override;
};
#include "Reimpl/BaseSystem.h"
class CVRSystem_011 : public vr::IVRSystem_011::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_011();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void ResetSeatedZeroPose() override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) override;
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool CaptureInputFocus() override;
	void ReleaseInputFocus() override;
	bool IsInputFocusCapturedByAnotherProcess() override;
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	void AcknowledgeQuit_UserPrompt() override;
	void PerformanceTestEnableCapture(bool bEnable) override;
	void PerformanceTestReportFidelityLevelChange(int nFidelityLevel) override;
};
#include "Reimpl/BaseSystem.h"
class CVRSystem_012 : public vr::IVRSystem_012::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_012();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void ResetSeatedZeroPose() override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) override;
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool CaptureInputFocus() override;
	void ReleaseInputFocus() override;
	bool IsInputFocusCapturedByAnotherProcess() override;
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	void AcknowledgeQuit_UserPrompt() override;
};
#include "Reimpl/BaseSystem.h"
class CVRSystem_014 : public vr::IVRSystem_014::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_014();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void ResetSeatedZeroPose() override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) override;
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool CaptureInputFocus() override;
	void ReleaseInputFocus() override;
	bool IsInputFocusCapturedByAnotherProcess() override;
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	void AcknowledgeQuit_UserPrompt() override;
};
#include "Reimpl/BaseSystem.h"
class CVRSystem_015 : public vr::IVRSystem_015::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_015();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void ResetSeatedZeroPose() override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) override;
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool CaptureInputFocus() override;
	void ReleaseInputFocus() override;
	bool IsInputFocusCapturedByAnotherProcess() override;
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	void AcknowledgeQuit_UserPrompt() override;
};
#include "Reimpl/BaseSystem.h"
class CVRSystem_016 : public vr::IVRSystem_016::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_016();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	void GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void ResetSeatedZeroPose() override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) override;
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool CaptureInputFocus() override;
	void ReleaseInputFocus() override;
	bool IsInputFocusCapturedByAnotherProcess() override;
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	void AcknowledgeQuit_UserPrompt() override;
};
#include "Reimpl/BaseSystem.h"
class CVRSystem_017 : public vr::IVRSystem_017::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_017();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	void GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void ResetSeatedZeroPose() override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) override;
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool CaptureInputFocus() override;
	void ReleaseInputFocus() override;
	bool IsInputFocusCapturedByAnotherProcess() override;
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	void AcknowledgeQuit_UserPrompt() override;
};
#include "Reimpl/BaseSystem.h"
class CVRSystem_019 : public vr::IVRSystem_019::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_019();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	void GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void ResetSeatedZeroPose() override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) override;
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::PropertyTypeTag_t propType, void* pBuffer, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool IsInputAvailable() override;
	bool IsSteamVRDrawingControllers() override;
	bool ShouldApplicationPause() override;
	bool ShouldApplicationReduceRenderingWork() override;
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	void AcknowledgeQuit_UserPrompt() override;
};
#include "Reimpl/BaseSystem.h"
class CVRSystem_020 : public vr::IVRSystem_020::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_020();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	void GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void ResetSeatedZeroPose() override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) override;
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::PropertyTypeTag_t propType, void* pBuffer, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool IsInputAvailable() override;
	bool IsSteamVRDrawingControllers() override;
	bool ShouldApplicationPause() override;
	bool ShouldApplicationReduceRenderingWork() override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	void AcknowledgeQuit_UserPrompt() override;
	uint32_t GetAppContainerFilePaths(char* pchBuffer, uint32_t unBufferSize) override;
	const char* GetRuntimeVersion() override;
};
#include "Reimpl/BaseSystem.h"
class CVRSystem_021 : public vr::IVRSystem_021::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_021();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	void GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	void ResetSeatedZeroPose() override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) override;
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::PropertyTypeTag_t propType, void* pBuffer, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool IsInputAvailable() override;
	bool IsSteamVRDrawingControllers() override;
	bool ShouldApplicationPause() override;
	bool ShouldApplicationReduceRenderingWork() override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	uint32_t GetAppContainerFilePaths(char* pchBuffer, uint32_t unBufferSize) override;
	const char* GetRuntimeVersion() override;
};
#include "Reimpl/BaseSystem.h"
class CVRSystem_022 : public vr::IVRSystem_022::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSystem_022();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) override;
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye) override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;
	int32_t GetD3D9AdapterIndex() override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex) override;
	void GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) override;
	bool IsDisplayOnDesktop() override;
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop) override;
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) override;
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override;
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) override;
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) override;
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) override;
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) override;
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) override;
	uint32_t GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::PropertyTypeTag_t propType, void* pBuffer, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) override;
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) override;
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) override;
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType) override;
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) override;
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) override;
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) override;
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) override;
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) override;
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) override;
	bool IsInputAvailable() override;
	bool IsSteamVRDrawingControllers() override;
	bool ShouldApplicationPause() override;
	bool ShouldApplicationReduceRenderingWork() override;
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) override;
	void AcknowledgeQuit_Exiting() override;
	uint32_t GetAppContainerFilePaths(char* pchBuffer, uint32_t unBufferSize) override;
	const char* GetRuntimeVersion() override;
};
