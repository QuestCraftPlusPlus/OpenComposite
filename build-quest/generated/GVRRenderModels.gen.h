#pragma once
#include "BaseCommon.h"
#include "interfaces/IVRRenderModels_002.h"
#include "interfaces/IVRRenderModels_004.h"
#include "interfaces/IVRRenderModels_005.h"
#include "interfaces/IVRRenderModels_006.h"
#include "Reimpl/BaseRenderModels.h"
class CVRRenderModels_002 : public vr::IVRRenderModels_002::IVRRenderModels, public CVRCommon {
private:
	const std::shared_ptr<BaseRenderModels> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRRenderModels_002();
	// Interface methods:
	bool LoadRenderModel(const char* pchRenderModelName, vr::IVRRenderModels_002::RenderModel_t** ppRenderModel) override;
	void FreeRenderModel(vr::IVRRenderModels_002::RenderModel_t* pRenderModel) override;
	bool LoadTexture(vr::IVRRenderModels_002::TextureID_t textureId, vr::IVRRenderModels_002::RenderModel_TextureMap_t** ppTexture) override;
	void FreeTexture(vr::IVRRenderModels_002::RenderModel_TextureMap_t* pTexture) override;
	uint32_t GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen) override;
	uint32_t GetRenderModelCount() override;
	uint32_t GetComponentCount(const char* pchRenderModelName) override;
	uint32_t GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen) override;
	uint64_t GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName) override;
	uint32_t GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) override;
	bool GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, vr::IVRRenderModels_002::RenderModel_ComponentState_t* pComponentState) override;
};
#include "Reimpl/BaseRenderModels.h"
class CVRRenderModels_004 : public vr::IVRRenderModels_004::IVRRenderModels, public CVRCommon {
private:
	const std::shared_ptr<BaseRenderModels> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRRenderModels_004();
	// Interface methods:
	vr::IVRRenderModels_004::EVRRenderModelError LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_004::RenderModel_t** ppRenderModel) override;
	void FreeRenderModel(vr::IVRRenderModels_004::RenderModel_t* pRenderModel) override;
	vr::IVRRenderModels_004::EVRRenderModelError LoadTexture_Async(vr::IVRRenderModels_004::TextureID_t textureId, vr::IVRRenderModels_004::RenderModel_TextureMap_t** ppTexture) override;
	void FreeTexture(vr::IVRRenderModels_004::RenderModel_TextureMap_t* pTexture) override;
	vr::IVRRenderModels_004::EVRRenderModelError LoadTextureD3D11_Async(vr::IVRRenderModels_004::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D) override;
	void FreeTextureD3D11(void* pD3D11Texture2D) override;
	uint32_t GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen) override;
	uint32_t GetRenderModelCount() override;
	uint32_t GetComponentCount(const char* pchRenderModelName) override;
	uint32_t GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen) override;
	uint64_t GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName) override;
	uint32_t GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) override;
	bool GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_004::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_004::RenderModel_ComponentState_t* pComponentState) override;
	bool RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName) override;
};
#include "Reimpl/BaseRenderModels.h"
class CVRRenderModels_005 : public vr::IVRRenderModels_005::IVRRenderModels, public CVRCommon {
private:
	const std::shared_ptr<BaseRenderModels> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRRenderModels_005();
	// Interface methods:
	vr::IVRRenderModels_005::EVRRenderModelError LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_005::RenderModel_t** ppRenderModel) override;
	void FreeRenderModel(vr::IVRRenderModels_005::RenderModel_t* pRenderModel) override;
	vr::IVRRenderModels_005::EVRRenderModelError LoadTexture_Async(vr::IVRRenderModels_005::TextureID_t textureId, vr::IVRRenderModels_005::RenderModel_TextureMap_t** ppTexture) override;
	void FreeTexture(vr::IVRRenderModels_005::RenderModel_TextureMap_t* pTexture) override;
	vr::IVRRenderModels_005::EVRRenderModelError LoadTextureD3D11_Async(vr::IVRRenderModels_005::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D) override;
	vr::IVRRenderModels_005::EVRRenderModelError LoadIntoTextureD3D11_Async(vr::IVRRenderModels_005::TextureID_t textureId, void* pDstTexture) override;
	void FreeTextureD3D11(void* pD3D11Texture2D) override;
	uint32_t GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen) override;
	uint32_t GetRenderModelCount() override;
	uint32_t GetComponentCount(const char* pchRenderModelName) override;
	uint32_t GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen) override;
	uint64_t GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName) override;
	uint32_t GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) override;
	bool GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_005::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_005::RenderModel_ComponentState_t* pComponentState) override;
	bool RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName) override;
	uint32_t GetRenderModelThumbnailURL(const char* pchRenderModelName, char* pchThumbnailURL, uint32_t unThumbnailURLLen, vr::IVRRenderModels_005::EVRRenderModelError* peError) override;
	uint32_t GetRenderModelOriginalPath(const char* pchRenderModelName, char* pchOriginalPath, uint32_t unOriginalPathLen, vr::IVRRenderModels_005::EVRRenderModelError* peError) override;
	const char* GetRenderModelErrorNameFromEnum(vr::IVRRenderModels_005::EVRRenderModelError error) override;
};
#include "Reimpl/BaseRenderModels.h"
class CVRRenderModels_006 : public vr::IVRRenderModels_006::IVRRenderModels, public CVRCommon {
private:
	const std::shared_ptr<BaseRenderModels> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRRenderModels_006();
	// Interface methods:
	vr::IVRRenderModels_006::EVRRenderModelError LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_006::RenderModel_t** ppRenderModel) override;
	void FreeRenderModel(vr::IVRRenderModels_006::RenderModel_t* pRenderModel) override;
	vr::IVRRenderModels_006::EVRRenderModelError LoadTexture_Async(vr::IVRRenderModels_006::TextureID_t textureId, vr::IVRRenderModels_006::RenderModel_TextureMap_t** ppTexture) override;
	void FreeTexture(vr::IVRRenderModels_006::RenderModel_TextureMap_t* pTexture) override;
	vr::IVRRenderModels_006::EVRRenderModelError LoadTextureD3D11_Async(vr::IVRRenderModels_006::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D) override;
	vr::IVRRenderModels_006::EVRRenderModelError LoadIntoTextureD3D11_Async(vr::IVRRenderModels_006::TextureID_t textureId, void* pDstTexture) override;
	void FreeTextureD3D11(void* pD3D11Texture2D) override;
	uint32_t GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen) override;
	uint32_t GetRenderModelCount() override;
	uint32_t GetComponentCount(const char* pchRenderModelName) override;
	uint32_t GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen) override;
	uint64_t GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName) override;
	uint32_t GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) override;
	bool GetComponentStateForDevicePath(const char* pchRenderModelName, const char* pchComponentName, vr::VRInputValueHandle_t devicePath, const vr::IVRRenderModels_006::RenderModel_ControllerMode_State_t* pState, vr::RenderModel_ComponentState_t* pComponentState) override;
	bool GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_006::RenderModel_ControllerMode_State_t* pState, vr::RenderModel_ComponentState_t* pComponentState) override;
	bool RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName) override;
	uint32_t GetRenderModelThumbnailURL(const char* pchRenderModelName, char* pchThumbnailURL, uint32_t unThumbnailURLLen, vr::IVRRenderModels_006::EVRRenderModelError* peError) override;
	uint32_t GetRenderModelOriginalPath(const char* pchRenderModelName, char* pchOriginalPath, uint32_t unOriginalPathLen, vr::IVRRenderModels_006::EVRRenderModelError* peError) override;
	const char* GetRenderModelErrorNameFromEnum(vr::IVRRenderModels_006::EVRRenderModelError error) override;
};
