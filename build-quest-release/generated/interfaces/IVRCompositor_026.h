#pragma once
#include "openvr.h"
#include "version.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrcompositor.h
namespace vr
{
namespace IVRCompositor_026
{

#pragma pack( push, 8 )

/** Errors that can occur with the VR compositor */
enum EVRCompositorError
{
	VRCompositorError_None						= 0,
	VRCompositorError_RequestFailed				= 1,
	VRCompositorError_IncompatibleVersion		= 100,
	VRCompositorError_DoNotHaveFocus			= 101,
	VRCompositorError_InvalidTexture			= 102,
	VRCompositorError_IsNotSceneApplication		= 103,
	VRCompositorError_TextureIsOnWrongDevice	= 104,
	VRCompositorError_TextureUsesUnsupportedFormat = 105,
	VRCompositorError_SharedTexturesNotSupported = 106,
	VRCompositorError_IndexOutOfRange			= 107,
	VRCompositorError_AlreadySubmitted			= 108,
	VRCompositorError_InvalidBounds				= 109,
	VRCompositorError_AlreadySet				= 110,
};

/** Timing mode passed to SetExplicitTimingMode(); see that function for documentation */
enum EVRCompositorTimingMode
{
	VRCompositorTimingMode_Implicit											= 0,
	VRCompositorTimingMode_Explicit_RuntimePerformsPostPresentHandoff		= 1,
	VRCompositorTimingMode_Explicit_ApplicationPerformsPostPresentHandoff	= 2,
};

/** Cumulative stats for current application.  These are not cleared until a new app connects,
* but they do stop accumulating once the associated app disconnects. */
struct Compositor_CumulativeStats
{
	uint32_t m_nPid; // Process id associated with these stats (may no longer be running).
	uint32_t m_nNumFramePresents; // total number of times we called present (includes reprojected frames)
	uint32_t m_nNumDroppedFrames; // total number of times an old frame was re-scanned out (without reprojection)
	uint32_t m_nNumReprojectedFrames; // total number of times a frame was scanned out a second time (with reprojection)

	/** Values recorded at startup before application has fully faded in the first time. */
	uint32_t m_nNumFramePresentsOnStartup;
	uint32_t m_nNumDroppedFramesOnStartup;
	uint32_t m_nNumReprojectedFramesOnStartup;

	/** Applications may explicitly fade to the compositor.  This is usually to handle level transitions, and loading often causes
	* system wide hitches.  The following stats are collected during this period.  Does not include values recorded during startup. */
	uint32_t m_nNumLoading;
	uint32_t m_nNumFramePresentsLoading;
	uint32_t m_nNumDroppedFramesLoading;
	uint32_t m_nNumReprojectedFramesLoading;

	/** If we don't get a new frame from the app in less than 2.5 frames, then we assume the app has hung and start
	* fading back to the compositor.  The following stats are a result of this, and are a subset of those recorded above.
	* Does not include values recorded during start up or loading. */
	uint32_t m_nNumTimedOut;
	uint32_t m_nNumFramePresentsTimedOut;
	uint32_t m_nNumDroppedFramesTimedOut;
	uint32_t m_nNumReprojectedFramesTimedOut;
};

struct Compositor_StageRenderSettings
{
	/** Primary color is applied as a tint to (i.e. multiplied with) the model's texture */
	HmdColor_t m_PrimaryColor;
	HmdColor_t m_SecondaryColor;

	/** Vignette radius is in meters and is used to fade to the specified secondary solid color over
	* that 3D distance from the origin of the playspace. */
	float m_flVignetteInnerRadius;
	float m_flVignetteOuterRadius;

	/** Fades to the secondary color based on view incidence.  This variable controls the linearity
	* of the effect.  It is mutually exclusive with vignette.  Additionally, it treats the mesh as faceted. */
	float m_flFresnelStrength;

	/** Controls backface culling. */
	bool m_bBackfaceCulling;

	/** Converts the render model's texture to luma and applies to rgb equally.  This is useful to
	* combat compression artifacts that can occur on desaturated source material. */
	bool m_bGreyscale;

	/** Renders mesh as a wireframe. */
	bool m_bWireframe;
};

static inline Compositor_StageRenderSettings DefaultStageRenderSettings()
{
	Compositor_StageRenderSettings settings;
	settings.m_PrimaryColor.r = 1.0f;
	settings.m_PrimaryColor.g = 1.0f;
	settings.m_PrimaryColor.b = 1.0f;
	settings.m_PrimaryColor.a = 1.0f;
	settings.m_SecondaryColor.r = 1.0f;
	settings.m_SecondaryColor.g = 1.0f;
	settings.m_SecondaryColor.b = 1.0f;
	settings.m_SecondaryColor.a = 1.0f;
	settings.m_flVignetteInnerRadius = 0.0f;
	settings.m_flVignetteOuterRadius = 0.0f;
	settings.m_flFresnelStrength = 0.0f;
	settings.m_bBackfaceCulling = false;
	settings.m_bGreyscale = false;
	settings.m_bWireframe = false;
	return settings;
}

#pragma pack( pop )

/** Allows the application to interact with the compositor */
class IVRCompositor
{
public:
	/** Sets tracking space returned by WaitGetPoses */
	virtual void SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) = 0;

	/** Gets current tracking space returned by WaitGetPoses */
	virtual ETrackingUniverseOrigin GetTrackingSpace() = 0;

	/** Scene applications should call this function to get poses to render with (and optionally poses predicted an additional frame out to use for gameplay).
	* This function will block until "running start" milliseconds before the start of the frame, and should be called at the last moment before needing to
	* start rendering.
	*
	* Return codes:
	*	- IsNotSceneApplication (make sure to call VR_Init with VRApplicaiton_Scene)
	*	- DoNotHaveFocus (some other app has taken focus - this will throttle the call to 10hz to reduce the impact on that app)
	*/
	virtual EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;

	/** Get the last set of poses returned by WaitGetPoses. */
	virtual EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;

	/** Interface for accessing last set of poses returned by WaitGetPoses one at a time.
	* Returns VRCompositorError_IndexOutOfRange if unDeviceIndex not less than k_unMaxTrackedDeviceCount otherwise VRCompositorError_None.
	* It is okay to pass NULL for either pose if you only want one of the values. */
	virtual EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose ) = 0;

	/** Updated scene texture to display. If pBounds is NULL the entire texture will be used.  If called from an OpenGL app, consider adding a glFlush after
	* Submitting both frames to signal the driver to start processing, otherwise it may wait until the command buffer fills up, causing the app to miss frames.
	*
	* OpenGL dirty state:
	*	glBindTexture
	*
	* Return codes:
	*	- IsNotSceneApplication (make sure to call VR_Init with VRApplicaiton_Scene)
	*	- DoNotHaveFocus (some other app has taken focus)
	*	- TextureIsOnWrongDevice (application did not use proper AdapterIndex - see IVRSystem.GetDXGIOutputInfo)
	*	- SharedTexturesNotSupported (application needs to call CreateDXGIFactory1 or later before creating DX device)
	*	- TextureUsesUnsupportedFormat (scene textures must be compatible with DXGI sharing rules - e.g. uncompressed, no mips, etc.)
	*	- InvalidTexture (usually means bad arguments passed in)
	*	- AlreadySubmitted (app has submitted two left textures or two right textures in a single frame - i.e. before calling WaitGetPoses again)
	*/
	virtual EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds = 0, EVRSubmitFlags nSubmitFlags = Submit_Default ) = 0;

	/** Clears the frame that was sent with the last call to Submit. This will cause the 
	* compositor to show the grid until Submit is called again. */
	virtual void ClearLastSubmittedFrame() = 0;

	/** Call immediately after presenting your app's window (i.e. companion window) to unblock the compositor.
	* This is an optional call, which only needs to be used if you can't instead call WaitGetPoses immediately after Present.
	* For example, if your engine's render and game loop are not on separate threads, or blocking the render thread until 3ms before the next vsync would
	* introduce a deadlock of some sort.  This function tells the compositor that you have finished all rendering after having Submitted buffers for both
	* eyes, and it is free to start its rendering work.  This should only be called from the same thread you are rendering on. */
	virtual void PostPresentHandoff() = 0;

	/** Returns true if timing data is filled it.  Sets oldest timing info if nFramesAgo is larger than the stored history.
	* Be sure to set timing.size = sizeof(Compositor_FrameTiming) on struct passed in before calling this function. */
	virtual bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo = 0 ) = 0;

	/** Interface for copying a range of timing data.  Frames are returned in ascending order (oldest to newest) with the last being the most recent frame.
	* Only the first entry's m_nSize needs to be set, as the rest will be inferred from that.  Returns total number of entries filled out. */
	virtual uint32_t GetFrameTimings( VR_ARRAY_COUNT( nFrames ) Compositor_FrameTiming *pTiming, uint32_t nFrames ) = 0;

	/** Returns the time in seconds left in the current (as identified by FrameTiming's frameIndex) frame.
	* Due to "running start", this value may roll over to the next frame before ever reaching 0.0. */
	virtual float GetFrameTimeRemaining() = 0;

	/** Fills out stats accumulated for the last connected application.  Pass in sizeof( Compositor_CumulativeStats ) as second parameter. */
	virtual void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes ) = 0;

	/** Fades the view on the HMD to the specified color. The fade will take fSeconds, and the color values are between
	* 0.0 and 1.0. This color is faded on top of the scene based on the alpha parameter. Removing the fade color instantly 
	* would be FadeToColor( 0.0, 0.0, 0.0, 0.0, 0.0 ).  Values are in un-premultiplied alpha space. */
	virtual void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false ) = 0;

	/** Get current fade color value. */
	virtual HmdColor_t GetCurrentFadeColor( bool bBackground = false ) = 0;

	/** Fading the Grid in or out in fSeconds */
	virtual void FadeGrid( float fSeconds, bool bFadeIn ) = 0;

	/** Get current alpha value of grid. */
	virtual float GetCurrentGridAlpha() = 0;

	/** Override the skybox used in the compositor (e.g. for during level loads when the app can't feed scene images fast enough)
	* Order is Front, Back, Left, Right, Top, Bottom.  If only a single texture is passed, it is assumed in lat-long format.
	* If two are passed, it is assumed a lat-long stereo pair. */
	virtual EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount ) = 0;

	/** Resets compositor skybox back to defaults. */
	virtual void ClearSkyboxOverride() = 0;

	/** Brings the compositor window to the front. This is useful for covering any other window that may be on the HMD
	* and is obscuring the compositor window. */
	virtual void CompositorBringToFront() = 0;

	/** Pushes the compositor window to the back. This is useful for allowing other applications to draw directly to the HMD. */
	virtual void CompositorGoToBack() = 0;

	/** Tells the compositor process to clean up and exit. You do not need to call this function at shutdown. Under normal 
	* circumstances the compositor will manage its own life cycle based on what applications are running. */
	virtual void CompositorQuit() = 0;
	
	/** Return whether the compositor is fullscreen */
	virtual bool IsFullscreen() = 0;

	/** Returns the process ID of the process that is currently rendering the scene */
	virtual uint32_t GetCurrentSceneFocusProcess() = 0;

	/** Returns the process ID of the process that rendered the last frame (or 0 if the compositor itself rendered the frame.)
	* Returns 0 when fading out from an app and the app's process Id when fading into an app. */
	virtual uint32_t GetLastFrameRenderer() = 0;

	/** Returns true if the current process has the scene focus */
	virtual bool CanRenderScene() = 0;

	/** DEPRECATED: Opens the headset view (as either a window or docked widget depending on user's preferences) that displays what the user
	* sees in the headset. */
	virtual void ShowMirrorWindow() = 0;

	/** DEPRECATED: Closes the headset view, either as a window or docked widget. */
	virtual void HideMirrorWindow() = 0;

	/** DEPRECATED: Returns true if the headset view (either as a window or docked widget) is shown. */
	virtual bool IsMirrorWindowVisible() = 0;

	/** Writes back buffer and stereo left/right pair from the application to a 'screenshots' folder in the SteamVR runtime root. */
	virtual void CompositorDumpImages() = 0;

	/** Let an app know it should be rendering with low resources. */
	virtual bool ShouldAppRenderWithLowResources() = 0;

	/** Override interleaved reprojection logic to force on. */
	virtual void ForceInterleavedReprojectionOn( bool bOverride ) = 0;

	/** Force reconnecting to the compositor process. */
	virtual void ForceReconnectProcess() = 0;

	/** Temporarily suspends rendering (useful for finer control over scene transitions). */
	virtual void SuspendRendering( bool bSuspend ) = 0;

	/** Opens a shared D3D11 texture with the undistorted composited image for each eye.  Use ReleaseMirrorTextureD3D11 when finished
	* instead of calling Release on the resource itself. */
	virtual EVRCompositorError GetMirrorTextureD3D11( EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView ) = 0;
	virtual void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView ) = 0;

	/** Access to mirror textures from OpenGL. */
	virtual EVRCompositorError GetMirrorTextureGL( EVREye eEye, glUInt_t *pglTextureId, glSharedTextureHandle_t *pglSharedTextureHandle ) = 0;
	virtual bool ReleaseSharedGLTexture( glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	virtual void LockGLSharedTextureForAccess( glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	virtual void UnlockGLSharedTextureForAccess( glSharedTextureHandle_t glSharedTextureHandle ) = 0;

	/** [Vulkan Only]
	* return 0. Otherwise it returns the length of the number of bytes necessary to hold this string including the trailing
	* null.  The string will be a space separated list of-required instance extensions to enable in VkCreateInstance */
	virtual uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;

	/** [Vulkan only]
	* return 0. Otherwise it returns the length of the number of bytes necessary to hold this string including the trailing
	* null.  The string will be a space separated list of required device extensions to enable in VkCreateDevice */
	virtual uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;

	/** [ Vulkan/D3D12 Only ]
	* There are two purposes for SetExplicitTimingMode:
	*	1. To get a more accurate GPU timestamp for when the frame begins in Vulkan/D3D12 applications.
	*	2. (Optional) To avoid having WaitGetPoses access the Vulkan queue so that the queue can be accessed from
	*	another thread while WaitGetPoses is executing.
	*
	* More accurate GPU timestamp for the start of the frame is achieved by the application calling
	* SubmitExplicitTimingData immediately before its first submission to the Vulkan/D3D12 queue.
	* This is more accurate because normally this GPU timestamp is recorded during WaitGetPoses.  In D3D11, 
	* WaitGetPoses queues a GPU timestamp write, but it does not actually get submitted to the GPU until the 
	* application flushes.  By using SubmitExplicitTimingData, the timestamp is recorded at the same place for 
	* Vulkan/D3D12 as it is for D3D11, resulting in a more accurate GPU time measurement for the frame.
	*
	* Avoiding WaitGetPoses accessing the Vulkan queue can be achieved using SetExplicitTimingMode as well.  If this is desired,
	* the application should set the timing mode to Explicit_ApplicationPerformsPostPresentHandoff and *MUST* call PostPresentHandoff
	* itself. If these conditions are met, then WaitGetPoses is guaranteed not to access the queue.  Note that PostPresentHandoff
	* and SubmitExplicitTimingData will access the queue, so only WaitGetPoses becomes safe for accessing the queue from another
	* thread. */
	virtual void SetExplicitTimingMode( EVRCompositorTimingMode eTimingMode ) = 0;

	/** [ Vulkan/D3D12 Only ]
	* Submit explicit timing data.  When SetExplicitTimingMode is true, this must be called immediately before
	* the application's first vkQueueSubmit (Vulkan) or ID3D12CommandQueue::ExecuteCommandLists (D3D12) of each frame.
	* This function will insert a GPU timestamp write just before the application starts its rendering.  This function
	* will perform a vkQueueSubmit on Vulkan so must not be done simultaneously with VkQueue operations on another thread.
	* Returns VRCompositorError_RequestFailed if SetExplicitTimingMode is not enabled. */
	virtual EVRCompositorError SubmitExplicitTimingData() = 0;

	/** Indicates whether or not motion smoothing is enabled by the user settings.
	* If you want to know if motion smoothing actually triggered due to a late frame, check Compositor_FrameTiming
	* m_nReprojectionFlags & VRCompositor_ReprojectionMotion instead. */
	virtual bool IsMotionSmoothingEnabled() = 0;

	/** Indicates whether or not motion smoothing is supported by the current hardware. */
	virtual bool IsMotionSmoothingSupported() = 0;

	/** Indicates whether or not the current scene focus app is currently loading.  This is inferred from its use of FadeGrid to
	* explicitly fade to the compositor to cover up the fact that it cannot render at a sustained full framerate during this time. */
	virtual bool IsCurrentSceneFocusAppLoading() = 0;

	/** Override the stage model used in the compositor to replace the grid.  RenderModelPath is a full path the an OBJ file to load.
	* This file will be loaded asynchronously from disk and uploaded to the gpu by the runtime.  Once ready for rendering, the
	* VREvent StageOverrideReady will be sent.  Use FadeToGrid to reveal.  Call ClearStageOverride to free the associated resources when finished. */
	virtual EVRCompositorError SetStageOverride_Async( const char *pchRenderModelPath, const HmdMatrix34_t *pTransform = 0,
		const Compositor_StageRenderSettings *pRenderSettings = 0, uint32_t nSizeOfRenderSettings = 0 ) = 0;

	/** Resets the stage to its default user specified setting. */
	virtual void ClearStageOverride() = 0;

	/** Returns true if pBenchmarkResults is filled it.  Sets pBenchmarkResults with the result of the compositor benchmark.
	* nSizeOfBenchmarkResults should be set to sizeof(Compositor_BenchmarkResults) */
	virtual bool GetCompositorBenchmarkResults( Compositor_BenchmarkResults *pBenchmarkResults, uint32_t nSizeOfBenchmarkResults ) = 0;

	/** Returns the frame id associated with the poses last returned by WaitGetPoses.  Deltas between IDs correspond to number of headset vsync intervals. */
	virtual EVRCompositorError GetLastPosePredictionIDs( uint32_t *pRenderPosePredictionID, uint32_t *pGamePosePredictionID ) = 0;

	/** Get the most up-to-date predicted (or recorded - up to 100ms old) set of poses for a given frame id. */
	virtual EVRCompositorError GetPosesForFrame( uint32_t unPosePredictionID, VR_ARRAY_COUNT( unPoseArrayCount ) TrackedDevicePose_t* pPoseArray, uint32_t unPoseArrayCount ) = 0;
};

static const char * const IVRCompositor_Version = "IVRCompositor_026";

} // namespace vr



} // Close custom namespace
