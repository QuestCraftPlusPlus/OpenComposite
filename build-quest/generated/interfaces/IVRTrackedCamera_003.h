#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrtrackedcamera.h
namespace vr
{
namespace IVRTrackedCamera_003
{

class IVRTrackedCamera
{
public:
	/** Returns a string for an error */
	virtual const char *GetCameraErrorNameFromEnum( EVRTrackedCameraError eCameraError ) = 0;

	/** For convenience, same as tracked property request Prop_HasCamera_Bool */
	virtual EVRTrackedCameraError HasCamera( TrackedDeviceIndex_t nDeviceIndex, bool *pHasCamera ) = 0;

	/** Gets size of the image frame. */
	virtual EVRTrackedCameraError GetCameraFrameSize( TrackedDeviceIndex_t nDeviceIndex, EVRTrackedCameraFrameType eFrameType, uint32_t *pnWidth, uint32_t *pnHeight, uint32_t *pnFrameBufferSize ) = 0;

	virtual EVRTrackedCameraError GetCameraIntrinsics( TrackedDeviceIndex_t nDeviceIndex, EVRTrackedCameraFrameType eFrameType, HmdVector2_t *pFocalLength, HmdVector2_t *pCenter ) = 0;

	virtual EVRTrackedCameraError GetCameraProjection( TrackedDeviceIndex_t nDeviceIndex, EVRTrackedCameraFrameType eFrameType, float flZNear, float flZFar, HmdMatrix44_t *pProjection ) = 0;

	/** Acquiring streaming service permits video streaming for the caller. Releasing hints the system that video services do not need to be maintained for this client.
	* If the camera has not already been activated, a one time spin up may incur some auto exposure as well as initial streaming frame delays.
	* The camera should be considered a global resource accessible for shared consumption but not exclusive to any caller.
	* The camera may go inactive due to lack of active consumers or headset idleness. */
	virtual EVRTrackedCameraError AcquireVideoStreamingService( TrackedDeviceIndex_t nDeviceIndex, TrackedCameraHandle_t *pHandle ) = 0;
	virtual EVRTrackedCameraError ReleaseVideoStreamingService( TrackedCameraHandle_t hTrackedCamera ) = 0;

	/** Copies the image frame into a caller's provided buffer. The image data is currently provided as RGBA data, 4 bytes per pixel.
	* A caller can provide null for the framebuffer or frameheader if not desired. Requesting the frame header first, followed by the frame buffer allows
	* the caller to determine if the frame as advanced per the frame header sequence. 
	* If there is no frame available yet, due to initial camera spinup or re-activation, the error will be VRTrackedCameraError_NoFrameAvailable.
	* Ideally a caller should be polling at ~16ms intervals */
	virtual EVRTrackedCameraError GetVideoStreamFrameBuffer( TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, void *pFrameBuffer, uint32_t nFrameBufferSize, CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize ) = 0;

	/** Gets size of the image frame. */
	virtual EVRTrackedCameraError GetVideoStreamTextureSize( TrackedDeviceIndex_t nDeviceIndex, EVRTrackedCameraFrameType eFrameType, VRTextureBounds_t *pTextureBounds, uint32_t *pnWidth, uint32_t *pnHeight ) = 0; 

	/** Access a shared D3D11 texture for the specified tracked camera stream.
	* The camera frame type VRTrackedCameraFrameType_Undistorted is not supported directly as a shared texture. It is an interior subregion of the shared texture VRTrackedCameraFrameType_MaximumUndistorted.
	* Instead, use GetVideoStreamTextureSize() with VRTrackedCameraFrameType_Undistorted to determine the proper interior subregion bounds along with GetVideoStreamTextureD3D11() with
	* VRTrackedCameraFrameType_MaximumUndistorted to provide the texture. The VRTrackedCameraFrameType_MaximumUndistorted will yield an image where the invalid regions are decoded
	* by the alpha channel having a zero component. The valid regions all have a non-zero alpha component. The subregion as described by VRTrackedCameraFrameType_Undistorted 
	* guarantees a rectangle where all pixels are valid. */
	virtual EVRTrackedCameraError GetVideoStreamTextureD3D11( TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize ) = 0;

	/** Access a shared GL texture for the specified tracked camera stream */
	virtual EVRTrackedCameraError GetVideoStreamTextureGL( TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, glUInt_t *pglTextureId, CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize ) = 0;
	virtual EVRTrackedCameraError ReleaseVideoStreamTextureGL( TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId ) = 0;
};

static const char * const IVRTrackedCamera_Version = "IVRTrackedCamera_003";

} // namespace vr


} // Close custom namespace
