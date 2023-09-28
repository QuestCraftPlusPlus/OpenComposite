#pragma once
#include "BaseCommon.h"
#include "custom_interfaces/IVRInputInternal_002.h"
#include "Reimpl/BaseInputInternal.h"
class CVRInputInternal_002 : public vr::IVRInputInternal_002::IVRInputInternal, public CVRCommon {
private:
	const std::shared_ptr<BaseInputInternal> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRInputInternal_002();
	// Interface methods:
	void UknFunc001() override;
	void UknFunc002() override;
	void UknFunc003() override;
	void UknFunc004() override;
	void UknFunc005() override;
	void UknFunc006() override;
	void UknFunc007() override;
	void UknFunc008() override;
	void UknFunc009() override;
	void UknFunc010() override;
	void UknFunc011() override;
	void UknFunc012() override;
	void UknFunc013() override;
	void UknFunc014() override;
	void UknFunc015() override;
	void UknFunc016() override;
	void UknFunc017() override;
	void UknFunc018() override;
	void UknFunc019() override;
	void UknFunc020() override;
};
