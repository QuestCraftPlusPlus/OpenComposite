#pragma once
#include "BaseCommon.h"
#include "custom_interfaces/IVRMailbox_001.h"
#include "Reimpl/BaseMailbox.h"
class CVRMailbox_001 : public vr::IVRMailbox_001::IVRMailbox, public CVRCommon {
private:
	const std::shared_ptr<BaseMailbox> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRMailbox_001();
	// Interface methods:
	vr::IVRMailbox_001::vrmb_typeb RegisterMailbox(const char* name, vr::IVRMailbox_001::mbox_handle* handle) override;
	vr::IVRMailbox_001::vrmb_typeb UnregisterMailbox(vr::IVRMailbox_001::mbox_handle handle) override;
	vr::IVRMailbox_001::vrmb_typeb SendMessage(vr::IVRMailbox_001::mbox_handle handle, const char* type, const char* message) override;
	vr::IVRMailbox_001::vrmb_typeb ReadMessage(vr::IVRMailbox_001::mbox_handle mbox, char* outBuf, uint32_t outBufLen, uint32_t* msgLen) override;
};
