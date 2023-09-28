#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrscreenshots.h

namespace vr
{
namespace IVRScreenshots_001
{

/** Errors that can occur with the VR compositor */
enum EVRScreenshotError
{
	VRScreenshotError_None							= 0,
	VRScreenshotError_RequestFailed					= 1,
	VRScreenshotError_IncompatibleVersion			= 100,
	VRScreenshotError_NotFound						= 101,
	VRScreenshotError_BufferTooSmall				= 102,
	VRScreenshotError_ScreenshotAlreadyInProgress	= 108,
};

/** Allows the application to generate screenshots */
class IVRScreenshots
{
public:
	/** Request a screenshot of the requested type.
	 *  A request of the VRScreenshotType_Stereo type will always
	 *  work. Other types will depend on the underlying application
	 *  support.
	 *  The first file name is for the preview image and should be a
	 *  regular screenshot (ideally from the left eye). The second
	 *  is the VR screenshot in the correct format. They should be
	 *  in the same aspect ratio.  Formats per type:
	 *  VRScreenshotType_Mono: the VR filename is ignored (can be
	 *  nullptr), this is a normal flat single shot.
	 *  VRScreenshotType_Stereo:  The VR image should be a
	 *  side-by-side with the left eye image on the left.
	 *  VRScreenshotType_Cubemap: The VR image should be six square
	 *  images composited horizontally.
	 *  VRScreenshotType_StereoPanorama: above/below with left eye
	 *  panorama being the above image.  Image is typically square
	 *  with the panorama being 2x horizontal.
	 *
	 *  Note that the VR dashboard will call this function when
	 *  the user presses the screenshot binding (currently System
	 *  Button + Trigger).  If Steam is running, the destination
	 *  file names will be in %TEMP% and will be copied into
	 *  Steam's screenshot library for the running application
	 *  once SubmitScreenshot() is called.
	 *  If Steam is not running, the paths will be in the user's
	 *  documents folder under Documents\SteamVR\Screenshots.
	 *  Other VR applications can call this to initiate a
	 *  screenshot outside of user control.
	 *  The destination file names do not need an extension,
	 *  will be replaced with the correct one for the format
	 *  which is currently .png. */
	virtual EVRScreenshotError RequestScreenshot( ScreenshotHandle_t *pOutScreenshotHandle, EVRScreenshotType type, const char *pchPreviewFilename, const char *pchVRFilename ) = 0;

	/** Called by the running VR application to indicate that it
	 *  wishes to be in charge of screenshots.  If the
	 *  application does not call this, the Compositor will only
	 *  support VRScreenshotType_Stereo screenshots that will be
	 *  captured without notification to the running app.
	 *  Once hooked your application will receive a
	 *  VREvent_RequestScreenshot event when the user presses the
	 *  buttons to take a screenshot. */
	virtual EVRScreenshotError HookScreenshot( VR_ARRAY_COUNT( numTypes ) const EVRScreenshotType *pSupportedTypes, int numTypes ) = 0;

	/** When your application receives a
	 *  VREvent_RequestScreenshot event, call these functions to get
	 *  the details of the screenshot request. */
	virtual EVRScreenshotType GetScreenshotPropertyType( ScreenshotHandle_t screenshotHandle, EVRScreenshotError *pError ) = 0;

	/** Get the filename for the preview or vr image (see
	 *  EScreenshotPropertyFilenames).  The return value is
	 *  the size of the string.   */
 	virtual uint32_t GetScreenshotPropertyFilename( ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, VR_OUT_STRING() char *pchFilename, uint32_t cchFilename, EVRScreenshotError *pError ) = 0;

	/** Call this if the application is taking the screen shot
	 *  will take more than a few ms processing. This will result
	 *  in an overlay being presented that shows a completion
	 *  bar. */
	virtual EVRScreenshotError UpdateScreenshotProgress( ScreenshotHandle_t screenshotHandle, float flProgress ) = 0;

	/** Tells the compositor to take an internal screenshot of
	 *  type VRScreenshotType_Stereo. It will take the current
	 *  submitted scene textures of the running application and
	 *  write them into the preview image and a side-by-side file
	 *  for the VR image.
	 *  This is similar to request screenshot, but doesn't ever
	 *  talk to the application, just takes the shot and submits. */
	virtual EVRScreenshotError TakeStereoScreenshot( ScreenshotHandle_t *pOutScreenshotHandle, const char *pchPreviewFilename, const char *pchVRFilename ) = 0;

	/** Submit the completed screenshot.  If Steam is running
	 *  this will call into the Steam client and upload the
	 *  screenshot to the screenshots section of the library for
	 *  the running application.  If Steam is not running, this
	 *  function will display a notification to the user that the
	 *  screenshot was taken. The paths should be full paths with
	 *  extensions.
	 *  File paths should be absolute including extensions.
	 *  screenshotHandle can be k_unScreenshotHandleInvalid if this
	 *  was a new shot taking by the app to be saved and not
	 *  initiated by a user (achievement earned or something) */
	virtual EVRScreenshotError SubmitScreenshot( ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, const char *pchSourcePreviewFilename, const char *pchSourceVRFilename ) = 0;
};

static const char * const IVRScreenshots_Version = "IVRScreenshots_001";

} // namespace vr



} // Close custom namespace
