#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
#include "vrtrackedcameratypes.h"
// ivrcompositor.h
namespace vr
{
namespace IVRCompositor_009
{

#if defined(__linux__) || defined(__APPLE__) 
	// The 32-bit version of gcc has the alignment requirement for uint64 and double set to
	// 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
	// The 64-bit version of gcc has the alignment requirement for these types set to
	// 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
	// The 64-bit structure packing has to match the 32-bit structure packing for each platform.
	#pragma pack( push, 4 )
#else
	#pragma pack( push, 8 )
#endif

/** Errors that can occur with the VR compositor */
enum EVRCompositorError
{
	VRCompositorError_None						= 0,
	VRCompositorError_IncompatibleVersion		= 100,
	VRCompositorError_DoNotHaveFocus			= 101,
	VRCompositorError_InvalidTexture			= 102,
	VRCompositorError_IsNotSceneApplication		= 103,
	VRCompositorError_TextureIsOnWrongDevice	= 104,
	VRCompositorError_TextureUsesUnsupportedFormat = 105,
};


/** Provides a single frame's timing information to the app */
struct Compositor_FrameTiming
{
	uint32_t size; // sizeof(Compositor_FrameTiming)
	double frameStart;
	float frameVSync; // seconds from frame start
	uint32_t droppedFrames;
	uint32_t frameIndex;
	TrackedDevicePose_t pose;

	float prediction;

	float m_flFrameIntervalMs;
	float m_flSceneRenderCpuMs;
	float m_flSceneRenderGpuMs;
	float m_flCompositorRenderCpuMs;
	float m_flCompositorRenderGpuMs;
	float m_flPresentCallCpuMs;
	float m_flRunningStartMs;
	float m_flHandoffStartMs;
	float m_flHandoffEndMs;
};


#pragma pack( pop )


/** Allows the application to interact with the compositor */
class IVRCompositor
{
public:
	/** Sets tracking space returned by WaitGetPoses */
	virtual void SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) = 0;

	/** Gets current tracking space returned by WaitGetPoses */
	virtual ETrackingUniverseOrigin GetTrackingSpace() = 0;

	/** Returns pose(s) to use to render scene (and optionally poses predicted two frames out for gameplay). */
	virtual EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;

	/** Get the last set of poses returned by WaitGetPoses. */
	virtual EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;

	/** Updated scene texture to display. If pBounds is NULL the entire texture will be used.  If called from an OpenGL app, consider adding a glFlush after
	* Submitting both frames to signal the driver to start processing, otherwise it may wait until the command buffer fills up, causing the app to miss frames.
	*
	* OpenGL dirty state:
	*	glBindTexture
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

	/** Returns the time in seconds left in the current (as identified by FrameTiming's frameIndex) frame.
	* Due to "running start", this value may roll over to the next frame before ever reaching 0.0. */
	virtual float GetFrameTimeRemaining() = 0;

	/** Fades the view on the HMD to the specified color. The fade will take fSeconds, and the color values are between
	* 0.0 and 1.0. This color is faded on top of the scene based on the alpha parameter. Removing the fade color instantly 
	* would be FadeToColor( 0.0, 0.0, 0.0, 0.0, 0.0 ).  Values are in un-premultiplied alpha space. */
	virtual void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false ) = 0;

	/** Fading the Grid in or out in fSeconds */
	virtual void FadeGrid( float fSeconds, bool bFadeIn ) = 0;

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

	/** Creates a window on the primary monitor to display what is being shown in the headset. */
	virtual void ShowMirrorWindow() = 0;

	/** Closes the mirror window. */
	virtual void HideMirrorWindow() = 0;

	/** Returns true if the mirror window is shown */
	virtual bool IsMirrorWindowVisible() = 0;

	/** Writes all images that the compositor knows about (including overlays) to a 'screenshots' folder in the SteamVR runtime root. */
	virtual void CompositorDumpImages() = 0;
};

static const char * const IVRCompositor_Version = "IVRCompositor_009";

} // namespace vr



} // Close custom namespace
