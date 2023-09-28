#pragma once
#include "BaseCommon.h"
#include "interfaces/IVRInput_004.h"
#include "interfaces/IVRInput_005.h"
#include "interfaces/IVRInput_006.h"
#include "interfaces/IVRInput_007.h"
#include "interfaces/IVRInput_010.h"
#include "Reimpl/BaseInput.h"
class CVRInput_004 : public vr::IVRInput_004::IVRInput, public CVRCommon {
private:
	const std::shared_ptr<BaseInput> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRInput_004();
	// Interface methods:
	vr::EVRInputError SetActionManifestPath(const char* pchActionManifestPath) override;
	vr::EVRInputError GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) override;
	vr::EVRInputError GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) override;
	vr::EVRInputError GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) override;
	vr::EVRInputError UpdateActionState(vr::IVRInput_004::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) override;
	vr::EVRInputError GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_004::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_004::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetPoseActionData(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_004::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_004::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_004::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::IVRInput_004::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError DecompressSkeletalBoneData(void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_004::EVRSkeletalTransformSpace* peTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) override;
	vr::EVRInputError GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize) override;
	vr::EVRInputError GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_004::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) override;
	vr::EVRInputError ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) override;
	vr::EVRInputError ShowBindingsForActionSet(vr::IVRInput_004::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) override;
};
#include "Reimpl/BaseInput.h"
class CVRInput_005 : public vr::IVRInput_005::IVRInput, public CVRCommon {
private:
	const std::shared_ptr<BaseInput> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRInput_005();
	// Interface methods:
	vr::EVRInputError SetActionManifestPath(const char* pchActionManifestPath) override;
	vr::EVRInputError GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) override;
	vr::EVRInputError GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) override;
	vr::EVRInputError GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) override;
	vr::EVRInputError UpdateActionState(vr::IVRInput_005::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) override;
	vr::EVRInputError GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_005::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_005::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetPoseActionData(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_005::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_005::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize) override;
	vr::EVRInputError GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) override;
	vr::EVRInputError GetBoneHierarchy(vr::VRActionHandle_t action, vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) override;
	vr::EVRInputError GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, char* pchBoneName, uint32_t unNameBufferSize) override;
	vr::EVRInputError GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::IVRInput_005::EVRSkeletalTransformSpace eTransformSpace, vr::IVRInput_005::EVRSkeletalReferencePose eReferencePose, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::IVRInput_005::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) override;
	vr::EVRInputError GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_005::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::IVRInput_005::VRSkeletalSummaryData_t* pSkeletalSummaryData) override;
	vr::EVRInputError GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize) override;
	vr::EVRInputError DecompressSkeletalBoneData(const void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_005::EVRSkeletalTransformSpace eTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) override;
	vr::EVRInputError GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) override;
	vr::EVRInputError GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_005::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) override;
	vr::EVRInputError ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) override;
	vr::EVRInputError ShowBindingsForActionSet(vr::IVRInput_005::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) override;
};
#include "Reimpl/BaseInput.h"
class CVRInput_006 : public vr::IVRInput_006::IVRInput, public CVRCommon {
private:
	const std::shared_ptr<BaseInput> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRInput_006();
	// Interface methods:
	vr::EVRInputError SetActionManifestPath(const char* pchActionManifestPath) override;
	vr::EVRInputError GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) override;
	vr::EVRInputError GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) override;
	vr::EVRInputError GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) override;
	vr::EVRInputError UpdateActionState(vr::IVRInput_006::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) override;
	vr::EVRInputError GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_006::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_006::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetPoseActionDataRelativeToNow(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_006::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetPoseActionDataForNextFrame(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, vr::IVRInput_006::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_006::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize) override;
	vr::EVRInputError GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) override;
	vr::EVRInputError GetBoneHierarchy(vr::VRActionHandle_t action, vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) override;
	vr::EVRInputError GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, char* pchBoneName, uint32_t unNameBufferSize) override;
	vr::EVRInputError GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::IVRInput_006::EVRSkeletalTransformSpace eTransformSpace, vr::IVRInput_006::EVRSkeletalReferencePose eReferencePose, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) override;
	vr::EVRInputError GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_006::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::IVRInput_006::EVRSummaryType eSummaryType, vr::IVRInput_006::VRSkeletalSummaryData_t* pSkeletalSummaryData) override;
	vr::EVRInputError GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize) override;
	vr::EVRInputError DecompressSkeletalBoneData(const void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_006::EVRSkeletalTransformSpace eTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) override;
	vr::EVRInputError GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) override;
	vr::EVRInputError GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_006::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) override;
	vr::EVRInputError ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) override;
	vr::EVRInputError ShowBindingsForActionSet(vr::IVRInput_006::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) override;
	bool IsUsingLegacyInput() override;
};
#include "Reimpl/BaseInput.h"
class CVRInput_007 : public vr::IVRInput_007::IVRInput, public CVRCommon {
private:
	const std::shared_ptr<BaseInput> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRInput_007();
	// Interface methods:
	vr::EVRInputError SetActionManifestPath(const char* pchActionManifestPath) override;
	vr::EVRInputError GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) override;
	vr::EVRInputError GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) override;
	vr::EVRInputError GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) override;
	vr::EVRInputError UpdateActionState(vr::IVRInput_007::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) override;
	vr::EVRInputError GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_007::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_007::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetPoseActionDataRelativeToNow(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_007::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetPoseActionDataForNextFrame(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, vr::IVRInput_007::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_007::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize) override;
	vr::EVRInputError GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) override;
	vr::EVRInputError GetBoneHierarchy(vr::VRActionHandle_t action, vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) override;
	vr::EVRInputError GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, char* pchBoneName, uint32_t unNameBufferSize) override;
	vr::EVRInputError GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::IVRInput_007::EVRSkeletalTransformSpace eTransformSpace, vr::IVRInput_007::EVRSkeletalReferencePose eReferencePose, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) override;
	vr::EVRInputError GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_007::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::IVRInput_007::EVRSummaryType eSummaryType, vr::IVRInput_007::VRSkeletalSummaryData_t* pSkeletalSummaryData) override;
	vr::EVRInputError GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize) override;
	vr::EVRInputError DecompressSkeletalBoneData(const void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_007::EVRSkeletalTransformSpace eTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) override;
	vr::EVRInputError GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) override;
	vr::EVRInputError GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_007::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) override;
	vr::EVRInputError GetActionBindingInfo(vr::VRActionHandle_t action, vr::IVRInput_007::InputBindingInfo_t* pOriginInfo, uint32_t unBindingInfoSize, uint32_t unBindingInfoCount, uint32_t* punReturnedBindingInfoCount) override;
	vr::EVRInputError ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) override;
	vr::EVRInputError ShowBindingsForActionSet(vr::IVRInput_007::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) override;
	bool IsUsingLegacyInput() override;
	vr::EVRInputError OpenBindingUI(const char* pchAppKey, vr::VRActionSetHandle_t ulActionSetHandle, vr::VRInputValueHandle_t ulDeviceHandle, bool bShowOnDesktop) override;
};
#include "Reimpl/BaseInput.h"
class CVRInput_010 : public vr::IVRInput_010::IVRInput, public CVRCommon {
private:
	const std::shared_ptr<BaseInput> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRInput_010();
	// Interface methods:
	vr::EVRInputError SetActionManifestPath(const char* pchActionManifestPath) override;
	vr::EVRInputError GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) override;
	vr::EVRInputError GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) override;
	vr::EVRInputError GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) override;
	vr::EVRInputError UpdateActionState(vr::IVRInput_010::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) override;
	vr::EVRInputError GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_010::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_010::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetPoseActionDataRelativeToNow(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_010::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetPoseActionDataForNextFrame(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, vr::IVRInput_010::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_010::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize) override;
	vr::EVRInputError GetDominantHand(vr::ETrackedControllerRole* peDominantHand) override;
	vr::EVRInputError SetDominantHand(vr::ETrackedControllerRole eDominantHand) override;
	vr::EVRInputError GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) override;
	vr::EVRInputError GetBoneHierarchy(vr::VRActionHandle_t action, vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) override;
	vr::EVRInputError GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, char* pchBoneName, uint32_t unNameBufferSize) override;
	vr::EVRInputError GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::IVRInput_010::EVRSkeletalTransformSpace eTransformSpace, vr::IVRInput_010::EVRSkeletalReferencePose eReferencePose, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) override;
	vr::EVRInputError GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_010::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::IVRInput_010::EVRSummaryType eSummaryType, vr::IVRInput_010::VRSkeletalSummaryData_t* pSkeletalSummaryData) override;
	vr::EVRInputError GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize) override;
	vr::EVRInputError DecompressSkeletalBoneData(const void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_010::EVRSkeletalTransformSpace eTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) override;
	vr::EVRInputError TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) override;
	vr::EVRInputError GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) override;
	vr::EVRInputError GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) override;
	vr::EVRInputError GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_010::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) override;
	vr::EVRInputError GetActionBindingInfo(vr::VRActionHandle_t action, vr::IVRInput_010::InputBindingInfo_t* pOriginInfo, uint32_t unBindingInfoSize, uint32_t unBindingInfoCount, uint32_t* punReturnedBindingInfoCount) override;
	vr::EVRInputError ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) override;
	vr::EVRInputError ShowBindingsForActionSet(vr::IVRInput_010::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) override;
	vr::EVRInputError GetComponentStateForBinding(const char* pchRenderModelName, const char* pchComponentName, const vr::IVRInput_010::InputBindingInfo_t* pOriginInfo, uint32_t unBindingInfoSize, uint32_t unBindingInfoCount, vr::RenderModel_ComponentState_t* pComponentState) override;
	bool IsUsingLegacyInput() override;
	vr::EVRInputError OpenBindingUI(const char* pchAppKey, vr::VRActionSetHandle_t ulActionSetHandle, vr::VRInputValueHandle_t ulDeviceHandle, bool bShowOnDesktop) override;
	vr::EVRInputError GetBindingVariant(vr::VRInputValueHandle_t ulDevicePath, char* pchVariantArray, uint32_t unVariantArraySize) override;
};
