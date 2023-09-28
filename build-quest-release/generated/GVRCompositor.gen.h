#pragma once
#include "BaseCommon.h"
#include "interfaces/IVRCompositor_009.h"
#include "interfaces/IVRCompositor_012.h"
#include "interfaces/IVRCompositor_013.h"
#include "interfaces/IVRCompositor_014.h"
#include "interfaces/IVRCompositor_015.h"
#include "interfaces/IVRCompositor_016.h"
#include "custom_interfaces/IVRCompositor_017.h"
#include "interfaces/IVRCompositor_018.h"
#include "interfaces/IVRCompositor_019.h"
#include "interfaces/IVRCompositor_020.h"
#include "interfaces/IVRCompositor_021.h"
#include "interfaces/IVRCompositor_022.h"
#include "interfaces/IVRCompositor_024.h"
#include "interfaces/IVRCompositor_026.h"
#include "interfaces/IVRCompositor_027.h"
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_009 : public vr::IVRCompositor_009::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_009();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_009::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_009::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_009::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_009::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	float GetFrameTimeRemaining() override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	vr::IVRCompositor_009::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_012 : public vr::IVRCompositor_012::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_012();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_012::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_012::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_012::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_012::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_012::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	float GetFrameTimeRemaining() override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	vr::IVRCompositor_012::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_013 : public vr::IVRCompositor_013::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_013();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_013::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_013::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_013::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_013::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_013::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	float GetFrameTimeRemaining() override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	vr::IVRCompositor_013::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_014 : public vr::IVRCompositor_014::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_014();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_014::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_014::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_014::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_014::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_014::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	float GetFrameTimeRemaining() override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	vr::IVRCompositor_014::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_015 : public vr::IVRCompositor_015::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_015();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_015::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_015::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_015::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_015::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_015::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_015::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	vr::IVRCompositor_015::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_015::EVRCompositorError RequestScreenshot(vr::EVRScreenshotType type, const char* pchDestinationFileName, const char* pchVRDestinationFileName) override;
	vr::EVRScreenshotType GetCurrentScreenshotType() override;
	vr::IVRCompositor_015::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	vr::IVRCompositor_015::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_016 : public vr::IVRCompositor_016::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_016();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_016::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_016::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_016::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_016::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_016::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_016::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	vr::IVRCompositor_016::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_016::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	vr::IVRCompositor_016::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_017 : public vr::IVRCompositor_017::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_017();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_017::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_017::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_017::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_017::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_017::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	uint32_t GetFrameTimings(vr::IVRCompositor_017::Compositor_FrameTiming* pTiming, uint32_t nFrames) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_017::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	vr::IVRCompositor_017::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_017::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	vr::IVRCompositor_017::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_018 : public vr::IVRCompositor_018::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_018();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_018::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_018::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_018::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_018::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_018::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	uint32_t GetFrameTimings(vr::IVRCompositor_018::Compositor_FrameTiming* pTiming, uint32_t nFrames) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_018::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	float GetCurrentGridAlpha() override;
	vr::IVRCompositor_018::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_018::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	vr::IVRCompositor_018::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_019 : public vr::IVRCompositor_019::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_019();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_019::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_019::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_019::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_019::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_019::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	uint32_t GetFrameTimings(vr::IVRCompositor_019::Compositor_FrameTiming* pTiming, uint32_t nFrames) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_019::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	float GetCurrentGridAlpha() override;
	vr::IVRCompositor_019::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_019::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	vr::IVRCompositor_019::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) override;
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_020 : public vr::IVRCompositor_020::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_020();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_020::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_020::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_020::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_020::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_020::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	uint32_t GetFrameTimings(vr::IVRCompositor_020::Compositor_FrameTiming* pTiming, uint32_t nFrames) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_020::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	float GetCurrentGridAlpha() override;
	vr::IVRCompositor_020::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_020::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	void ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) override;
	vr::IVRCompositor_020::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) override;
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_021 : public vr::IVRCompositor_021::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_021();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_021::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_021::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_021::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_021::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::IVRCompositor_021::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	uint32_t GetFrameTimings(vr::IVRCompositor_021::Compositor_FrameTiming* pTiming, uint32_t nFrames) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_021::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	float GetCurrentGridAlpha() override;
	vr::IVRCompositor_021::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_021::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	void ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) override;
	vr::IVRCompositor_021::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) override;
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) override;
	void SetExplicitTimingMode(bool bExplicitTimingMode) override;
	vr::IVRCompositor_021::EVRCompositorError SubmitExplicitTimingData() override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_022 : public vr::IVRCompositor_022::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_022();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_022::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_022::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_022::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_022::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	uint32_t GetFrameTimings(vr::Compositor_FrameTiming* pTiming, uint32_t nFrames) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_022::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	float GetCurrentGridAlpha() override;
	vr::IVRCompositor_022::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_022::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	void ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) override;
	vr::IVRCompositor_022::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) override;
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) override;
	void SetExplicitTimingMode(vr::IVRCompositor_022::EVRCompositorTimingMode eTimingMode) override;
	vr::IVRCompositor_022::EVRCompositorError SubmitExplicitTimingData() override;
	bool IsMotionSmoothingEnabled() override;
	bool IsMotionSmoothingSupported() override;
	bool IsCurrentSceneFocusAppLoading() override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_024 : public vr::IVRCompositor_024::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_024();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_024::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_024::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_024::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_024::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	uint32_t GetFrameTimings(vr::Compositor_FrameTiming* pTiming, uint32_t nFrames) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_024::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	float GetCurrentGridAlpha() override;
	vr::IVRCompositor_024::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_024::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	void ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) override;
	vr::IVRCompositor_024::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) override;
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) override;
	void SetExplicitTimingMode(vr::IVRCompositor_024::EVRCompositorTimingMode eTimingMode) override;
	vr::IVRCompositor_024::EVRCompositorError SubmitExplicitTimingData() override;
	bool IsMotionSmoothingEnabled() override;
	bool IsMotionSmoothingSupported() override;
	bool IsCurrentSceneFocusAppLoading() override;
	vr::IVRCompositor_024::EVRCompositorError SetStageOverride_Async(const char* pchRenderModelPath, const vr::HmdMatrix34_t* pTransform, const vr::IVRCompositor_024::Compositor_StageRenderSettings* pRenderSettings, uint32_t nSizeOfRenderSettings) override;
	void ClearStageOverride() override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_026 : public vr::IVRCompositor_026::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_026();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_026::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_026::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_026::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_026::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	uint32_t GetFrameTimings(vr::Compositor_FrameTiming* pTiming, uint32_t nFrames) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_026::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeIn) override;
	float GetCurrentGridAlpha() override;
	vr::IVRCompositor_026::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_026::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	void ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) override;
	vr::IVRCompositor_026::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) override;
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) override;
	void SetExplicitTimingMode(vr::IVRCompositor_026::EVRCompositorTimingMode eTimingMode) override;
	vr::IVRCompositor_026::EVRCompositorError SubmitExplicitTimingData() override;
	bool IsMotionSmoothingEnabled() override;
	bool IsMotionSmoothingSupported() override;
	bool IsCurrentSceneFocusAppLoading() override;
	vr::IVRCompositor_026::EVRCompositorError SetStageOverride_Async(const char* pchRenderModelPath, const vr::HmdMatrix34_t* pTransform, const vr::IVRCompositor_026::Compositor_StageRenderSettings* pRenderSettings, uint32_t nSizeOfRenderSettings) override;
	void ClearStageOverride() override;
	bool GetCompositorBenchmarkResults(vr::Compositor_BenchmarkResults* pBenchmarkResults, uint32_t nSizeOfBenchmarkResults) override;
	vr::IVRCompositor_026::EVRCompositorError GetLastPosePredictionIDs(uint32_t* pRenderPosePredictionID, uint32_t* pGamePosePredictionID) override;
	vr::IVRCompositor_026::EVRCompositorError GetPosesForFrame(uint32_t unPosePredictionID, vr::TrackedDevicePose_t* pPoseArray, uint32_t unPoseArrayCount) override;
};
#include "Reimpl/BaseCompositor.h"
class CVRCompositor_027 : public vr::IVRCompositor_027::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRCompositor_027();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) override;
	vr::ETrackingUniverseOrigin GetTrackingSpace() override;
	vr::IVRCompositor_027::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_027::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) override;
	vr::IVRCompositor_027::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) override;
	vr::IVRCompositor_027::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) override;
	void ClearLastSubmittedFrame() override;
	void PostPresentHandoff() override;
	bool GetFrameTiming(vr::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) override;
	uint32_t GetFrameTimings(vr::Compositor_FrameTiming* pTiming, uint32_t nFrames) override;
	float GetFrameTimeRemaining() override;
	void GetCumulativeStats(vr::IVRCompositor_027::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) override;
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) override;
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground) override;
	void FadeGrid(float fSeconds, bool bFadeGridIn) override;
	float GetCurrentGridAlpha() override;
	vr::IVRCompositor_027::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) override;
	void ClearSkyboxOverride() override;
	void CompositorBringToFront() override;
	void CompositorGoToBack() override;
	void CompositorQuit() override;
	bool IsFullscreen() override;
	uint32_t GetCurrentSceneFocusProcess() override;
	uint32_t GetLastFrameRenderer() override;
	bool CanRenderScene() override;
	void ShowMirrorWindow() override;
	void HideMirrorWindow() override;
	bool IsMirrorWindowVisible() override;
	void CompositorDumpImages() override;
	bool ShouldAppRenderWithLowResources() override;
	void ForceInterleavedReprojectionOn(bool bOverride) override;
	void ForceReconnectProcess() override;
	void SuspendRendering(bool bSuspend) override;
	vr::IVRCompositor_027::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) override;
	void ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) override;
	vr::IVRCompositor_027::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) override;
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) override;
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) override;
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) override;
	void SetExplicitTimingMode(vr::IVRCompositor_027::EVRCompositorTimingMode eTimingMode) override;
	vr::IVRCompositor_027::EVRCompositorError SubmitExplicitTimingData() override;
	bool IsMotionSmoothingEnabled() override;
	bool IsMotionSmoothingSupported() override;
	bool IsCurrentSceneFocusAppLoading() override;
	vr::IVRCompositor_027::EVRCompositorError SetStageOverride_Async(const char* pchRenderModelPath, const vr::HmdMatrix34_t* pTransform, const vr::IVRCompositor_027::Compositor_StageRenderSettings* pRenderSettings, uint32_t nSizeOfRenderSettings) override;
	void ClearStageOverride() override;
	bool GetCompositorBenchmarkResults(vr::Compositor_BenchmarkResults* pBenchmarkResults, uint32_t nSizeOfBenchmarkResults) override;
	vr::IVRCompositor_027::EVRCompositorError GetLastPosePredictionIDs(uint32_t* pRenderPosePredictionID, uint32_t* pGamePosePredictionID) override;
	vr::IVRCompositor_027::EVRCompositorError GetPosesForFrame(uint32_t unPosePredictionID, vr::TrackedDevicePose_t* pPoseArray, uint32_t unPoseArrayCount) override;
};
