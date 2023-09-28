#pragma once
#include "BaseCommon.h"
#include "custom_interfaces/IVRClientCore_003.h"
#include "custom_interfaces/IVRClientCore_002.h"
#include "Reimpl/BaseClientCore.h"
class CVRClientCore_003 : public vr::IVRClientCore_003::IVRClientCore, public CVRCommon {
private:
	const std::shared_ptr<BaseClientCore> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRClientCore_003();
	// Interface methods:
	vr::EVRInitError Init(vr::EVRApplicationType eApplicationType, const char* pStartupInfo) override;
	void Cleanup() override;
	vr::EVRInitError IsInterfaceVersionValid(const char* pchInterfaceVersion) override;
	void* GetGenericInterface(const char* pchNameAndVersion, vr::EVRInitError* peError) override;
	bool BIsHmdPresent() override;
	const char* GetEnglishStringForHmdError(vr::EVRInitError eError) override;
	const char* GetIDForVRInitError(vr::EVRInitError eError) override;
};
#include "Reimpl/BaseClientCore.h"
class CVRClientCore_002 : public vr::IVRClientCore_002::IVRClientCore, public CVRCommon {
private:
	const std::shared_ptr<BaseClientCore> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRClientCore_002();
	// Interface methods:
	vr::EVRInitError Init(vr::EVRApplicationType eApplicationType) override;
	void Cleanup() override;
	vr::EVRInitError IsInterfaceVersionValid(const char* pchInterfaceVersion) override;
	void* GetGenericInterface(const char* pchNameAndVersion, vr::EVRInitError* peError) override;
	bool BIsHmdPresent() override;
	const char* GetEnglishStringForHmdError(vr::EVRInitError eError) override;
	const char* GetIDForVRInitError(vr::EVRInitError eError) override;
};
