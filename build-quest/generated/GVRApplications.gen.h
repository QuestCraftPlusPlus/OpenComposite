#pragma once
#include "BaseCommon.h"
#include "interfaces/IVRApplications_002.h"
#include "interfaces/IVRApplications_004.h"
#include "interfaces/IVRApplications_005.h"
#include "interfaces/IVRApplications_006.h"
#include "interfaces/IVRApplications_007.h"
#include "Reimpl/BaseApplications.h"
class CVRApplications_002 : public vr::IVRApplications_002::IVRApplications, public CVRCommon {
private:
	const std::shared_ptr<BaseApplications> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRApplications_002();
	// Interface methods:
	vr::IVRApplications_002::EVRApplicationError AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) override;
	vr::IVRApplications_002::EVRApplicationError RemoveApplicationManifest(const char* pchApplicationManifestFullPath) override;
	bool IsApplicationInstalled(const char* pchAppKey) override;
	uint32_t GetApplicationCount() override;
	vr::IVRApplications_002::EVRApplicationError GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_002::EVRApplicationError GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_002::EVRApplicationError LaunchApplication(const char* pchAppKey) override;
	vr::IVRApplications_002::EVRApplicationError LaunchDashboardOverlay(const char* pchAppKey) override;
	vr::IVRApplications_002::EVRApplicationError IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) override;
	uint32_t GetApplicationProcessId(const char* pchAppKey) override;
	const char* GetApplicationsErrorNameFromEnum(vr::IVRApplications_002::EVRApplicationError error) override;
	uint32_t GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_002::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_002::EVRApplicationError* peError) override;
	bool GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_002::EVRApplicationProperty eProperty, vr::IVRApplications_002::EVRApplicationError* peError) override;
	vr::IVRApplications_002::EVRApplicationError SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) override;
	bool GetApplicationAutoLaunch(const char* pchAppKey) override;
	vr::IVRApplications_002::EVRApplicationError GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_002::EVRApplicationTransitionState GetTransitionState() override;
	vr::IVRApplications_002::EVRApplicationError PerformApplicationPrelaunchCheck(const char* pchAppKey) override;
	const char* GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_002::EVRApplicationTransitionState state) override;
	bool IsQuitUserPromptRequested() override;
};
#include "Reimpl/BaseApplications.h"
class CVRApplications_004 : public vr::IVRApplications_004::IVRApplications, public CVRCommon {
private:
	const std::shared_ptr<BaseApplications> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRApplications_004();
	// Interface methods:
	vr::IVRApplications_004::EVRApplicationError AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) override;
	vr::IVRApplications_004::EVRApplicationError RemoveApplicationManifest(const char* pchApplicationManifestFullPath) override;
	bool IsApplicationInstalled(const char* pchAppKey) override;
	uint32_t GetApplicationCount() override;
	vr::IVRApplications_004::EVRApplicationError GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_004::EVRApplicationError GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_004::EVRApplicationError LaunchApplication(const char* pchAppKey) override;
	vr::IVRApplications_004::EVRApplicationError LaunchDashboardOverlay(const char* pchAppKey) override;
	bool CancelApplicationLaunch(const char* pchAppKey) override;
	vr::IVRApplications_004::EVRApplicationError IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) override;
	uint32_t GetApplicationProcessId(const char* pchAppKey) override;
	const char* GetApplicationsErrorNameFromEnum(vr::IVRApplications_004::EVRApplicationError error) override;
	uint32_t GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_004::EVRApplicationError* peError) override;
	bool GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, vr::IVRApplications_004::EVRApplicationError* peError) override;
	uint64_t GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, vr::IVRApplications_004::EVRApplicationError* peError) override;
	vr::IVRApplications_004::EVRApplicationError SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) override;
	bool GetApplicationAutoLaunch(const char* pchAppKey) override;
	vr::IVRApplications_004::EVRApplicationError GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_004::EVRApplicationTransitionState GetTransitionState() override;
	vr::IVRApplications_004::EVRApplicationError PerformApplicationPrelaunchCheck(const char* pchAppKey) override;
	const char* GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_004::EVRApplicationTransitionState state) override;
	bool IsQuitUserPromptRequested() override;
	vr::IVRApplications_004::EVRApplicationError LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory) override;
};
#include "Reimpl/BaseApplications.h"
class CVRApplications_005 : public vr::IVRApplications_005::IVRApplications, public CVRCommon {
private:
	const std::shared_ptr<BaseApplications> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRApplications_005();
	// Interface methods:
	vr::IVRApplications_005::EVRApplicationError AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) override;
	vr::IVRApplications_005::EVRApplicationError RemoveApplicationManifest(const char* pchApplicationManifestFullPath) override;
	bool IsApplicationInstalled(const char* pchAppKey) override;
	uint32_t GetApplicationCount() override;
	vr::IVRApplications_005::EVRApplicationError GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_005::EVRApplicationError GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_005::EVRApplicationError LaunchApplication(const char* pchAppKey) override;
	vr::IVRApplications_005::EVRApplicationError LaunchTemplateApplication(const char* pchTemplateAppKey, const char* pchNewAppKey, const vr::IVRApplications_005::AppOverrideKeys_t* pKeys, uint32_t unKeys) override;
	vr::IVRApplications_005::EVRApplicationError LaunchDashboardOverlay(const char* pchAppKey) override;
	bool CancelApplicationLaunch(const char* pchAppKey) override;
	vr::IVRApplications_005::EVRApplicationError IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) override;
	uint32_t GetApplicationProcessId(const char* pchAppKey) override;
	const char* GetApplicationsErrorNameFromEnum(vr::IVRApplications_005::EVRApplicationError error) override;
	uint32_t GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_005::EVRApplicationError* peError) override;
	bool GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, vr::IVRApplications_005::EVRApplicationError* peError) override;
	uint64_t GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, vr::IVRApplications_005::EVRApplicationError* peError) override;
	vr::IVRApplications_005::EVRApplicationError SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) override;
	bool GetApplicationAutoLaunch(const char* pchAppKey) override;
	vr::IVRApplications_005::EVRApplicationError GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_005::EVRApplicationTransitionState GetTransitionState() override;
	vr::IVRApplications_005::EVRApplicationError PerformApplicationPrelaunchCheck(const char* pchAppKey) override;
	const char* GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_005::EVRApplicationTransitionState state) override;
	bool IsQuitUserPromptRequested() override;
	vr::IVRApplications_005::EVRApplicationError LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory) override;
};
#include "Reimpl/BaseApplications.h"
class CVRApplications_006 : public vr::IVRApplications_006::IVRApplications, public CVRCommon {
private:
	const std::shared_ptr<BaseApplications> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRApplications_006();
	// Interface methods:
	vr::IVRApplications_006::EVRApplicationError AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) override;
	vr::IVRApplications_006::EVRApplicationError RemoveApplicationManifest(const char* pchApplicationManifestFullPath) override;
	bool IsApplicationInstalled(const char* pchAppKey) override;
	uint32_t GetApplicationCount() override;
	vr::IVRApplications_006::EVRApplicationError GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_006::EVRApplicationError GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_006::EVRApplicationError LaunchApplication(const char* pchAppKey) override;
	vr::IVRApplications_006::EVRApplicationError LaunchTemplateApplication(const char* pchTemplateAppKey, const char* pchNewAppKey, const vr::IVRApplications_006::AppOverrideKeys_t* pKeys, uint32_t unKeys) override;
	vr::IVRApplications_006::EVRApplicationError LaunchApplicationFromMimeType(const char* pchMimeType, const char* pchArgs) override;
	vr::IVRApplications_006::EVRApplicationError LaunchDashboardOverlay(const char* pchAppKey) override;
	bool CancelApplicationLaunch(const char* pchAppKey) override;
	vr::IVRApplications_006::EVRApplicationError IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) override;
	uint32_t GetApplicationProcessId(const char* pchAppKey) override;
	const char* GetApplicationsErrorNameFromEnum(vr::IVRApplications_006::EVRApplicationError error) override;
	uint32_t GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_006::EVRApplicationError* peError) override;
	bool GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, vr::IVRApplications_006::EVRApplicationError* peError) override;
	uint64_t GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, vr::IVRApplications_006::EVRApplicationError* peError) override;
	vr::IVRApplications_006::EVRApplicationError SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) override;
	bool GetApplicationAutoLaunch(const char* pchAppKey) override;
	vr::IVRApplications_006::EVRApplicationError SetDefaultApplicationForMimeType(const char* pchAppKey, const char* pchMimeType) override;
	bool GetDefaultApplicationForMimeType(const char* pchMimeType, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	bool GetApplicationSupportedMimeTypes(const char* pchAppKey, char* pchMimeTypesBuffer, uint32_t unMimeTypesBuffer) override;
	uint32_t GetApplicationsThatSupportMimeType(const char* pchMimeType, char* pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer) override;
	uint32_t GetApplicationLaunchArguments(uint32_t unHandle, char* pchArgs, uint32_t unArgs) override;
	vr::IVRApplications_006::EVRApplicationError GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_006::EVRApplicationTransitionState GetTransitionState() override;
	vr::IVRApplications_006::EVRApplicationError PerformApplicationPrelaunchCheck(const char* pchAppKey) override;
	const char* GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_006::EVRApplicationTransitionState state) override;
	bool IsQuitUserPromptRequested() override;
	vr::IVRApplications_006::EVRApplicationError LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory) override;
	uint32_t GetCurrentSceneProcessId() override;
};
#include "Reimpl/BaseApplications.h"
class CVRApplications_007 : public vr::IVRApplications_007::IVRApplications, public CVRCommon {
private:
	const std::shared_ptr<BaseApplications> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRApplications_007();
	// Interface methods:
	vr::IVRApplications_007::EVRApplicationError AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) override;
	vr::IVRApplications_007::EVRApplicationError RemoveApplicationManifest(const char* pchApplicationManifestFullPath) override;
	bool IsApplicationInstalled(const char* pchAppKey) override;
	uint32_t GetApplicationCount() override;
	vr::IVRApplications_007::EVRApplicationError GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_007::EVRApplicationError GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_007::EVRApplicationError LaunchApplication(const char* pchAppKey) override;
	vr::IVRApplications_007::EVRApplicationError LaunchTemplateApplication(const char* pchTemplateAppKey, const char* pchNewAppKey, const vr::IVRApplications_007::AppOverrideKeys_t* pKeys, uint32_t unKeys) override;
	vr::IVRApplications_007::EVRApplicationError LaunchApplicationFromMimeType(const char* pchMimeType, const char* pchArgs) override;
	vr::IVRApplications_007::EVRApplicationError LaunchDashboardOverlay(const char* pchAppKey) override;
	bool CancelApplicationLaunch(const char* pchAppKey) override;
	vr::IVRApplications_007::EVRApplicationError IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) override;
	uint32_t GetApplicationProcessId(const char* pchAppKey) override;
	const char* GetApplicationsErrorNameFromEnum(vr::IVRApplications_007::EVRApplicationError error) override;
	uint32_t GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_007::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_007::EVRApplicationError* peError) override;
	bool GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_007::EVRApplicationProperty eProperty, vr::IVRApplications_007::EVRApplicationError* peError) override;
	uint64_t GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_007::EVRApplicationProperty eProperty, vr::IVRApplications_007::EVRApplicationError* peError) override;
	vr::IVRApplications_007::EVRApplicationError SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) override;
	bool GetApplicationAutoLaunch(const char* pchAppKey) override;
	vr::IVRApplications_007::EVRApplicationError SetDefaultApplicationForMimeType(const char* pchAppKey, const char* pchMimeType) override;
	bool GetDefaultApplicationForMimeType(const char* pchMimeType, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	bool GetApplicationSupportedMimeTypes(const char* pchAppKey, char* pchMimeTypesBuffer, uint32_t unMimeTypesBuffer) override;
	uint32_t GetApplicationsThatSupportMimeType(const char* pchMimeType, char* pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer) override;
	uint32_t GetApplicationLaunchArguments(uint32_t unHandle, char* pchArgs, uint32_t unArgs) override;
	vr::IVRApplications_007::EVRApplicationError GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) override;
	vr::IVRApplications_007::EVRSceneApplicationState GetSceneApplicationState() override;
	vr::IVRApplications_007::EVRApplicationError PerformApplicationPrelaunchCheck(const char* pchAppKey) override;
	const char* GetSceneApplicationStateNameFromEnum(vr::IVRApplications_007::EVRSceneApplicationState state) override;
	vr::IVRApplications_007::EVRApplicationError LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory) override;
	uint32_t GetCurrentSceneProcessId() override;
};
