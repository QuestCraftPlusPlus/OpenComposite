#pragma once
#include "BaseCommon.h"
#include "custom_interfaces/IVRControlPanel_006.h"
#include "Reimpl/BaseControlPanel.h"
class CVRControlPanel_006 : public vr::IVRControlPanel_006::IVRControlPanel, public CVRCommon {
private:
	const std::shared_ptr<BaseControlPanel> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRControlPanel_006();
	// Interface methods:
	void UknFunc00() override;
	void UknFunc01() override;
	void UknFunc02() override;
	void UknFunc03() override;
	void UknFunc04() override;
	void UknFunc05() override;
	void UknFunc06() override;
	void UknFunc07() override;
	void UknFunc08() override;
	void UknFunc09() override;
	void UknFunc10() override;
	void UknFunc11() override;
	void UknFunc12() override;
	void UknFunc13() override;
	void UknFunc14() override;
	void SetDashBoardUserToggleEnabled(bool status) override;
	void UknFunc16() override;
	void UknFunc17() override;
	void UknFunc18() override;
	void UknFunc19() override;
	void UknFunc20() override;
	void UknFunc21() override;
	void UknFunc22() override;
	void UknFunc23() override;
	void UknFunc24() override;
	void UknFunc25() override;
	vr::IVRControlPanel_006::EVR_ControlPanel_Error RegisterExternalWebRoot() override;
	void UknFunc27() override;
	void UknFunc28() override;
	void UknFunc29() override;
};
