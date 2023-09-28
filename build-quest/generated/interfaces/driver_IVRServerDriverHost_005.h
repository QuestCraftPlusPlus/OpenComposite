#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
#include "driver_ITrackedDeviceServerDriver_005.h"
#include "vrtrackedcameratypes.h"
// ivrserverdriverhost.h
namespace vr
{
namespace driver_IVRServerDriverHost_005
{

/** This interface is provided by vrserver to allow the driver to notify 
* the system when something changes about a device. These changes must
* not change the serial number or class of the device because those values
* are permanently associated with the device's index. */
class IVRServerDriverHost
{
public:
	/** Notifies the server that a tracked device has been added. If this function returns true
	* the server will call Activate on the device. If it returns false some kind of error
	* has occurred and the device will not be activated. */
	virtual bool TrackedDeviceAdded( const char *pchDeviceSerialNumber, ETrackedDeviceClass eDeviceClass, vr::driver_ITrackedDeviceServerDriver_005::ITrackedDeviceServerDriver *pDriver ) = 0;

	/** Notifies the server that a tracked device's pose has been updated */
	virtual void TrackedDevicePoseUpdated( uint32_t unWhichDevice, const vr::driver_ITrackedDeviceServerDriver_005::DriverPose_t & newPose, uint32_t unPoseStructSize ) = 0;

	/** Notifies the server that vsync has occurred on the the display attached to the device. This is
	* only permitted on devices of the HMD class. */
	virtual void VsyncEvent( double vsyncTimeOffsetSeconds ) = 0;

	/** Sends a vendor specific event (VREvent_VendorSpecific_Reserved_Start..VREvent_VendorSpecific_Reserved_End */
	virtual void VendorSpecificEvent( uint32_t unWhichDevice, EVREventType eventType, const VREvent_Data_t & eventData, double eventTimeOffset ) = 0;

	/** Returns true if SteamVR is exiting */
	virtual bool IsExiting() = 0;

	/** Returns true and fills the event with the next event on the queue if there is one. If there are no events
	* this method returns false. uncbVREvent should be the size in bytes of the VREvent_t struct */
	virtual bool PollNextEvent( VREvent_t *pEvent, uint32_t uncbVREvent ) = 0;

	/** Provides access to device poses for drivers.  Poses are in their "raw" tracking space which is uniquely
	* defined by each driver providing poses for its devices.  It is up to clients of this function to correlate
	* poses across different drivers.  Poses are indexed by their device id, and their associated driver and
	* other properties can be looked up via IVRProperties. */
	virtual void GetRawTrackedDevicePoses( float fPredictedSecondsFromNow, TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount ) = 0;

	/** Notifies the server that a tracked device's display component transforms have been updated. */
	virtual void TrackedDeviceDisplayTransformUpdated( uint32_t unWhichDevice, HmdMatrix34_t eyeToHeadLeft, HmdMatrix34_t eyeToHeadRight ) = 0;
};

static const char *IVRServerDriverHost_Version = "IVRServerDriverHost_005";

}

} // Close custom namespace