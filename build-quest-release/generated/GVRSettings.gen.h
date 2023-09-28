#pragma once
#include "BaseCommon.h"
#include "interfaces/IVRSettings_001.h"
#include "interfaces/IVRSettings_002.h"
#include "interfaces/IVRSettings_003.h"
#include "Reimpl/BaseSettings.h"
class CVRSettings_001 : public vr::IVRSettings_001::IVRSettings, public CVRCommon {
private:
	const std::shared_ptr<BaseSettings> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSettings_001();
	// Interface methods:
	const char* GetSettingsErrorNameFromEnum(vr::IVRSettings_001::EVRSettingsError eError) override;
	bool Sync(bool bForce, vr::IVRSettings_001::EVRSettingsError* peError) override;
	bool GetBool(const char* pchSection, const char* pchSettingsKey, bool bDefaultValue, vr::IVRSettings_001::EVRSettingsError* peError) override;
	void SetBool(const char* pchSection, const char* pchSettingsKey, bool bValue, vr::IVRSettings_001::EVRSettingsError* peError) override;
	int32_t GetInt32(const char* pchSection, const char* pchSettingsKey, int32_t nDefaultValue, vr::IVRSettings_001::EVRSettingsError* peError) override;
	void SetInt32(const char* pchSection, const char* pchSettingsKey, int32_t nValue, vr::IVRSettings_001::EVRSettingsError* peError) override;
	float GetFloat(const char* pchSection, const char* pchSettingsKey, float flDefaultValue, vr::IVRSettings_001::EVRSettingsError* peError) override;
	void SetFloat(const char* pchSection, const char* pchSettingsKey, float flValue, vr::IVRSettings_001::EVRSettingsError* peError) override;
	void GetString(const char* pchSection, const char* pchSettingsKey, char* pchValue, uint32_t unValueLen, const char* pchDefaultValue, vr::IVRSettings_001::EVRSettingsError* peError) override;
	void SetString(const char* pchSection, const char* pchSettingsKey, const char* pchValue, vr::IVRSettings_001::EVRSettingsError* peError) override;
	void RemoveSection(const char* pchSection, vr::IVRSettings_001::EVRSettingsError* peError) override;
	void RemoveKeyInSection(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_001::EVRSettingsError* peError) override;
};
#include "Reimpl/BaseSettings.h"
class CVRSettings_002 : public vr::IVRSettings_002::IVRSettings, public CVRCommon {
private:
	const std::shared_ptr<BaseSettings> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSettings_002();
	// Interface methods:
	const char* GetSettingsErrorNameFromEnum(vr::IVRSettings_002::EVRSettingsError eError) override;
	bool Sync(bool bForce, vr::IVRSettings_002::EVRSettingsError* peError) override;
	void SetBool(const char* pchSection, const char* pchSettingsKey, bool bValue, vr::IVRSettings_002::EVRSettingsError* peError) override;
	void SetInt32(const char* pchSection, const char* pchSettingsKey, int32_t nValue, vr::IVRSettings_002::EVRSettingsError* peError) override;
	void SetFloat(const char* pchSection, const char* pchSettingsKey, float flValue, vr::IVRSettings_002::EVRSettingsError* peError) override;
	void SetString(const char* pchSection, const char* pchSettingsKey, const char* pchValue, vr::IVRSettings_002::EVRSettingsError* peError) override;
	bool GetBool(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) override;
	int32_t GetInt32(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) override;
	float GetFloat(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) override;
	void GetString(const char* pchSection, const char* pchSettingsKey, char* pchValue, uint32_t unValueLen, vr::IVRSettings_002::EVRSettingsError* peError) override;
	void RemoveSection(const char* pchSection, vr::IVRSettings_002::EVRSettingsError* peError) override;
	void RemoveKeyInSection(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) override;
};
#include "Reimpl/BaseSettings.h"
class CVRSettings_003 : public vr::IVRSettings_003::IVRSettings, public CVRCommon {
private:
	const std::shared_ptr<BaseSettings> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRSettings_003();
	// Interface methods:
	const char* GetSettingsErrorNameFromEnum(vr::IVRSettings_003::EVRSettingsError eError) override;
	void SetBool(const char* pchSection, const char* pchSettingsKey, bool bValue, vr::IVRSettings_003::EVRSettingsError* peError) override;
	void SetInt32(const char* pchSection, const char* pchSettingsKey, int32_t nValue, vr::IVRSettings_003::EVRSettingsError* peError) override;
	void SetFloat(const char* pchSection, const char* pchSettingsKey, float flValue, vr::IVRSettings_003::EVRSettingsError* peError) override;
	void SetString(const char* pchSection, const char* pchSettingsKey, const char* pchValue, vr::IVRSettings_003::EVRSettingsError* peError) override;
	bool GetBool(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_003::EVRSettingsError* peError) override;
	int32_t GetInt32(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_003::EVRSettingsError* peError) override;
	float GetFloat(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_003::EVRSettingsError* peError) override;
	void GetString(const char* pchSection, const char* pchSettingsKey, char* pchValue, uint32_t unValueLen, vr::IVRSettings_003::EVRSettingsError* peError) override;
	void RemoveSection(const char* pchSection, vr::IVRSettings_003::EVRSettingsError* peError) override;
	void RemoveKeyInSection(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_003::EVRSettingsError* peError) override;
};
