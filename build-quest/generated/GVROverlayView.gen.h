#pragma once
#include "BaseCommon.h"
#include "interfaces/IVROverlayView_003.h"
#include "Reimpl/BaseOverlayView.h"
class CVROverlayView_003 : public vr::IVROverlayView_003::IVROverlayView, public CVRCommon {
private:
	const std::shared_ptr<BaseOverlayView> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVROverlayView_003();
	// Interface methods:
	vr::EVROverlayError AcquireOverlayView(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlayView_003::VRNativeDevice_t* pNativeDevice, vr::IVROverlayView_003::VROverlayView_t* pOverlayView, uint32_t unOverlayViewSize) override;
	vr::EVROverlayError ReleaseOverlayView(vr::IVROverlayView_003::VROverlayView_t* pOverlayView) override;
	void PostOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, const vr::VREvent_t* pvrEvent) override;
	bool IsViewingPermitted(vr::VROverlayHandle_t ulOverlayHandle) override;
};
