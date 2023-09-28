#pragma once
#include "BaseCommon.h"
#include "interfaces/IVRChaperoneSetup_004.h"
#include "interfaces/IVRChaperoneSetup_005.h"
#include "interfaces/IVRChaperoneSetup_006.h"
#include "Reimpl/BaseChaperoneSetup.h"
class CVRChaperoneSetup_004 : public vr::IVRChaperoneSetup_004::IVRChaperoneSetup, public CVRCommon {
private:
	const std::shared_ptr<BaseChaperoneSetup> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRChaperoneSetup_004();
	// Interface methods:
	bool CommitWorkingCopy(vr::IVRChaperoneSetup_004::EChaperoneConfigFile configFile) override;
	void RevertWorkingCopy() override;
	bool GetWorkingPlayAreaSize(float* pSizeX, float* pSizeZ) override;
	bool GetWorkingPlayAreaRect(vr::HmdQuad_t* rect) override;
	bool GetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) override;
	bool GetLiveCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) override;
	bool GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) override;
	bool GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatStandingZeroPoseToRawTrackingPose) override;
	void SetWorkingPlayAreaSize(float sizeX, float sizeZ) override;
	void SetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount) override;
	void SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatSeatedZeroPoseToRawTrackingPose) override;
	void SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatStandingZeroPoseToRawTrackingPose) override;
	void ReloadFromDisk(vr::IVRChaperoneSetup_004::EChaperoneConfigFile configFile) override;
	bool GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) override;
};
#include "Reimpl/BaseChaperoneSetup.h"
class CVRChaperoneSetup_005 : public vr::IVRChaperoneSetup_005::IVRChaperoneSetup, public CVRCommon {
private:
	const std::shared_ptr<BaseChaperoneSetup> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRChaperoneSetup_005();
	// Interface methods:
	bool CommitWorkingCopy(vr::IVRChaperoneSetup_005::EChaperoneConfigFile configFile) override;
	void RevertWorkingCopy() override;
	bool GetWorkingPlayAreaSize(float* pSizeX, float* pSizeZ) override;
	bool GetWorkingPlayAreaRect(vr::HmdQuad_t* rect) override;
	bool GetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) override;
	bool GetLiveCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) override;
	bool GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) override;
	bool GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatStandingZeroPoseToRawTrackingPose) override;
	void SetWorkingPlayAreaSize(float sizeX, float sizeZ) override;
	void SetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount) override;
	void SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatSeatedZeroPoseToRawTrackingPose) override;
	void SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatStandingZeroPoseToRawTrackingPose) override;
	void ReloadFromDisk(vr::IVRChaperoneSetup_005::EChaperoneConfigFile configFile) override;
	bool GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) override;
	void SetWorkingCollisionBoundsTagsInfo(uint8_t* pTagsBuffer, uint32_t unTagCount) override;
	bool GetLiveCollisionBoundsTagsInfo(uint8_t* pTagsBuffer, uint32_t* punTagCount) override;
	bool SetWorkingPhysicalBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount) override;
	bool GetLivePhysicalBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) override;
	bool ExportLiveToBuffer(char* pBuffer, uint32_t* pnBufferLength) override;
	bool ImportFromBufferToWorking(const char* pBuffer, uint32_t nImportFlags) override;
};
#include "Reimpl/BaseChaperoneSetup.h"
class CVRChaperoneSetup_006 : public vr::IVRChaperoneSetup_006::IVRChaperoneSetup, public CVRCommon {
private:
	const std::shared_ptr<BaseChaperoneSetup> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRChaperoneSetup_006();
	// Interface methods:
	bool CommitWorkingCopy(vr::IVRChaperoneSetup_006::EChaperoneConfigFile configFile) override;
	void RevertWorkingCopy() override;
	bool GetWorkingPlayAreaSize(float* pSizeX, float* pSizeZ) override;
	bool GetWorkingPlayAreaRect(vr::HmdQuad_t* rect) override;
	bool GetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) override;
	bool GetLiveCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) override;
	bool GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) override;
	bool GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatStandingZeroPoseToRawTrackingPose) override;
	void SetWorkingPlayAreaSize(float sizeX, float sizeZ) override;
	void SetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount) override;
	void SetWorkingPerimeter(vr::HmdVector2_t* pPointBuffer, uint32_t unPointCount) override;
	void SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatSeatedZeroPoseToRawTrackingPose) override;
	void SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatStandingZeroPoseToRawTrackingPose) override;
	void ReloadFromDisk(vr::IVRChaperoneSetup_006::EChaperoneConfigFile configFile) override;
	bool GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) override;
	bool ExportLiveToBuffer(char* pBuffer, uint32_t* pnBufferLength) override;
	bool ImportFromBufferToWorking(const char* pBuffer, uint32_t nImportFlags) override;
	void ShowWorkingSetPreview() override;
	void HideWorkingSetPreview() override;
	void RoomSetupStarting() override;
};
