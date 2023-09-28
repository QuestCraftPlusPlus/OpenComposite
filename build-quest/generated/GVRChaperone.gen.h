#pragma once
#include "BaseCommon.h"
#include "interfaces/IVRChaperone_003.h"
#include "interfaces/IVRChaperone_004.h"
#include "Reimpl/BaseChaperone.h"
class CVRChaperone_003 : public vr::IVRChaperone_003::IVRChaperone, public CVRCommon {
private:
	const std::shared_ptr<BaseChaperone> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRChaperone_003();
	// Interface methods:
	vr::IVRChaperone_003::ChaperoneCalibrationState GetCalibrationState() override;
	bool GetPlayAreaSize(float* pSizeX, float* pSizeZ) override;
	bool GetPlayAreaRect(vr::HmdQuad_t* rect) override;
	void ReloadInfo() override;
	void SetSceneColor(vr::HmdColor_t color) override;
	void GetBoundsColor(vr::HmdColor_t* pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, vr::HmdColor_t* pOutputCameraColor) override;
	bool AreBoundsVisible() override;
	void ForceBoundsVisible(bool bForce) override;
};
#include "Reimpl/BaseChaperone.h"
class CVRChaperone_004 : public vr::IVRChaperone_004::IVRChaperone, public CVRCommon {
private:
	const std::shared_ptr<BaseChaperone> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRChaperone_004();
	// Interface methods:
	vr::IVRChaperone_004::ChaperoneCalibrationState GetCalibrationState() override;
	bool GetPlayAreaSize(float* pSizeX, float* pSizeZ) override;
	bool GetPlayAreaRect(vr::HmdQuad_t* rect) override;
	void ReloadInfo() override;
	void SetSceneColor(vr::HmdColor_t color) override;
	void GetBoundsColor(vr::HmdColor_t* pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, vr::HmdColor_t* pOutputCameraColor) override;
	bool AreBoundsVisible() override;
	void ForceBoundsVisible(bool bForce) override;
	void ResetZeroPose(vr::ETrackingUniverseOrigin eTrackingUniverseOrigin) override;
};
