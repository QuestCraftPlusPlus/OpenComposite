#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
#include "vrtrackedcameratypes.h"
// ivrtrackedcamera.h
namespace vr
{
namespace IVRTrackedCamera_001
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

#pragma pack( pop )

class IVRTrackedCamera
{
public:
	virtual bool HasCamera( TrackedDeviceIndex_t nDeviceIndex ) = 0;
	virtual bool GetCameraFirmwareDescription( TrackedDeviceIndex_t nDeviceIndex, char *pBuffer, uint32_t nBufferLen ) = 0;

	// An invalid or unsupported format returns false. Frame dimensions imply sensor size.
	virtual bool GetCameraFrameDimensions( TrackedDeviceIndex_t nDeviceIndex, ECameraVideoStreamFormat nVideoStreamFormat, uint32_t *pWidth, uint32_t *pHeight ) = 0;

	// Caller can request a specific streaming format prior to enable. The request may be ignored if camera has been granted exclusive use by lower level systems.
	// Format cannot be changed after camera has been enabled. An unsupported or rejected format returns false.
	// Use CVS_FORMAT_UNKNOWN for defaults.
	virtual bool SetCameraVideoStreamFormat( TrackedDeviceIndex_t nDeviceIndex, ECameraVideoStreamFormat nVideoStreamFormat ) = 0;
	virtual ECameraVideoStreamFormat GetCameraVideoStreamFormat( TrackedDeviceIndex_t nDeviceIndex ) = 0;

	// Camera must be enabled prior to streaming. Enabling causes frame buffering allocations and locks attributes.
	virtual bool EnableCameraForStreaming( TrackedDeviceIndex_t nDeviceIndex, bool bEnable ) = 0;

	virtual bool StartVideoStream( TrackedDeviceIndex_t nDeviceIndex ) = 0;
	virtual bool StopVideoStream( TrackedDeviceIndex_t nDeviceIndex ) = 0;
	virtual bool IsVideoStreamActive( TrackedDeviceIndex_t nDeviceIndex ) = 0;

	// Starts at 0 and advances in seconds when stream started and valid. A stopped stream returns 0. 
	// A paused stream is still considered active and the elapsed time advances.
	virtual float GetVideoStreamElapsedTime( TrackedDeviceIndex_t nDeviceIndex ) = 0;

	// Caller acquires ref-counted frames for exclusive use and releases when finished. Failure to release frames degrades frame buffering.
	// NULL implies no frame available.
	virtual const CameraVideoStreamFrame_t *GetVideoStreamFrame( TrackedDeviceIndex_t nDeviceIndex ) = 0;
	virtual bool ReleaseVideoStreamFrame( TrackedDeviceIndex_t nDeviceIndex, const CameraVideoStreamFrame_t *pFrameImage ) = 0;

	virtual bool SetAutoExposure( TrackedDeviceIndex_t nDeviceIndex, bool bEnable ) = 0;

	// A stream can only be paused after it is started. The pause state is cleared after stopping.
	// The camera may not support pause/resume semantics due to HW limitations.
	virtual bool SupportsPauseResume( TrackedDeviceIndex_t nDeviceIndex ) = 0;
	virtual bool PauseVideoStream( TrackedDeviceIndex_t nDeviceIndex ) = 0;
	virtual bool ResumeVideoStream( TrackedDeviceIndex_t nDeviceIndex ) = 0;
	virtual bool IsVideoStreamPaused( TrackedDeviceIndex_t nDeviceIndex ) = 0;

	virtual bool GetCameraDistortion( TrackedDeviceIndex_t nDeviceIndex, float flInputU, float flInputV, float *pflOutputU, float *pflOutputV ) = 0;
	virtual bool GetCameraProjection( TrackedDeviceIndex_t nDeviceIndex, float flWidthPixels, float flHeightPixels, float flZNear, float flZFar, HmdMatrix44_t *pProjection ) = 0;
};

static const char * const IVRTrackedCamera_Version = "IVRTrackedCamera_001";

}
} // Close custom namespace
