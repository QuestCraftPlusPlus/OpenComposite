#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
#include "vrtrackedcameratypes.h"
// ivroverlay.h
namespace vr
{
namespace IVROverlay_007
{

	/** The maximum length of an overlay key in bytes, counting the terminating null character. */
	static const uint32_t k_unVROverlayMaxKeyLength = 128;

	/** The maximum length of an overlay name in bytes, counting the terminating null character. */
	static const uint32_t k_unVROverlayMaxNameLength = 128;

	/** The maximum number of overlays that can exist in the system at one time. */
	static const uint32_t k_unMaxOverlayCount = 32;

	/** Types of input supported by VR Overlays */
	enum VROverlayInputMethod
	{
		VROverlayInputMethod_None		= 0, // No input events will be generated automatically for this overlay
		VROverlayInputMethod_Mouse		= 1, // Tracked controllers will get mouse events automatically
	};

	/** Allows the caller to figure out which overlay transform getter to call. */
	enum VROverlayTransformType
	{
		VROverlayTransform_Absolute					= 0,
		VROverlayTransform_TrackedDeviceRelative	= 1,
		VROverlayTransform_SystemOverlay			= 2,
	};

	/** Overlay control settings */
	enum VROverlayFlags
	{
		VROverlayFlags_None			= 0,

		// The following only take effect when rendered using the high quality render path (see SetHighQualityOverlay).
		VROverlayFlags_Curved		= 1,
		VROverlayFlags_RGSS4X		= 2,

		// Set this flag on a dashboard overlay to prevent a tab from showing up for that overlay
		VROverlayFlags_NoDashboardTab = 3,

		// Set this flag on a dashboard that is able to deal with gamepad focus events
		VROverlayFlags_AcceptsGamepadEvents = 4,

		// Indicates that the overlay should dim/brighten to show gamepad focus
		VROverlayFlags_ShowGamepadFocus = 5,

	};

	struct VROverlayIntersectionParams_t
	{
		HmdVector3_t vSource;
		HmdVector3_t vDirection;
		ETrackingUniverseOrigin eOrigin;
	};

	struct VROverlayIntersectionResults_t
	{
		HmdVector3_t vPoint;
		HmdVector3_t vNormal;
		HmdVector2_t vUVs;
		float fDistance;
	};

	// Input modes for the Big Picture gamepad text entry
	enum EGamepadTextInputMode
	{
		k_EGamepadTextInputModeNormal = 0,
		k_EGamepadTextInputModePassword = 1
	};


	// Controls number of allowed lines for the Big Picture gamepad text entry
	enum EGamepadTextInputLineMode
	{
		k_EGamepadTextInputLineModeSingleLine = 0,
		k_EGamepadTextInputLineModeMultipleLines = 1
	};

	/** Directions for changing focus between overlays with the gamepad */
	enum EOverlayDirection
	{
		OverlayDirection_Up = 0,
		OverlayDirection_Down = 1,
		OverlayDirection_Left = 2,
		OverlayDirection_Right = 3,
		
		OverlayDirection_Count = 4,
	};

	class IVROverlay
	{
	public:

		// ---------------------------------------------
		// Overlay management methods
		// ---------------------------------------------

		/** Finds an existing overlay with the specified key. */
		virtual EVROverlayError FindOverlay( const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle ) = 0;

		/** Creates a new named overlay. All overlays start hidden and with default settings. */
		virtual EVROverlayError CreateOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pOverlayHandle ) = 0;

		/** Destroys the specified overlay. When an application calls VR_Shutdown all overlays created by that app are
		* automatically destroyed. */
		virtual EVROverlayError DestroyOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Specify which overlay to use the high quality render path.  This overlay will be composited in during the distortion pass which
		* results in it drawing on top of everything else, but also at a higher quality as it samples the source texture directly rather than
		* rasterizing into each eye's render texture first.  Because if this, only one of these is supported at any given time.  It is most useful
		* for overlays that are expected to take up most of the user's view (e.g. streaming video). */
		virtual EVROverlayError SetHighQualityOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Returns the overlay handle of the current overlay being rendered using the single high quality overlay render path.
		* Otherwise it will return k_ulOverlayHandleInvalid. */
		virtual VROverlayHandle_t GetHighQualityOverlay() = 0;

		/** Fills the provided buffer with the string key of the overlay. Returns the size of buffer required to store the key, including
		* the terminating null character. k_unVROverlayMaxKeyLength will be enough bytes to fit the string. */
		virtual uint32_t GetOverlayKey( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError = 0L ) = 0;

		/** Fills the provided buffer with the friendly name of the overlay. Returns the size of buffer required to store the key, including
		* the terminating null character. k_unVROverlayMaxNameLength will be enough bytes to fit the string. */
		virtual uint32_t GetOverlayName( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError = 0L ) = 0;

		/** Gets the raw image data from an overlay. Overlay image data is always returned as RGBA data, 4 bytes per pixel. If the buffer is not large enough, width and height 
		* will be set and VROverlayError_ArrayTooSmall is returned. */
		virtual EVROverlayError GetOverlayImageData( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight ) = 0;

		/** returns a string that corresponds with the specified overlay error. The string will be the name 
		* of the error enum value for all valid error codes */
		virtual const char *GetOverlayErrorNameFromEnum( EVROverlayError error ) = 0;


		// ---------------------------------------------
		// Overlay rendering methods
		// ---------------------------------------------

		/** Specify flag setting for a given overlay */
		virtual EVROverlayError SetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled ) = 0;

		/** Sets flag setting for a given overlay */
		virtual EVROverlayError GetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled ) = 0;

		/** Sets the color tint of the overlay quad. Use 0.0 to 1.0 per channel. */
		virtual EVROverlayError SetOverlayColor( VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue ) = 0;

		/** Gets the color tint of the overlay quad. */
		virtual EVROverlayError GetOverlayColor( VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue ) = 0;

		/** Sets the alpha of the overlay quad. Use 1.0 for 100 percent opacity to 0.0 for 0 percent opacity. */
		virtual EVROverlayError SetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float fAlpha ) = 0;

		/** Gets the alpha of the overlay quad. By default overlays are rendering at 100 percent alpha (1.0). */
		virtual EVROverlayError GetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float *pfAlpha ) = 0;

		/** Sets the width of the overlay quad in meters. By default overlays are rendered on a quad that is 1 meter across */
		virtual EVROverlayError SetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float fWidthInMeters ) = 0;

		/** Returns the width of the overlay quad in meters. By default overlays are rendered on a quad that is 1 meter across */
		virtual EVROverlayError GetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters ) = 0;

		/** For high-quality curved overlays only, sets the distance range in meters from the overlay used to automatically curve
		* the surface around the viewer.  Min is distance is when the surface will be most curved.  Max is when least curved. */
		virtual EVROverlayError SetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters ) = 0;

		/** For high-quality curved overlays only, gets the distance range in meters from the overlay used to automatically curve
		* the surface around the viewer.  Min is distance is when the surface will be most curved.  Max is when least curved. */
		virtual EVROverlayError GetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters ) = 0;

		/** Sets the colorspace the overlay texture's data is in.  Defaults to 'auto'.
		* If the texture needs to be resolved, you should call SetOverlayTexture with the appropriate colorspace instead. */
		virtual EVROverlayError SetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace ) = 0;

		/** Gets the overlay's current colorspace setting. */
		virtual EVROverlayError GetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace ) = 0;

		/** Sets the part of the texture to use for the overlay. UV Min is the upper left corner and UV Max is the lower right corner. */
		virtual EVROverlayError SetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds ) = 0;

		/** Gets the part of the texture to use for the overlay. UV Min is the upper left corner and UV Max is the lower right corner. */
		virtual EVROverlayError GetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds ) = 0;

		/** Returns the transform type of this overlay. */
		virtual EVROverlayError GetOverlayTransformType( VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType ) = 0;

		/** Sets the transform to absolute tracking origin. */
		virtual EVROverlayError SetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform ) = 0;

		/** Gets the transform if it is absolute. Returns an error if the transform is some other type. */
		virtual EVROverlayError GetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform ) = 0;

		/** Sets the transform to relative to the transform of the specified tracked device. */
		virtual EVROverlayError SetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform ) = 0;

		/** Gets the transform if it is relative to a tracked device. Returns an error if the transform is some other type. */
		virtual EVROverlayError GetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform ) = 0;

		/** Shows the VR overlay.  For dashboard overlays, only the Dashboard Manager is allowed to call this. */
		virtual EVROverlayError ShowOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Hides the VR overlay.  For dashboard overlays, only the Dashboard Manager is allowed to call this. */
		virtual EVROverlayError HideOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Returns true if the overlay is visible. */
		virtual bool IsOverlayVisible( VROverlayHandle_t ulOverlayHandle ) = 0;


		// ---------------------------------------------
		// Overlay input methods
		// ---------------------------------------------

		/** Returns true and fills the event with the next event on the overlay's event queue, if there is one. 
		* If there are no events this method returns false */
		virtual bool PollNextOverlayEvent( VROverlayHandle_t ulOverlayHandle, VREvent_t *pEvent ) = 0;

		/** Returns the current input settings for the specified overlay. */
		virtual EVROverlayError GetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod ) = 0;

		/** Sets the input settings for the specified overlay. */
		virtual EVROverlayError SetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod ) = 0;

		/** Gets the mouse scaling factor that is used for mouse events. The actual texture may be a different size, but this is
		* typically the size of the underlying UI in pixels. */
		virtual EVROverlayError GetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale ) = 0;

		/** Sets the mouse scaling factor that is used for mouse events. The actual texture may be a different size, but this is
		* typically the size of the underlying UI in pixels. */
		virtual EVROverlayError SetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale ) = 0;

		/** Computes the overlay-space pixel coordinates of where the ray intersects the overlay with the
		* specified settings. Returns false if there is no intersection. */
		virtual bool ComputeOverlayIntersection( VROverlayHandle_t ulOverlayHandle, const VROverlayIntersectionParams_t *pParams, VROverlayIntersectionResults_t *pResults ) = 0;

		/** Processes mouse input from the specified controller as though it were a mouse pointed at a compositor overlay with the
		* specified settings. The controller is treated like a laser pointer on the -z axis. The point where the laser pointer would
		* intersect with the overlay is the mouse position, the trigger is left mouse, and the track pad is right mouse. 
		*
		* Return true if the controller is pointed at the overlay and an event was generated. */
		virtual bool HandleControllerOverlayInteractionAsMouse( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex ) = 0;

		/** Returns true if the specified overlay is the hover target. An overlay is the hover target when it is the last overlay "moused over" 
		* by the virtual mouse pointer */
		virtual bool IsHoverTargetOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Returns the current Gamepad focus overlay */
		virtual VROverlayHandle_t GetGamepadFocusOverlay() = 0;

		/** Sets the current Gamepad focus overlay */
		virtual EVROverlayError SetGamepadFocusOverlay( VROverlayHandle_t ulNewFocusOverlay ) = 0;

		/** Sets an overlay's neighbor. This will also set the neighbor of the "to" overlay
		* to point back to the "from" overlay. If an overlay's neighbor is set to invalid both
		* ends will be cleared */
		virtual EVROverlayError SetOverlayNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo ) = 0;

		/** Changes the Gamepad focus from one overlay to one of its neighbors. Returns VROverlayError_NoNeighbor if there is no
		* neighbor in that direction */
		virtual EVROverlayError MoveGamepadFocusToNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom ) = 0;

		// ---------------------------------------------
		// Overlay texture methods
		// ---------------------------------------------

		/** Texture to draw for the overlay. IVRCompositor::SetGraphicsDevice must be called before 
		* this function. This function can only be called by the overlay's renderer process.
		*
		* If pBounds is NULL the entire texture will be used.
		*
		* OpenGL dirty state:
		*	glBindTexture
		*/
		virtual EVROverlayError SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture ) = 0;

		/** Use this to tell the overlay system to release the texture set for this overlay. */
		virtual EVROverlayError ClearOverlayTexture( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Separate interface for providing the data as a stream of bytes, but there is an upper bound on data 
		* that can be sent. This function can only be called by the overlay's renderer process. */
		virtual EVROverlayError SetOverlayRaw( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth ) = 0;

		/** Separate interface for providing the image through a filename: can be png or jpg, and should not be bigger than 1920x1080.
		* This function can only be called by the overlay's renderer process */
		virtual EVROverlayError SetOverlayFromFile( VROverlayHandle_t ulOverlayHandle, const char *pchFilePath ) = 0;

		// ----------------------------------------------
		// Dashboard Overlay Methods
		// ----------------------------------------------

		/** Creates a dashboard overlay and returns its handle */
		virtual EVROverlayError CreateDashboardOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle ) = 0;

		/** Returns true if the dashboard is visible */
		virtual bool IsDashboardVisible() = 0;

		/** returns true if the dashboard is visible and the specified overlay is the active system Overlay */
		virtual bool IsActiveDashboardOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Sets the dashboard overlay to only appear when the specified process ID has scene focus */
		virtual EVROverlayError SetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId ) = 0;

		/** Gets the process ID that this dashboard overlay requires to have scene focus */
		virtual EVROverlayError GetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId ) = 0;

		/** Shows the dashboard. */
		virtual void ShowDashboard( const char *pchOverlayToShow ) = 0;

		// ---------------------------------------------
		// Keyboard methods
		// ---------------------------------------------
		
		/** Show the virtual keyboard to accept input **/
		virtual EVROverlayError ShowKeyboard( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue ) = 0;

		virtual EVROverlayError ShowKeyboardForOverlay( VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue ) = 0;

		/** Get the text that was entered into the text input **/
		virtual uint32_t GetKeyboardText( VR_OUT_STRING() char *pchText, uint32_t cchText ) = 0;

		/** Hide the virtual keyboard **/
		virtual void HideKeyboard() = 0;

	};

	static const char * const IVROverlay_Version = "IVROverlay_007";

} // namespace vr

} // Close custom namespace
