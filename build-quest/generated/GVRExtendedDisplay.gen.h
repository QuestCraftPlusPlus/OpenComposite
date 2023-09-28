#pragma once
#include "BaseCommon.h"
#include "interfaces/IVRExtendedDisplay_001.h"
#include "Reimpl/BaseExtendedDisplay.h"
class CVRExtendedDisplay_001 : public vr::IVRExtendedDisplay_001::IVRExtendedDisplay, public CVRCommon {
private:
	const std::shared_ptr<BaseExtendedDisplay> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRExtendedDisplay_001();
	// Interface methods:
	void GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
	void GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex, int32_t* pnAdapterOutputIndex) override;
};
