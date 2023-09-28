#pragma once
#include "openvr.h"
#include "version.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrsystem.h
namespace vr
{
namespace IVRSystem_021
{

class IVRSystem
{
public:


	// ------------------------------------
	// Display Methods
	// ------------------------------------

	/** Suggested size for the intermediate render target that the distortion pulls from. */
	virtual void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight ) = 0;

	/** The projection matrix for the specified eye */
	virtual HmdMatrix44_t GetProjectionMatrix( EVREye eEye, float fNearZ, float fFarZ ) = 0;

	/** The components necessary to build your own projection matrix in case your
	* application is doing something fancy like infinite Z */
	virtual void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) = 0;

	/** Gets the result of the distortion function for the specified eye and input UVs. UVs go from 0,0 in 
	* the upper left of that eye's viewport and 1,1 in the lower right of that eye's viewport.
	* Returns true for success. Otherwise, returns false, and distortion coordinates are not suitable. */
	virtual bool ComputeDistortion( EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates ) = 0;

	/** Returns the transform from eye space to the head space. Eye space is the per-eye flavor of head
	* space that provides stereo disparity. Instead of Model * View * Projection the sequence is Model * View * Eye^-1 * Projection. 
	* Normally View and Eye^-1 will be multiplied together and treated as View in your application. 
	*/
	virtual HmdMatrix34_t GetEyeToHeadTransform( EVREye eEye ) = 0;

	/** Returns the number of elapsed seconds since the last recorded vsync event. This 
	*	will come from a vsync timer event in the timer if possible or from the application-reported
	*   time if that is not available. If no vsync times are available the function will 
	*   return zero for vsync time and frame counter and return false from the method. */
	virtual bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter ) = 0;

	/** [D3D9 Only]
	* Returns the adapter index that the user should pass into CreateDevice to set up D3D9 in such
	* a way that it can go full screen exclusive on the HMD. Returns -1 if there was an error.
	*/
	virtual int32_t GetD3D9AdapterIndex() = 0;

	/** [D3D10/11 Only]
	* Returns the adapter index that the user should pass into EnumAdapters to create the device 
	* and swap chain in DX10 and DX11. If an error occurs the index will be set to -1.
	*/
	virtual void GetDXGIOutputInfo( int32_t *pnAdapterIndex ) = 0;
	
	/**
	 * Returns platform- and texture-type specific adapter identification so that applications and the
	 * compositor are creating textures and swap chains on the same GPU. If an error occurs the device
	 * will be set to 0.
	 * pInstance is an optional parameter that is required only when textureType is TextureType_Vulkan.
	 * [D3D10/11/12 Only (D3D9 Not Supported)]
	 *  Returns the adapter LUID that identifies the GPU attached to the HMD. The user should
	 *  enumerate all adapters using IDXGIFactory::EnumAdapters and IDXGIAdapter::GetDesc to find
	 *  the adapter with the matching LUID, or use IDXGIFactory4::EnumAdapterByLuid.
	 *  The discovered IDXGIAdapter should be used to create the device and swap chain.
	 * [Vulkan Only]
	 *  Returns the VkPhysicalDevice that should be used by the application.
	 *  pInstance must be the instance the application will use to query for the VkPhysicalDevice.  The application
	 *  must create the VkInstance with extensions returned by IVRCompositor::GetVulkanInstanceExtensionsRequired enabled.
	 * [macOS Only]
	 *  For TextureType_IOSurface returns the id<MTLDevice> that should be used by the application.
	 *  On 10.13+ for TextureType_OpenGL returns the 'registryId' of the renderer which should be used
	 *   by the application. See Apple Technical Q&A QA1168 for information on enumerating GL Renderers, and the
	 *   new kCGLRPRegistryIDLow and kCGLRPRegistryIDHigh CGLRendererProperty values in the 10.13 SDK.
	 *  Pre 10.13 for TextureType_OpenGL returns 0, as there is no dependable way to correlate the HMDs MTLDevice
	 *   with a GL Renderer.
	 */
	virtual void GetOutputDevice( uint64_t *pnDevice, ETextureType textureType, VkInstance_T *pInstance = nullptr ) = 0;

	// ------------------------------------
	// Display Mode methods
	// ------------------------------------

	/** Use to determine if the headset display is part of the desktop (i.e. extended) or hidden (i.e. direct mode). */
	virtual bool IsDisplayOnDesktop() = 0;

	/** Set the display visibility (true = extended, false = direct mode).  Return value of true indicates that the change was successful. */
	virtual bool SetDisplayVisibility( bool bIsVisibleOnDesktop ) = 0;

	// ------------------------------------
	// Tracking Methods
	// ------------------------------------

	/** The pose that the tracker thinks that the HMD will be in at the specified number of seconds into the 
	* future. Pass 0 to get the state at the instant the method is called. Most of the time the application should
	* calculate the time until the photons will be emitted from the display and pass that time into the method.
	*
	* This is roughly analogous to the inverse of the view matrix in most applications, though 
	* many games will need to do some additional rotation or translation on top of the rotation
	* and translation provided by the head pose.
	*
	* For devices where bPoseIsValid is true the application can use the pose to position the device
	* in question. The provided array can be any size up to k_unMaxTrackedDeviceCount. 
	*
	* Seated experiences should call this method with TrackingUniverseSeated and receive poses relative
	* to the seated zero pose. Standing experiences should call this method with TrackingUniverseStanding 
	* and receive poses relative to the Chaperone Play Area. TrackingUniverseRawAndUncalibrated should 
	* probably not be used unless the application is the Chaperone calibration tool itself, but will provide
	* poses relative to the hardware-specific coordinate system in the driver.
	*/
	virtual void GetDeviceToAbsoluteTrackingPose( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount ) = 0;

	/** Sets the zero pose for the seated tracker coordinate system to the current position and yaw of the HMD. After 
	* ResetSeatedZeroPose all GetDeviceToAbsoluteTrackingPose calls that pass TrackingUniverseSeated as the origin 
	* will be relative to this new zero pose. The new zero coordinate system will not change the fact that the Y axis 
	* is up in the real world, so the next pose returned from GetDeviceToAbsoluteTrackingPose after a call to 
	* ResetSeatedZeroPose may not be exactly an identity matrix.
	*
	* NOTE: This function overrides the user's previously saved seated zero pose and should only be called as the result of a user action. 
	* Users are also able to set their seated zero pose via the OpenVR Dashboard.
	**/
	virtual void ResetSeatedZeroPose() = 0;

	/** Returns the transform from the seated zero pose to the standing absolute tracking system. This allows 
	* applications to represent the seated origin to used or transform object positions from one coordinate
	* system to the other. 
	*
	* The seated origin may or may not be inside the Play Area or Collision Bounds returned by IVRChaperone. Its position 
	* depends on what the user has set from the Dashboard settings and previous calls to ResetSeatedZeroPose. */
	virtual HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() = 0;

	/** Returns the transform from the tracking origin to the standing absolute tracking system. This allows
	* applications to convert from raw tracking space to the calibrated standing coordinate system. */
	virtual HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() = 0;

	/** Get a sorted array of device indices of a given class of tracked devices (e.g. controllers).  Devices are sorted right to left
	* relative to the specified tracked device (default: hmd -- pass in -1 for absolute tracking space).  Returns the number of devices
	* in the list, or the size of the array needed if not large enough. */
	virtual uint32_t GetSortedTrackedDeviceIndicesOfClass( ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex = k_unTrackedDeviceIndex_Hmd ) = 0;

	/** Returns the level of activity on the device. */
	virtual EDeviceActivityLevel GetTrackedDeviceActivityLevel( TrackedDeviceIndex_t unDeviceId ) = 0;

	/** Convenience utility to apply the specified transform to the specified pose.
	*   This properly transforms all pose components, including velocity and angular velocity
	*/
	virtual void ApplyTransform( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform ) = 0;

	/** Returns the device index associated with a specific role, for example the left hand or the right hand. This function is deprecated in favor of the new IVRInput system. */
	virtual TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( ETrackedControllerRole unDeviceType ) = 0;

	/** Returns the controller type associated with a device index. This function is deprecated in favor of the new IVRInput system. */
	virtual ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex ) = 0;

	// ------------------------------------
	// Property methods
	// ------------------------------------

	/** Returns the device class of a tracked device. If there has not been a device connected in this slot
	* since the application started this function will return TrackedDevice_Invalid. For previous detected
	* devices the function will return the previously observed device class. 
	*
	* To determine which devices exist on the system, just loop from 0 to k_unMaxTrackedDeviceCount and check
	* the device class. Every device with something other than TrackedDevice_Invalid is associated with an 
	* actual tracked device. */
	virtual ETrackedDeviceClass GetTrackedDeviceClass( TrackedDeviceIndex_t unDeviceIndex ) = 0;

	/** Returns true if there is a device connected in this slot. */
	virtual bool IsTrackedDeviceConnected( TrackedDeviceIndex_t unDeviceIndex ) = 0;

	/** Returns a bool property. If the device index is not valid or the property is not a bool type this function will return false. */
	virtual bool GetBoolTrackedDeviceProperty( TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) = 0;

	/** Returns a float property. If the device index is not valid or the property is not a float type this function will return 0. */
	virtual float GetFloatTrackedDeviceProperty( TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) = 0;

	/** Returns an int property. If the device index is not valid or the property is not a int type this function will return 0. */
	virtual int32_t GetInt32TrackedDeviceProperty( TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) = 0;

	/** Returns a uint64 property. If the device index is not valid or the property is not a uint64 type this function will return 0. */
	virtual uint64_t GetUint64TrackedDeviceProperty( TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) = 0;

	/** Returns a matrix property. If the device index is not valid or the property is not a matrix type, this function will return identity. */
	virtual HmdMatrix34_t GetMatrix34TrackedDeviceProperty( TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) = 0;
	
	/** Returns an array of one type of property. If the device index is not valid or the property is not a single value or an array of the specified type,
	* this function will return 0. Otherwise it returns the number of bytes necessary to hold the array of properties. If unBufferSize is
	* greater than the returned size and pBuffer is non-NULL, pBuffer is filled with the contents of array of properties. */
	virtual uint32_t GetArrayTrackedDeviceProperty( TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, PropertyTypeTag_t propType, void *pBuffer, uint32_t unBufferSize, ETrackedPropertyError *pError = 0L ) = 0;

	/** Returns a string property. If the device index is not valid or the property is not a string type this function will 
	* return 0. Otherwise it returns the length of the number of bytes necessary to hold this string including the trailing
	* null. Strings will always fit in buffers of k_unMaxPropertyStringSize characters. */
	virtual uint32_t GetStringTrackedDeviceProperty( TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError = 0L ) = 0;

	/** returns a string that corresponds with the specified property error. The string will be the name 
	* of the error enum value for all valid error codes */
	virtual const char *GetPropErrorNameFromEnum( ETrackedPropertyError error ) = 0;

	// ------------------------------------
	// Event methods
	// ------------------------------------

	/** Returns true and fills the event with the next event on the queue if there is one. If there are no events
	* this method returns false. uncbVREvent should be the size in bytes of the VREvent_t struct */
	virtual bool PollNextEvent( VREvent_t *pEvent, uint32_t uncbVREvent ) = 0;

	/** Returns true and fills the event with the next event on the queue if there is one. If there are no events
	* this method returns false. Fills in the pose of the associated tracked device in the provided pose struct. 
	* This pose will always be older than the call to this function and should not be used to render the device. 
	uncbVREvent should be the size in bytes of the VREvent_t struct */
	virtual bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, VREvent_t *pEvent, uint32_t uncbVREvent, TrackedDevicePose_t *pTrackedDevicePose ) = 0;

	/** returns the name of an EVREvent enum value */
	virtual const char *GetEventTypeNameFromEnum( EVREventType eType ) = 0;

	// ------------------------------------
	// Rendering helper methods
	// ------------------------------------

	/** Returns the hidden area mesh for the current HMD. The pixels covered by this mesh will never be seen by the user after the lens distortion is
	* applied based on visibility to the panels. If this HMD does not have a hidden area mesh, the vertex data and count will be NULL and 0 respectively.
	* This mesh is meant to be rendered into the stencil buffer (or into the depth buffer setting nearz) before rendering each eye's view. 
	* This will improve performance by letting the GPU early-reject pixels the user will never see before running the pixel shader.
	* NOTE: Render this mesh with backface culling disabled since the winding order of the vertices can be different per-HMD or per-eye.
	* Setting the bInverse argument to true will produce the visible area mesh that is commonly used in place of full-screen quads. The visible area mesh covers all of the pixels the hidden area mesh does not cover.
	* Setting the bLineLoop argument will return a line loop of vertices in HiddenAreaMesh_t->pVertexData with HiddenAreaMesh_t->unTriangleCount set to the number of vertices.
	*/
	virtual HiddenAreaMesh_t GetHiddenAreaMesh( EVREye eEye, EHiddenAreaMeshType type = k_eHiddenAreaMesh_Standard ) = 0;

	// ------------------------------------
	// Controller methods
	// ------------------------------------

	/** Fills the supplied struct with the current state of the controller. Returns false if the controller index
	* is invalid. This function is deprecated in favor of the new IVRInput system. */
	virtual bool GetControllerState( TrackedDeviceIndex_t unControllerDeviceIndex, VRControllerState_t *pControllerState, uint32_t unControllerStateSize ) = 0;

	/** fills the supplied struct with the current state of the controller and the provided pose with the pose of 
	* the controller when the controller state was updated most recently. Use this form if you need a precise controller
	* pose as input to your application when the user presses or releases a button. This function is deprecated in favor of the new IVRInput system. */
	virtual bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, TrackedDeviceIndex_t unControllerDeviceIndex, VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose ) = 0;

	/** Trigger a single haptic pulse on a controller. After this call the application may not trigger another haptic pulse on this controller
	* and axis combination for 5ms. This function is deprecated in favor of the new IVRInput system. */
	virtual void TriggerHapticPulse( TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec ) = 0;

	/** returns the name of an EVRButtonId enum value. This function is deprecated in favor of the new IVRInput system.  */
	virtual const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId ) = 0;

	/** returns the name of an EVRControllerAxisType enum value. This function is deprecated in favor of the new IVRInput system. */
	virtual const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType ) = 0;

	/** Returns true if this application is receiving input from the system. This would return false if 
	* system-related functionality is consuming the input stream. */
	virtual bool IsInputAvailable() = 0;

	/** Returns true SteamVR is drawing controllers on top of the application. Applications should consider
	* not drawing anything attached to the user's hands in this case. */
	virtual bool IsSteamVRDrawingControllers() = 0;

	/** Returns true if the user has put SteamVR into a mode that is distracting them from the application.
	* For applications where this is appropriate, the application should pause ongoing activity. */
	virtual bool ShouldApplicationPause() = 0;

	/** Returns true if SteamVR is doing significant rendering work and the game should do what it can to reduce
	* its own workload. One common way to do this is to reduce the size of the render target provided for each eye. */
	virtual bool ShouldApplicationReduceRenderingWork() = 0;

	// ------------------------------------
	// Firmware methods
	// ------------------------------------
	
	/** Performs the actual firmware update if applicable. 
	 * The following events will be sent, if VRFirmwareError_None was returned: VREvent_FirmwareUpdateStarted, VREvent_FirmwareUpdateFinished 
	 * Use the properties Prop_Firmware_UpdateAvailable_Bool, Prop_Firmware_ManualUpdate_Bool, and Prop_Firmware_ManualUpdateURL_String
	 * to figure our whether a firmware update is available, and to figure out whether its a manual update 
	 * Prop_Firmware_ManualUpdateURL_String should point to an URL describing the manual update process */
	virtual EVRFirmwareError PerformFirmwareUpdate( TrackedDeviceIndex_t unDeviceIndex ) = 0;

	// ------------------------------------
	// Application life cycle methods
	// ------------------------------------

	/** Call this to acknowledge to the system that VREvent_Quit has been received and that the process is exiting.
	* This extends the timeout until the process is killed. */
	virtual void AcknowledgeQuit_Exiting() = 0;

	// -------------------------------------
	// App container sandbox methods
	// -------------------------------------

	/** Retrieves a null-terminated, semicolon-delimited list of UTF8 file paths that an application 
	* must have read access to when running inside of an app container. Returns the number of bytes
	* needed to hold the list. */
	virtual uint32_t GetAppContainerFilePaths( VR_OUT_STRING() char *pchBuffer, uint32_t unBufferSize ) = 0;

	// -------------------------------------
	// System methods
	// -------------------------------------

	/** Returns the current version of the SteamVR runtime. The returned string will remain valid until VR_Shutdown is called.
	*
	* NOTE: Is it not appropriate to use this version to test for the presence of any SteamVR feature. Only use this version
	* number for logging or showing to a user, and not to try to detect anything at runtime. When appropriate, feature-specific
	* presence information is provided by other APIs. */
	virtual const char *GetRuntimeVersion() = 0;

};

static const char * const IVRSystem_Version = "IVRSystem_021";

}


} // Close custom namespace
