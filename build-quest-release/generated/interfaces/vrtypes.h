#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
// vrtypes.h


// Forward declarations to avoid requiring vulkan.h
struct VkDevice_T;
struct VkPhysicalDevice_T;
struct VkInstance_T;
struct VkQueue_T;

// Forward declarations to avoid requiring d3d12.h
struct ID3D12Resource;
struct ID3D12CommandQueue;

namespace vr
{
#pragma pack( push, 8 )

/** A handle for a spatial anchor.  This handle is only valid during the session it was created in.
* Anchors that live beyond one session should be saved by their string descriptors. */
typedef uint32_t SpatialAnchorHandle_t;

typedef void* glSharedTextureHandle_t;
typedef int32_t glInt_t;
typedef uint32_t glUInt_t;


/** Used to return the post-distortion UVs for each color channel.
* UVs range from 0 to 1 with 0,0 in the upper left corner of the
* source render target. The 0,0 to 1,1 range covers a single eye. */
struct DistortionCoordinates_t
{
	float rfRed[2];
	float rfGreen[2];
	float rfBlue[2];
};

enum EVREye
{
	Eye_Left = 0,
	Eye_Right = 1
};

enum ETextureType
{
	TextureType_Invalid = -1, // Handle has been invalidated
	TextureType_DirectX = 0, // Handle is an ID3D11Texture
	TextureType_OpenGL = 1,  // Handle is an OpenGL texture name or an OpenGL render buffer name, depending on submit flags
	TextureType_Vulkan = 2, // Handle is a pointer to a VRVulkanTextureData_t structure
	TextureType_IOSurface = 3, // Handle is a macOS cross-process-sharable IOSurfaceRef, deprecated in favor of TextureType_Metal on supported platforms
	TextureType_DirectX12 = 4, // Handle is a pointer to a D3D12TextureData_t structure
	TextureType_DXGISharedHandle = 5, // Handle is a HANDLE DXGI share handle, only supported for Overlay render targets.
									  // this texture is used directly by our renderer, so only perform atomic (copyresource or resolve) on it
	TextureType_Metal = 6, // Handle is a MTLTexture conforming to the MTLSharedTexture protocol. Textures submitted to IVRCompositor::Submit which
						   // are of type MTLTextureType2DArray assume layer 0 is the left eye texture (vr::EVREye::Eye_left), layer 1 is the right
						   // eye texture (vr::EVREye::Eye_Right)
};

enum EColorSpace
{
	ColorSpace_Auto = 0,	// Assumes 'gamma' for 8-bit per component formats, otherwise 'linear'.  This mirrors the DXGI formats which have _SRGB variants.
	ColorSpace_Gamma = 1,	// Texture data can be displayed directly on the display without any conversion (a.k.a. display native format).
	ColorSpace_Linear = 2,	// Same as gamma but has been converted to a linear representation using DXGI's sRGB conversion algorithm.
};

struct Texture_t
{
	void* handle; // See ETextureType definition above
	ETextureType eType;
	EColorSpace eColorSpace;
};

// Handle to a shared texture (HANDLE on Windows obtained using OpenSharedResource).
typedef uint64_t SharedTextureHandle_t;
#define INVALID_SHARED_TEXTURE_HANDLE	((vr::SharedTextureHandle_t)0)

enum ETrackingResult
{
	TrackingResult_Uninitialized			= 1,

	TrackingResult_Calibrating_InProgress	= 100,
	TrackingResult_Calibrating_OutOfRange	= 101,

	TrackingResult_Running_OK				= 200,
	TrackingResult_Running_OutOfRange		= 201,

	TrackingResult_Fallback_RotationOnly	= 300,
};

typedef uint32_t DriverId_t;
static const uint32_t k_nDriverNone = 0xFFFFFFFF;

static const uint32_t k_unMaxDriverDebugResponseSize = 32768;

/** Used to pass device IDs to API calls */
typedef uint32_t TrackedDeviceIndex_t;
static const uint32_t k_unTrackedDeviceIndex_Hmd = 0;
static const uint32_t k_unMaxTrackedDeviceCount = 64;
static const uint32_t k_unTrackedDeviceIndexOther = 0xFFFFFFFE;
static const uint32_t k_unTrackedDeviceIndexInvalid = 0xFFFFFFFF;

/** Describes what kind of object is being tracked at a given ID */
enum ETrackedDeviceClass
{
	TrackedDeviceClass_Invalid = 0,				// the ID was not valid.
	TrackedDeviceClass_HMD = 1,					// Head-Mounted Displays
	TrackedDeviceClass_Controller = 2,			// Tracked controllers
	TrackedDeviceClass_GenericTracker = 3,		// Generic trackers, similar to controllers
	TrackedDeviceClass_TrackingReference = 4,	// Camera and base stations that serve as tracking reference points
	TrackedDeviceClass_DisplayRedirect = 5,		// Accessories that aren't necessarily tracked themselves, but may redirect video output from other tracked devices

	TrackedDeviceClass_Max
};


/** Describes what specific role associated with a tracked device */
enum ETrackedControllerRole
{
	TrackedControllerRole_Invalid = 0,					// Invalid value for controller type
	TrackedControllerRole_LeftHand = 1,					// Tracked device associated with the left hand
	TrackedControllerRole_RightHand = 2,				// Tracked device associated with the right hand
	TrackedControllerRole_OptOut = 3,					// Tracked device is opting out of left/right hand selection
	TrackedControllerRole_Treadmill = 4,				// Tracked device is a treadmill or other locomotion device
	TrackedControllerRole_Stylus = 5,					// Tracked device is a stylus
	TrackedControllerRole_Max = 5
};


/** Returns true if the tracked controller role is allowed to be a hand */
inline bool IsRoleAllowedAsHand( ETrackedControllerRole eRole )
{
	switch ( eRole )
	{
	case TrackedControllerRole_Invalid:
	case TrackedControllerRole_LeftHand:
	case TrackedControllerRole_RightHand:
		return true;
	default:
		return false;
	}
}


/** describes a single pose for a tracked object */
struct TrackedDevicePose_t
{
	HmdMatrix34_t mDeviceToAbsoluteTracking;
	HmdVector3_t vVelocity;				// velocity in tracker space in m/s
	HmdVector3_t vAngularVelocity;		// angular velocity in radians/s (?)
	ETrackingResult eTrackingResult;
	bool bPoseIsValid;

	// This indicates that there is a device connected for this spot in the pose array.
	// It could go from true to false if the user unplugs the device.
	bool bDeviceIsConnected;
};

/** Identifies which style of tracking origin the application wants to use
* for the poses it is requesting */
enum ETrackingUniverseOrigin
{
	TrackingUniverseSeated = 0,		// Poses are provided relative to the seated zero pose
	TrackingUniverseStanding = 1,	// Poses are provided relative to the safe bounds configured by the user
	TrackingUniverseRawAndUncalibrated = 2,	// Poses are provided in the coordinate system defined by the driver.  It has Y up and is unified for devices of the same driver. You usually don't want this one.
};

enum EAdditionalRadioFeatures
{
	AdditionalRadioFeatures_None           = 0x00000000,
	AdditionalRadioFeatures_HTCLinkBox     = 0x00000001,
	AdditionalRadioFeatures_InternalDongle = 0x00000002,
	AdditionalRadioFeatures_ExternalDongle = 0x00000004,
};

typedef uint64_t WebConsoleHandle_t;
#define INVALID_WEB_CONSOLE_HANDLE	((vr::WebConsoleHandle_t)0)

// Refers to a single container of properties
typedef uint64_t PropertyContainerHandle_t;
typedef uint32_t PropertyTypeTag_t;

static const PropertyContainerHandle_t k_ulInvalidPropertyContainer = 0;
static const PropertyTypeTag_t k_unInvalidPropertyTag = 0;

typedef PropertyContainerHandle_t DriverHandle_t;
static const PropertyContainerHandle_t k_ulInvalidDriverHandle = 0;

// Use these tags to set/get common types as struct properties
static const PropertyTypeTag_t k_unFloatPropertyTag = 1;
static const PropertyTypeTag_t k_unInt32PropertyTag = 2;
static const PropertyTypeTag_t k_unUint64PropertyTag = 3;
static const PropertyTypeTag_t k_unBoolPropertyTag = 4;
static const PropertyTypeTag_t k_unStringPropertyTag = 5;
static const PropertyTypeTag_t k_unErrorPropertyTag = 6;
static const PropertyTypeTag_t k_unDoublePropertyTag = 7;

static const PropertyTypeTag_t k_unHmdMatrix34PropertyTag = 20;
static const PropertyTypeTag_t k_unHmdMatrix44PropertyTag = 21;
static const PropertyTypeTag_t k_unHmdVector3PropertyTag = 22;
static const PropertyTypeTag_t k_unHmdVector4PropertyTag = 23;
static const PropertyTypeTag_t k_unHmdVector2PropertyTag = 24;
static const PropertyTypeTag_t k_unHmdQuadPropertyTag = 25;

static const PropertyTypeTag_t k_unHiddenAreaPropertyTag = 30;
static const PropertyTypeTag_t k_unPathHandleInfoTag = 31;
static const PropertyTypeTag_t k_unActionPropertyTag = 32;
static const PropertyTypeTag_t k_unInputValuePropertyTag = 33;
static const PropertyTypeTag_t k_unWildcardPropertyTag = 34;
static const PropertyTypeTag_t k_unHapticVibrationPropertyTag = 35;
static const PropertyTypeTag_t k_unSkeletonPropertyTag = 36;

static const PropertyTypeTag_t k_unSpatialAnchorPosePropertyTag = 40;
static const PropertyTypeTag_t k_unJsonPropertyTag = 41;
static const PropertyTypeTag_t k_unActiveActionSetPropertyTag = 42;

static const PropertyTypeTag_t k_unOpenVRInternalReserved_Start = 1000;
static const PropertyTypeTag_t k_unOpenVRInternalReserved_End = 10000;


/** Each entry in this enum represents a property that can be retrieved about a
* tracked device. Many fields are only valid for one ETrackedDeviceClass. */
enum ETrackedDeviceProperty
{
	Prop_Invalid								= 0,

	// general properties that apply to all device classes
	Prop_TrackingSystemName_String				= 1000,
	Prop_ModelNumber_String						= 1001,
	Prop_SerialNumber_String					= 1002,
	Prop_RenderModelName_String					= 1003,
	Prop_WillDriftInYaw_Bool					= 1004,
	Prop_ManufacturerName_String				= 1005,
	Prop_TrackingFirmwareVersion_String			= 1006,
	Prop_HardwareRevision_String				= 1007,
	Prop_AllWirelessDongleDescriptions_String	= 1008,
	Prop_ConnectedWirelessDongle_String			= 1009,
	Prop_DeviceIsWireless_Bool					= 1010,
	Prop_DeviceIsCharging_Bool					= 1011,
	Prop_DeviceBatteryPercentage_Float			= 1012, // 0 is empty, 1 is full
	Prop_StatusDisplayTransform_Matrix34		= 1013,
	Prop_Firmware_UpdateAvailable_Bool			= 1014,
	Prop_Firmware_ManualUpdate_Bool				= 1015,
	Prop_Firmware_ManualUpdateURL_String		= 1016,
	Prop_HardwareRevision_Uint64				= 1017,
	Prop_FirmwareVersion_Uint64					= 1018,
	Prop_FPGAVersion_Uint64						= 1019,
	Prop_VRCVersion_Uint64						= 1020,
	Prop_RadioVersion_Uint64					= 1021,
	Prop_DongleVersion_Uint64					= 1022,
	Prop_BlockServerShutdown_Bool				= 1023,
	Prop_CanUnifyCoordinateSystemWithHmd_Bool	= 1024,
	Prop_ContainsProximitySensor_Bool			= 1025,
	Prop_DeviceProvidesBatteryStatus_Bool		= 1026,
	Prop_DeviceCanPowerOff_Bool					= 1027,
	Prop_Firmware_ProgrammingTarget_String		= 1028,
	Prop_DeviceClass_Int32						= 1029,
	Prop_HasCamera_Bool							= 1030,
	Prop_DriverVersion_String                   = 1031,
	Prop_Firmware_ForceUpdateRequired_Bool      = 1032,
	Prop_ViveSystemButtonFixRequired_Bool		= 1033,
	Prop_ParentDriver_Uint64					= 1034,
	Prop_ResourceRoot_String					= 1035,
	Prop_RegisteredDeviceType_String			= 1036,
	Prop_InputProfilePath_String				= 1037, // input profile to use for this device in the input system. Will default to tracking system name if this isn't provided
	Prop_NeverTracked_Bool						= 1038, // Used for devices that will never have a valid pose by design
	Prop_NumCameras_Int32						= 1039,
	Prop_CameraFrameLayout_Int32				= 1040, // EVRTrackedCameraFrameLayout value
	Prop_CameraStreamFormat_Int32				= 1041, // ECameraVideoStreamFormat value
	Prop_AdditionalDeviceSettingsPath_String	= 1042, // driver-relative path to additional device and global configuration settings
	Prop_Identifiable_Bool						= 1043, // Whether device supports being identified from vrmonitor (e.g. blink LED, vibrate haptics, etc)
	Prop_BootloaderVersion_Uint64			    = 1044,
	Prop_AdditionalSystemReportData_String		= 1045, // additional string to include in system reports about a tracked device
	Prop_CompositeFirmwareVersion_String        = 1046, // additional FW components from a device that gets propagated into reports
	Prop_Firmware_RemindUpdate_Bool             = 1047,
	Prop_PeripheralApplicationVersion_Uint64	= 1048,
	Prop_ManufacturerSerialNumber_String		= 1049,
	Prop_ComputedSerialNumber_String			= 1050,
	Prop_EstimatedDeviceFirstUseTime_Int32		= 1051,

	// Properties that are unique to TrackedDeviceClass_HMD
	Prop_ReportsTimeSinceVSync_Bool				= 2000,
	Prop_SecondsFromVsyncToPhotons_Float		= 2001,
	Prop_DisplayFrequency_Float					= 2002,
	Prop_UserIpdMeters_Float					= 2003,
	Prop_CurrentUniverseId_Uint64				= 2004,
	Prop_PreviousUniverseId_Uint64				= 2005,
	Prop_DisplayFirmwareVersion_Uint64			= 2006,
	Prop_IsOnDesktop_Bool						= 2007,
	Prop_DisplayMCType_Int32					= 2008,
	Prop_DisplayMCOffset_Float					= 2009,
	Prop_DisplayMCScale_Float					= 2010,
	Prop_EdidVendorID_Int32						= 2011,
	Prop_DisplayMCImageLeft_String              = 2012,
	Prop_DisplayMCImageRight_String             = 2013,
	Prop_DisplayGCBlackClamp_Float				= 2014,
	Prop_EdidProductID_Int32					= 2015,
	Prop_CameraToHeadTransform_Matrix34			= 2016,
	Prop_DisplayGCType_Int32					= 2017,
	Prop_DisplayGCOffset_Float					= 2018,
	Prop_DisplayGCScale_Float					= 2019,
	Prop_DisplayGCPrescale_Float				= 2020,
	Prop_DisplayGCImage_String					= 2021,
	Prop_LensCenterLeftU_Float					= 2022,
	Prop_LensCenterLeftV_Float					= 2023,
	Prop_LensCenterRightU_Float					= 2024,
	Prop_LensCenterRightV_Float					= 2025,
	Prop_UserHeadToEyeDepthMeters_Float			= 2026,
	Prop_CameraFirmwareVersion_Uint64			= 2027,
	Prop_CameraFirmwareDescription_String		= 2028,
	Prop_DisplayFPGAVersion_Uint64				= 2029,
	Prop_DisplayBootloaderVersion_Uint64		= 2030,
	Prop_DisplayHardwareVersion_Uint64			= 2031,
	Prop_AudioFirmwareVersion_Uint64			= 2032,
	Prop_CameraCompatibilityMode_Int32			= 2033,
	Prop_ScreenshotHorizontalFieldOfViewDegrees_Float = 2034,
	Prop_ScreenshotVerticalFieldOfViewDegrees_Float = 2035,
	Prop_DisplaySuppressed_Bool					= 2036,
	Prop_DisplayAllowNightMode_Bool				= 2037,
	Prop_DisplayMCImageWidth_Int32				= 2038,
	Prop_DisplayMCImageHeight_Int32				= 2039,
	Prop_DisplayMCImageNumChannels_Int32		= 2040,
	Prop_DisplayMCImageData_Binary				= 2041,
	Prop_SecondsFromPhotonsToVblank_Float		= 2042,
	Prop_DriverDirectModeSendsVsyncEvents_Bool	= 2043,
	Prop_DisplayDebugMode_Bool					= 2044,
	Prop_GraphicsAdapterLuid_Uint64				= 2045,
	Prop_DriverProvidedChaperonePath_String		= 2048,
	Prop_ExpectedTrackingReferenceCount_Int32	= 2049, // expected number of sensors or basestations to reserve UI space for
	Prop_ExpectedControllerCount_Int32			= 2050, // expected number of tracked controllers to reserve UI space for
	Prop_NamedIconPathControllerLeftDeviceOff_String	= 2051, // placeholder icon for "left" controller if not yet detected/loaded
	Prop_NamedIconPathControllerRightDeviceOff_String	= 2052, // placeholder icon for "right" controller if not yet detected/loaded
	Prop_NamedIconPathTrackingReferenceDeviceOff_String	= 2053, // placeholder icon for sensor/base if not yet detected/loaded
	Prop_DoNotApplyPrediction_Bool				= 2054, // currently no effect. was used to disable HMD pose prediction on MR, which is now done by MR driver setting velocity=0
	Prop_CameraToHeadTransforms_Matrix34_Array	= 2055,
	Prop_DistortionMeshResolution_Int32			= 2056, // custom resolution of compositor calls to IVRSystem::ComputeDistortion
	Prop_DriverIsDrawingControllers_Bool		= 2057,
	Prop_DriverRequestsApplicationPause_Bool	= 2058,
	Prop_DriverRequestsReducedRendering_Bool	= 2059,
	Prop_MinimumIpdStepMeters_Float				= 2060,
	Prop_AudioBridgeFirmwareVersion_Uint64		= 2061,
	Prop_ImageBridgeFirmwareVersion_Uint64		= 2062,
	Prop_ImuToHeadTransform_Matrix34			= 2063,
	Prop_ImuFactoryGyroBias_Vector3				= 2064,
	Prop_ImuFactoryGyroScale_Vector3			= 2065,
	Prop_ImuFactoryAccelerometerBias_Vector3	= 2066,
	Prop_ImuFactoryAccelerometerScale_Vector3	= 2067,
	// reserved 2068
	Prop_ConfigurationIncludesLighthouse20Features_Bool = 2069,
	Prop_AdditionalRadioFeatures_Uint64         = 2070,
	Prop_CameraWhiteBalance_Vector4_Array		= 2071, // Prop_NumCameras_Int32-sized array of float[4] RGBG white balance calibration data (max size is vr::k_unMaxCameras)
	Prop_CameraDistortionFunction_Int32_Array	= 2072, // Prop_NumCameras_Int32-sized array of vr::EVRDistortionFunctionType values (max size is vr::k_unMaxCameras)
	Prop_CameraDistortionCoefficients_Float_Array = 2073, // Prop_NumCameras_Int32-sized array of double[vr::k_unMaxDistortionFunctionParameters] (max size is vr::k_unMaxCameras)
	Prop_ExpectedControllerType_String			= 2074,
	Prop_HmdTrackingStyle_Int32					= 2075, // one of EHmdTrackingStyle
	Prop_DriverProvidedChaperoneVisibility_Bool = 2076,
	Prop_HmdColumnCorrectionSettingPrefix_String = 2077,
	Prop_CameraSupportsCompatibilityModes_Bool	= 2078,
	Prop_SupportsRoomViewDepthProjection_Bool	= 2079,
	Prop_DisplayAvailableFrameRates_Float_Array = 2080, // populated by compositor from actual EDID list when available from GPU driver
	Prop_DisplaySupportsMultipleFramerates_Bool = 2081, // if this is true but Prop_DisplayAvailableFrameRates_Float_Array is empty, explain to user
	Prop_DisplayColorMultLeft_Vector3			= 2082,
	Prop_DisplayColorMultRight_Vector3			= 2083,
	Prop_DisplaySupportsRuntimeFramerateChange_Bool = 2084,
	Prop_DisplaySupportsAnalogGain_Bool 		= 2085,
	Prop_DisplayMinAnalogGain_Float 			= 2086,
	Prop_DisplayMaxAnalogGain_Float 			= 2087,
    Prop_CameraExposureTime_Float               = 2088,
    Prop_CameraGlobalGain_Float                 = 2089,
	// Prop_DashboardLayoutPathName_String 		= 2090, // DELETED
	Prop_DashboardScale_Float 					= 2091,
	Prop_IpdUIRangeMinMeters_Float 				= 2100,
	Prop_IpdUIRangeMaxMeters_Float 				= 2101,
	Prop_Hmd_SupportsHDCP14LegacyCompat_Bool	= 2102,
	Prop_Hmd_SupportsMicMonitoring_Bool 		= 2103,

	// Driver requested mura correction properties
	Prop_DriverRequestedMuraCorrectionMode_Int32		= 2200,
	Prop_DriverRequestedMuraFeather_InnerLeft_Int32		= 2201,
	Prop_DriverRequestedMuraFeather_InnerRight_Int32	= 2202,
	Prop_DriverRequestedMuraFeather_InnerTop_Int32		= 2203,
	Prop_DriverRequestedMuraFeather_InnerBottom_Int32	= 2204,
	Prop_DriverRequestedMuraFeather_OuterLeft_Int32		= 2205,
	Prop_DriverRequestedMuraFeather_OuterRight_Int32	= 2206,
	Prop_DriverRequestedMuraFeather_OuterTop_Int32		= 2207,
	Prop_DriverRequestedMuraFeather_OuterBottom_Int32	= 2208,

	Prop_Audio_DefaultPlaybackDeviceId_String		= 2300,
	Prop_Audio_DefaultRecordingDeviceId_String		= 2301,
	Prop_Audio_DefaultPlaybackDeviceVolume_Float = 2302,
	Prop_Audio_SupportsDualSpeakerAndJackOutput_Bool = 2303,

	// Properties that are unique to TrackedDeviceClass_Controller
	Prop_AttachedDeviceId_String				= 3000,
	Prop_SupportedButtons_Uint64				= 3001,
	Prop_Axis0Type_Int32						= 3002, // Return value is of type EVRControllerAxisType
	Prop_Axis1Type_Int32						= 3003, // Return value is of type EVRControllerAxisType
	Prop_Axis2Type_Int32						= 3004, // Return value is of type EVRControllerAxisType
	Prop_Axis3Type_Int32						= 3005, // Return value is of type EVRControllerAxisType
	Prop_Axis4Type_Int32						= 3006, // Return value is of type EVRControllerAxisType
	Prop_ControllerRoleHint_Int32				= 3007, // Return value is of type ETrackedControllerRole

	// Properties that are unique to TrackedDeviceClass_TrackingReference
	Prop_FieldOfViewLeftDegrees_Float			= 4000,
	Prop_FieldOfViewRightDegrees_Float			= 4001,
	Prop_FieldOfViewTopDegrees_Float			= 4002,
	Prop_FieldOfViewBottomDegrees_Float			= 4003,
	Prop_TrackingRangeMinimumMeters_Float		= 4004,
	Prop_TrackingRangeMaximumMeters_Float		= 4005,
	Prop_ModeLabel_String						= 4006,
	Prop_CanWirelessIdentify_Bool               = 4007, // volatile, based on radio presence and fw discovery
	Prop_Nonce_Int32                            = 4008,

	// Properties that are used for user interface like icons names
	Prop_IconPathName_String						= 5000, // DEPRECATED. Value not referenced. Now expected to be part of icon path properties.
	Prop_NamedIconPathDeviceOff_String				= 5001, // {driver}/icons/icon_filename - PNG for static icon, or GIF for animation, 50x32 for headsets and 32x32 for others
	Prop_NamedIconPathDeviceSearching_String		= 5002, // {driver}/icons/icon_filename - PNG for static icon, or GIF for animation, 50x32 for headsets and 32x32 for others
	Prop_NamedIconPathDeviceSearchingAlert_String	= 5003, // {driver}/icons/icon_filename - PNG for static icon, or GIF for animation, 50x32 for headsets and 32x32 for others
	Prop_NamedIconPathDeviceReady_String			= 5004, // {driver}/icons/icon_filename - PNG for static icon, or GIF for animation, 50x32 for headsets and 32x32 for others
	Prop_NamedIconPathDeviceReadyAlert_String		= 5005, // {driver}/icons/icon_filename - PNG for static icon, or GIF for animation, 50x32 for headsets and 32x32 for others
	Prop_NamedIconPathDeviceNotReady_String			= 5006, // {driver}/icons/icon_filename - PNG for static icon, or GIF for animation, 50x32 for headsets and 32x32 for others
	Prop_NamedIconPathDeviceStandby_String			= 5007, // {driver}/icons/icon_filename - PNG for static icon, or GIF for animation, 50x32 for headsets and 32x32 for others
	Prop_NamedIconPathDeviceAlertLow_String			= 5008, // {driver}/icons/icon_filename - PNG for static icon, or GIF for animation, 50x32 for headsets and 32x32 for others
	Prop_NamedIconPathDeviceStandbyAlert_String		= 5009, // {driver}/icons/icon_filename - PNG for static icon, or GIF for animation, 50x32 for headsets and 32x32 for others

	// Properties that are used by helpers, but are opaque to applications
	Prop_DisplayHiddenArea_Binary_Start				= 5100,
	Prop_DisplayHiddenArea_Binary_End				= 5150,
	Prop_ParentContainer							= 5151,
	Prop_OverrideContainer_Uint64					= 5152,

	// Properties that are unique to drivers
	Prop_UserConfigPath_String					= 6000,
	Prop_InstallPath_String						= 6001,
	Prop_HasDisplayComponent_Bool				= 6002,
	Prop_HasControllerComponent_Bool			= 6003,
	Prop_HasCameraComponent_Bool				= 6004,
	Prop_HasDriverDirectModeComponent_Bool		= 6005,
	Prop_HasVirtualDisplayComponent_Bool		= 6006,
	Prop_HasSpatialAnchorsSupport_Bool		    = 6007,

	// Properties that are set internally based on other information provided by drivers
	Prop_ControllerType_String					= 7000,
	//Prop_LegacyInputProfile_String				= 7001, // This is no longer used. See "legacy_binding" in the input profile instead.
	Prop_ControllerHandSelectionPriority_Int32	= 7002, // Allows hand assignments to prefer some controllers over others. High numbers are selected over low numbers

	// Vendors are free to expose private debug data in this reserved region
	Prop_VendorSpecific_Reserved_Start			= 10000,
	Prop_VendorSpecific_Reserved_End			= 10999,

	Prop_TrackedDeviceProperty_Max				= 1000000,
};

/** No string property will ever be longer than this length */
static const uint32_t k_unMaxPropertyStringSize = 32 * 1024;

/** Used to return errors that occur when reading properties. */
enum ETrackedPropertyError
{
	TrackedProp_Success						= 0,
	TrackedProp_WrongDataType				= 1,
	TrackedProp_WrongDeviceClass			= 2,
	TrackedProp_BufferTooSmall				= 3,
	TrackedProp_UnknownProperty				= 4, // Driver has not set the property (and may not ever).
	TrackedProp_InvalidDevice				= 5,
	TrackedProp_CouldNotContactServer		= 6,
	TrackedProp_ValueNotProvidedByDevice	= 7,
	TrackedProp_StringExceedsMaximumLength	= 8,
	TrackedProp_NotYetAvailable				= 9, // The property value isn't known yet, but is expected soon. Call again later.
	TrackedProp_PermissionDenied			= 10,
	TrackedProp_InvalidOperation			= 11,
	TrackedProp_CannotWriteToWildcards		= 12,
	TrackedProp_IPCReadFailure				= 13,
	TrackedProp_OutOfMemory					= 14,
	TrackedProp_InvalidContainer			= 15,
};

/** Used to drive certain text in the UI when talking about the tracking system for the HMD */
enum EHmdTrackingStyle
{
	HmdTrackingStyle_Unknown				= 0,

	HmdTrackingStyle_Lighthouse				= 1, // base stations and lasers
	HmdTrackingStyle_OutsideInCameras		= 2, // Cameras and LED, Rift 1 style
	HmdTrackingStyle_InsideOutCameras		= 3, // Cameras on HMD looking at the world
};

typedef uint64_t VRActionHandle_t;
typedef uint64_t VRActionSetHandle_t;
typedef uint64_t VRInputValueHandle_t;

static const VRActionHandle_t k_ulInvalidActionHandle = 0;
static const VRActionSetHandle_t k_ulInvalidActionSetHandle = 0;
static const VRInputValueHandle_t k_ulInvalidInputValueHandle = 0;


/** Allows the application to control what part of the provided texture will be used in the
* frame buffer. */
struct VRTextureBounds_t
{
	float uMin, vMin;
	float uMax, vMax;
};

/** Allows specifying pose used to render provided scene texture (if different from value returned by WaitGetPoses). */
struct VRTextureWithPose_t : public Texture_t
{
	HmdMatrix34_t mDeviceToAbsoluteTracking; // Actual pose used to render scene textures.
};

struct VRTextureDepthInfo_t
{
	void* handle; // See ETextureType definition above
	HmdMatrix44_t mProjection;
	HmdVector2_t vRange; // 0..1
};

struct VRTextureWithDepth_t : public Texture_t
{
	VRTextureDepthInfo_t depth;
};

struct VRTextureWithPoseAndDepth_t : public VRTextureWithPose_t
{
	VRTextureDepthInfo_t depth;
};

/** Allows the application to control how scene textures are used by the compositor when calling Submit. */
enum EVRSubmitFlags
{
	// Simple render path. App submits rendered left and right eye images with no lens distortion correction applied.
	Submit_Default = 0x00,

	// App submits final left and right eye images with lens distortion already applied (lens distortion makes the images appear
	// barrel distorted with chromatic aberration correction applied). The app would have used the data returned by
	// vr::IVRSystem::ComputeDistortion() to apply the correct distortion to the rendered images before calling Submit().
	Submit_LensDistortionAlreadyApplied = 0x01,

	// If the texture pointer passed in is actually a renderbuffer (e.g. for MSAA in OpenGL) then set this flag.
	Submit_GlRenderBuffer = 0x02,

	// Do not use
	Submit_Reserved = 0x04,

	// Set to indicate that pTexture is a pointer to a VRTextureWithPose_t.
	// This flag can be combined with Submit_TextureWithDepth to pass a VRTextureWithPoseAndDepth_t.
	Submit_TextureWithPose = 0x08,

	// Set to indicate that pTexture is a pointer to a VRTextureWithDepth_t.
	// This flag can be combined with Submit_TextureWithPose to pass a VRTextureWithPoseAndDepth_t.
	Submit_TextureWithDepth = 0x10,

	// Set to indicate a discontinuity between this and the last frame.
	// This will prevent motion smoothing from attempting to extrapolate using the pair.
	Submit_FrameDiscontinuty = 0x20,

	// Set to indicate that pTexture->handle is a contains VRVulkanTextureArrayData_t
	Submit_VulkanTextureWithArrayData = 0x40,

	// If the texture pointer passed in is an OpenGL Array texture, set this flag
	Submit_GlArrayTexture = 0x80,

	// Do not use
	Submit_Reserved2 = 0x8000,


};

/** Data required for passing Vulkan textures to IVRCompositor::Submit.
* Be sure to call OpenVR_Shutdown before destroying these resources.
* Please see https://github.com/ValveSoftware/openvr/wiki/Vulkan for Vulkan-specific documentation */
struct VRVulkanTextureData_t
{
	uint64_t m_nImage; // VkImage
	VkDevice_T *m_pDevice;
	VkPhysicalDevice_T *m_pPhysicalDevice;
	VkInstance_T *m_pInstance;
	VkQueue_T *m_pQueue;
	uint32_t m_nQueueFamilyIndex;
	uint32_t m_nWidth, m_nHeight, m_nFormat, m_nSampleCount;
};

/** Data required for passing Vulkan texture arrays to IVRCompositor::Submit.
* Be sure to call OpenVR_Shutdown before destroying these resources.
* Please see https://github.com/ValveSoftware/openvr/wiki/Vulkan for Vulkan-specific documentation */
struct VRVulkanTextureArrayData_t : public VRVulkanTextureData_t
{
	uint32_t m_unArrayIndex;
	uint32_t m_unArraySize;
};

/** Data required for passing D3D12 textures to IVRCompositor::Submit.
* Be sure to call OpenVR_Shutdown before destroying these resources. */
struct D3D12TextureData_t
{
	ID3D12Resource *m_pResource;
	ID3D12CommandQueue *m_pCommandQueue;
	uint32_t m_nNodeMask;
};

/** Status of the overall system or tracked objects */
enum EVRState
{
	VRState_Undefined = -1,
	VRState_Off = 0,
	VRState_Searching = 1,
	VRState_Searching_Alert = 2,
	VRState_Ready = 3,
	VRState_Ready_Alert = 4,
	VRState_NotReady = 5,
	VRState_Standby = 6,
	VRState_Ready_Alert_Low = 7,
};

/** The types of events that could be posted (and what the parameters mean for each event type) */
enum EVREventType
{
	VREvent_None = 0,

	VREvent_TrackedDeviceActivated		= 100,
	VREvent_TrackedDeviceDeactivated	= 101,
	VREvent_TrackedDeviceUpdated		= 102,
	VREvent_TrackedDeviceUserInteractionStarted	= 103,
	VREvent_TrackedDeviceUserInteractionEnded	= 104,
	VREvent_IpdChanged					= 105,
	VREvent_EnterStandbyMode			= 106,
	VREvent_LeaveStandbyMode			= 107,
	VREvent_TrackedDeviceRoleChanged	= 108,
	VREvent_WatchdogWakeUpRequested		= 109,
	VREvent_LensDistortionChanged		= 110,
	VREvent_PropertyChanged				= 111,
	VREvent_WirelessDisconnect			= 112,
	VREvent_WirelessReconnect			= 113,

	VREvent_ButtonPress					= 200, // data is controller
	VREvent_ButtonUnpress				= 201, // data is controller
	VREvent_ButtonTouch					= 202, // data is controller
	VREvent_ButtonUntouch				= 203, // data is controller

	// VREvent_DualAnalog_Press			= 250, // No longer sent
	// VREvent_DualAnalog_Unpress		= 251, // No longer sent
	// VREvent_DualAnalog_Touch			= 252, // No longer sent
	// VREvent_DualAnalog_Untouch		= 253, // No longer sent
	// VREvent_DualAnalog_Move			= 254, // No longer sent
	// VREvent_DualAnalog_ModeSwitch1	= 255, // No longer sent
	// VREvent_DualAnalog_ModeSwitch2	= 256, // No longer sent
	VREvent_Modal_Cancel				= 257, // Sent to overlays with the

	VREvent_MouseMove					= 300, // data is mouse
	VREvent_MouseButtonDown				= 301, // data is mouse
	VREvent_MouseButtonUp				= 302, // data is mouse
	VREvent_FocusEnter					= 303, // data is overlay
	VREvent_FocusLeave					= 304, // data is overlay
	VREvent_ScrollDiscrete				= 305, // data is scroll
	VREvent_TouchPadMove				= 306, // data is mouse
	VREvent_OverlayFocusChanged			= 307, // data is overlay, global event
	VREvent_ReloadOverlays				= 308,
	VREvent_ScrollSmooth				= 309, // data is scroll
	VREvent_LockMousePosition			= 310,
	VREvent_UnlockMousePosition			= 311,

	VREvent_InputFocusCaptured			= 400, // data is process DEPRECATED
	VREvent_InputFocusReleased			= 401, // data is process DEPRECATED
	// VREvent_SceneFocusLost			= 402, // data is process
	// VREvent_SceneFocusGained			= 403, // data is process
	VREvent_SceneApplicationChanged		= 404, // data is process - The App actually drawing the scene changed (usually to or from the compositor)
	VREvent_SceneFocusChanged			= 405, // data is process - New app got access to draw the scene
	VREvent_InputFocusChanged			= 406, // data is process
	// VREvent_SceneApplicationSecondaryRenderingStarted = 407,
	VREvent_SceneApplicationUsingWrongGraphicsAdapter = 408, // data is process
	VREvent_ActionBindingReloaded		 = 409, // data is process - The App that action binds reloaded for

	VREvent_HideRenderModels			= 410, // Sent to the scene application to request hiding render models temporarily
	VREvent_ShowRenderModels			= 411, // Sent to the scene application to request restoring render model visibility

	VREvent_SceneApplicationStateChanged = 412, // No data; but query VRApplications()->GetSceneApplicationState();

	VREvent_ConsoleOpened               = 420,
	VREvent_ConsoleClosed               = 421,

	VREvent_OverlayShown				= 500,
	VREvent_OverlayHidden				= 501,
	VREvent_DashboardActivated			= 502,
	VREvent_DashboardDeactivated		= 503,
	//VREvent_DashboardThumbSelected		= 504, // Sent to the overlay manager - data is overlay - No longer sent
	VREvent_DashboardRequested			= 505, // Sent to the overlay manager - data is overlay
	VREvent_ResetDashboard				= 506, // Send to the overlay manager
	//VREvent_RenderToast					= 507, // Send to the dashboard to render a toast - data is the notification ID -- no longer sent
	VREvent_ImageLoaded					= 508, // Sent to overlays when a SetOverlayRaw or SetOverlayFromFile call finishes loading
	VREvent_ShowKeyboard				= 509, // Sent to keyboard renderer in the dashboard to invoke it
	VREvent_HideKeyboard				= 510, // Sent to keyboard renderer in the dashboard to hide it
	VREvent_OverlayGamepadFocusGained	= 511, // Sent to an overlay when IVROverlay::SetFocusOverlay is called on it
	VREvent_OverlayGamepadFocusLost		= 512, // Send to an overlay when it previously had focus and IVROverlay::SetFocusOverlay is called on something else
	VREvent_OverlaySharedTextureChanged = 513,
	//VREvent_DashboardGuideButtonDown	= 514, // These are no longer sent
	//VREvent_DashboardGuideButtonUp		= 515,
	VREvent_ScreenshotTriggered			= 516, // Screenshot button combo was pressed, Dashboard should request a screenshot
	VREvent_ImageFailed					= 517, // Sent to overlays when a SetOverlayRaw or SetOverlayfromFail fails to load
	VREvent_DashboardOverlayCreated		= 518,
	VREvent_SwitchGamepadFocus			= 519,

	// Screenshot API
	VREvent_RequestScreenshot				= 520, // Sent by vrclient application to compositor to take a screenshot
	VREvent_ScreenshotTaken					= 521, // Sent by compositor to the application that the screenshot has been taken
	VREvent_ScreenshotFailed				= 522, // Sent by compositor to the application that the screenshot failed to be taken
	VREvent_SubmitScreenshotToDashboard		= 523, // Sent by compositor to the dashboard that a completed screenshot was submitted
	VREvent_ScreenshotProgressToDashboard	= 524, // Sent by compositor to the dashboard that a completed screenshot was submitted

	VREvent_PrimaryDashboardDeviceChanged	= 525,
	VREvent_RoomViewShown					= 526, // Sent by compositor whenever room-view is enabled
	VREvent_RoomViewHidden					= 527, // Sent by compositor whenever room-view is disabled
	VREvent_ShowUI							= 528, // data is showUi
	VREvent_ShowDevTools					= 529, // data is showDevTools
	VREvent_DesktopViewUpdating				= 530,
	VREvent_DesktopViewReady				= 531,

	VREvent_Notification_Shown				= 600,
	VREvent_Notification_Hidden				= 601,
	VREvent_Notification_BeginInteraction	= 602,
	VREvent_Notification_Destroyed			= 603,

	VREvent_Quit							= 700, // data is process
	VREvent_ProcessQuit						= 701, // data is process
	//VREvent_QuitAborted_UserPrompt			= 702, // data is process
	VREvent_QuitAcknowledged				= 703, // data is process
	VREvent_DriverRequestedQuit				= 704, // The driver has requested that SteamVR shut down
	VREvent_RestartRequested				= 705, // A driver or other component wants the user to restart SteamVR

	VREvent_ChaperoneDataHasChanged			= 800, // this will never happen with the new chaperone system
	VREvent_ChaperoneUniverseHasChanged		= 801,
	VREvent_ChaperoneTempDataHasChanged		= 802, // this will never happen with the new chaperone system
	VREvent_ChaperoneSettingsHaveChanged	= 803,
	VREvent_SeatedZeroPoseReset				= 804,
	VREvent_ChaperoneFlushCache				= 805, // Sent when the process needs to reload any cached data it retrieved from VRChaperone()
	VREvent_ChaperoneRoomSetupStarting	    = 806, // Triggered by CVRChaperoneClient::RoomSetupStarting
	VREvent_ChaperoneRoomSetupFinished	    = 807, // Triggered by CVRChaperoneClient::CommitWorkingCopy
	VREvent_StandingZeroPoseReset			= 808,

	VREvent_AudioSettingsHaveChanged		= 820,

	VREvent_BackgroundSettingHasChanged				= 850,
	VREvent_CameraSettingsHaveChanged				= 851,
	VREvent_ReprojectionSettingHasChanged			= 852,
	VREvent_ModelSkinSettingsHaveChanged			= 853,
	VREvent_EnvironmentSettingsHaveChanged			= 854,
	VREvent_PowerSettingsHaveChanged				= 855,
	VREvent_EnableHomeAppSettingsHaveChanged		= 856,
	VREvent_SteamVRSectionSettingChanged			= 857,
	VREvent_LighthouseSectionSettingChanged			= 858,
	VREvent_NullSectionSettingChanged				= 859,
	VREvent_UserInterfaceSectionSettingChanged		= 860,
	VREvent_NotificationsSectionSettingChanged		= 861,
	VREvent_KeyboardSectionSettingChanged			= 862,
	VREvent_PerfSectionSettingChanged				= 863,
	VREvent_DashboardSectionSettingChanged			= 864,
	VREvent_WebInterfaceSectionSettingChanged		= 865,
	VREvent_TrackersSectionSettingChanged			= 866,
	VREvent_LastKnownSectionSettingChanged			= 867,
	VREvent_DismissedWarningsSectionSettingChanged	= 868,
	VREvent_GpuSpeedSectionSettingChanged			= 869,
	VREvent_WindowsMRSectionSettingChanged			= 870,
	VREvent_OtherSectionSettingChanged				= 871,

	VREvent_StatusUpdate					= 900,

	VREvent_WebInterface_InstallDriverCompleted = 950,

	VREvent_MCImageUpdated					= 1000,

	VREvent_FirmwareUpdateStarted			= 1100,
	VREvent_FirmwareUpdateFinished			= 1101,

	VREvent_KeyboardClosed					= 1200,
	VREvent_KeyboardCharInput				= 1201,
	VREvent_KeyboardDone					= 1202, // Sent when DONE button clicked on keyboard

	//VREvent_ApplicationTransitionStarted		= 1300,
	//VREvent_ApplicationTransitionAborted		= 1301,
	//VREvent_ApplicationTransitionNewAppStarted	= 1302,
	VREvent_ApplicationListUpdated				= 1303,
	VREvent_ApplicationMimeTypeLoad				= 1304,
	// VREvent_ApplicationTransitionNewAppLaunchComplete = 1305,
	VREvent_ProcessConnected					= 1306,
	VREvent_ProcessDisconnected					= 1307,

	//VREvent_Compositor_MirrorWindowShown		= 1400, // DEPRECATED
	//VREvent_Compositor_MirrorWindowHidden		= 1401, // DEPRECATED
	VREvent_Compositor_ChaperoneBoundsShown		= 1410,
	VREvent_Compositor_ChaperoneBoundsHidden	= 1411,
	VREvent_Compositor_DisplayDisconnected		= 1412,
	VREvent_Compositor_DisplayReconnected		= 1413,
	VREvent_Compositor_HDCPError				= 1414, // data is hdcpError
	VREvent_Compositor_ApplicationNotResponding	= 1415,
	VREvent_Compositor_ApplicationResumed		= 1416,
	VREvent_Compositor_OutOfVideoMemory			= 1417,
	VREvent_Compositor_DisplayModeNotSupported	= 1418, // k_pch_SteamVR_PreferredRefreshRate
	VREvent_Compositor_StageOverrideReady		= 1419,

	VREvent_TrackedCamera_StartVideoStream  = 1500,
	VREvent_TrackedCamera_StopVideoStream   = 1501,
	VREvent_TrackedCamera_PauseVideoStream  = 1502,
	VREvent_TrackedCamera_ResumeVideoStream = 1503,
	VREvent_TrackedCamera_EditingSurface    = 1550,

	VREvent_PerformanceTest_EnableCapture	= 1600,
	VREvent_PerformanceTest_DisableCapture	= 1601,
	VREvent_PerformanceTest_FidelityLevel	= 1602,

	VREvent_MessageOverlay_Closed			= 1650,
	VREvent_MessageOverlayCloseRequested	= 1651,

	VREvent_Input_HapticVibration			= 1700, // data is hapticVibration
	VREvent_Input_BindingLoadFailed			= 1701, // data is inputBinding
	VREvent_Input_BindingLoadSuccessful		= 1702, // data is inputBinding
	VREvent_Input_ActionManifestReloaded	= 1703, // no data
	VREvent_Input_ActionManifestLoadFailed	= 1704, // data is actionManifest
	VREvent_Input_ProgressUpdate			= 1705, // data is progressUpdate
	VREvent_Input_TrackerActivated			= 1706,
	VREvent_Input_BindingsUpdated			= 1707,
	VREvent_Input_BindingSubscriptionChanged = 1708,

	VREvent_SpatialAnchors_PoseUpdated		= 1800,        // data is spatialAnchor. broadcast
	VREvent_SpatialAnchors_DescriptorUpdated = 1801,       // data is spatialAnchor. broadcast
	VREvent_SpatialAnchors_RequestPoseUpdate = 1802,       // data is spatialAnchor. sent to specific driver
	VREvent_SpatialAnchors_RequestDescriptorUpdate = 1803, // data is spatialAnchor. sent to specific driver

	VREvent_SystemReport_Started			= 1900, // user or system initiated generation of a system report. broadcast

	VREvent_Monitor_ShowHeadsetView			= 2000, // data is process
	VREvent_Monitor_HideHeadsetView			= 2001, // data is process

	// Vendors are free to expose private events in this reserved region
	VREvent_VendorSpecific_Reserved_Start	= 10000,
	VREvent_VendorSpecific_Reserved_End		= 19999,
};


/** Level of Hmd activity */
// UserInteraction_Timeout means the device is in the process of timing out.
// InUse = ( k_EDeviceActivityLevel_UserInteraction || k_EDeviceActivityLevel_UserInteraction_Timeout )
// VREvent_TrackedDeviceUserInteractionStarted fires when the devices transitions from Standby -> UserInteraction or Idle -> UserInteraction.
// VREvent_TrackedDeviceUserInteractionEnded fires when the devices transitions from UserInteraction_Timeout -> Idle
enum EDeviceActivityLevel
{
	k_EDeviceActivityLevel_Unknown = -1,
	k_EDeviceActivityLevel_Idle = 0,						// No activity for the last 10 seconds
	k_EDeviceActivityLevel_UserInteraction = 1,				// Activity (movement or prox sensor) is happening now
	k_EDeviceActivityLevel_UserInteraction_Timeout = 2,		// No activity for the last 0.5 seconds
	k_EDeviceActivityLevel_Standby = 3,						// Idle for at least 5 seconds (configurable in Settings -> Power Management)
	k_EDeviceActivityLevel_Idle_Timeout = 4,
};


/** VR controller button and axis IDs */
enum EVRButtonId
{
	k_EButton_System			= 0,
	k_EButton_ApplicationMenu	= 1,
	k_EButton_Grip				= 2,
	k_EButton_DPad_Left			= 3,
	k_EButton_DPad_Up			= 4,
	k_EButton_DPad_Right		= 5,
	k_EButton_DPad_Down			= 6,
	k_EButton_A					= 7,

	k_EButton_ProximitySensor   = 31,

	k_EButton_Axis0				= 32,
	k_EButton_Axis1				= 33,
	k_EButton_Axis2				= 34,
	k_EButton_Axis3				= 35,
	k_EButton_Axis4				= 36,

	// aliases for well known controllers
	k_EButton_SteamVR_Touchpad	= k_EButton_Axis0,
	k_EButton_SteamVR_Trigger	= k_EButton_Axis1,

	k_EButton_Dashboard_Back	= k_EButton_Grip,

	k_EButton_IndexController_A		= k_EButton_Grip,
	k_EButton_IndexController_B		= k_EButton_ApplicationMenu,
	k_EButton_IndexController_JoyStick	= k_EButton_Axis3,

	k_EButton_Max				= 64
};

inline uint64_t ButtonMaskFromId( EVRButtonId id ) { return 1ull << id; }

/** used for controller button events */
struct VREvent_Controller_t
{
	uint32_t button; // EVRButtonId enum
};


/** used for simulated mouse events in overlay space */
enum EVRMouseButton
{
	VRMouseButton_Left					= 0x0001,
	VRMouseButton_Right					= 0x0002,
	VRMouseButton_Middle				= 0x0004,
};


/** used for simulated mouse events in overlay space */
struct VREvent_Mouse_t
{
	float x, y; // co-ords are in GL space, bottom left of the texture is 0,0
	uint32_t button; // EVRMouseButton enum
};

/** used for simulated mouse wheel scroll */
struct VREvent_Scroll_t
{
	float xdelta, ydelta;
	uint32_t unused;
	float viewportscale; // For scrolling on an overlay with laser mouse, this is the overlay's vertical size relative to the overlay height. Range: [0,1]
};

/** when in mouse input mode you can receive data from the touchpad, these events are only sent if the users finger
   is on the touchpad (or just released from it). These events are sent to overlays with the VROverlayFlags_SendVRTouchpadEvents
   flag set.
**/
struct VREvent_TouchPadMove_t
{
	// true if the users finger is detected on the touch pad
	bool bFingerDown;

	// How long the finger has been down in seconds
	float flSecondsFingerDown;

	// These values indicate the starting finger position (so you can do some basic swipe stuff)
	float fValueXFirst;
	float fValueYFirst;

	// This is the raw sampled coordinate without deadzoning
	float fValueXRaw;
	float fValueYRaw;
};

/** notification related events. Details will still change at this point */
struct VREvent_Notification_t
{
	uint64_t ulUserValue;
	uint32_t notificationId;
};

/** Used for events about processes */
struct VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	// If the associated event was triggered by a connection loss
	bool bConnectionLost;
};


/** Used for a few events about overlays */
struct VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t devicePath;
	uint64_t memoryBlockId;
};


/** Used for a few events about overlays */
struct VREvent_Status_t
{
	uint32_t statusState; // EVRState enum
};

/** Used for keyboard events **/
struct VREvent_Keyboard_t
{
	char cNewInput[8];	// Up to 11 bytes of new input
	uint64_t uUserValue;	// Possible flags about the new input
};

struct VREvent_Ipd_t
{
	float ipdMeters;
};

struct VREvent_Chaperone_t
{
	uint64_t m_nPreviousUniverse;
	uint64_t m_nCurrentUniverse;
};

/** Not actually used for any events */
struct VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
	uint64_t reserved2;
	uint64_t reserved3;
	uint64_t reserved4;
	uint64_t reserved5;
};

struct VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
};

struct VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
};

struct VREvent_Screenshot_t
{
	uint32_t handle;
	uint32_t type;
};

struct VREvent_ScreenshotProgress_t
{
	float progress;
};

struct VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t unArgsHandle;
};

struct VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t nVisualMode;
};

struct VREvent_MessageOverlay_t
{
	uint32_t unVRMessageOverlayResponse; // vr::VRMessageOverlayResponse enum
};

struct VREvent_Property_t
{
	PropertyContainerHandle_t container;
	ETrackedDeviceProperty prop;
};

struct VREvent_HapticVibration_t
{
	uint64_t containerHandle; // property container handle of the device with the haptic component
	uint64_t componentHandle; // Which haptic component needs to vibrate
	float fDurationSeconds;
	float fFrequency;
	float fAmplitude;
};

struct VREvent_WebConsole_t
{
	WebConsoleHandle_t webConsoleHandle;
};

struct VREvent_InputBindingLoad_t
{
	vr::PropertyContainerHandle_t ulAppContainer;
	uint64_t pathMessage;
	uint64_t pathUrl;
	uint64_t pathControllerType;
};

struct VREvent_InputActionManifestLoad_t
{
	uint64_t pathAppKey;
	uint64_t pathMessage;
	uint64_t pathMessageParam;
	uint64_t pathManifestPath;
};

struct VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
};

struct VREvent_ProgressUpdate_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t pathDevice;
	uint64_t pathInputSource;
	uint64_t pathProgressAction;
	uint64_t pathIcon;
	float fProgress;
};

enum EShowUIType
{
	ShowUI_ControllerBinding = 0,
	ShowUI_ManageTrackers = 1,
	// ShowUI_QuickStart = 2, // Deprecated
	ShowUI_Pairing = 3,
	ShowUI_Settings = 4,
	ShowUI_DebugCommands = 5,
	ShowUI_FullControllerBinding = 6,
	ShowUI_ManageDrivers = 7,
};

struct VREvent_ShowUI_t
{
	EShowUIType eType;
};

struct VREvent_ShowDevTools_t
{
	int32_t nBrowserIdentifier;
};

enum EHDCPError
{
	HDCPError_None = 0,
	HDCPError_LinkLost = 1,
	HDCPError_Tampered = 2,
	HDCPError_DeviceRevoked = 3,
	HDCPError_Unknown = 4
};

struct VREvent_HDCPError_t
{
	EHDCPError eCode;
};

typedef union
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Scroll_t scroll;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_Status_t status;
	VREvent_Keyboard_t keyboard;
	VREvent_Ipd_t ipd;
	VREvent_Chaperone_t chaperone;
	VREvent_PerformanceTest_t performanceTest;
	VREvent_TouchPadMove_t touchPadMove;
	VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
	VREvent_Screenshot_t screenshot;
	VREvent_ScreenshotProgress_t screenshotProgress;
	VREvent_ApplicationLaunch_t applicationLaunch;
	VREvent_EditingCameraSurface_t cameraSurface;
	VREvent_MessageOverlay_t messageOverlay;
	VREvent_Property_t property;
	VREvent_HapticVibration_t hapticVibration;
	VREvent_WebConsole_t webConsole;
	VREvent_InputBindingLoad_t inputBinding;
	VREvent_InputActionManifestLoad_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
	VREvent_ProgressUpdate_t progressUpdate;
	VREvent_ShowUI_t showUi;
	VREvent_ShowDevTools_t showDevTools;
	VREvent_HDCPError_t hdcpError;
    /** NOTE!!! If you change this you MUST manually update openvr_interop.cs.py */
} VREvent_Data_t;


#if defined(__linux__) || defined(__APPLE__)
// This structure was originally defined mis-packed on Linux, preserved for
// compatibility.
#pragma pack( push, 4 )
#endif

/** An event posted by the server to all running applications */
struct VREvent_t
{
	uint32_t eventType; // EVREventType enum
	TrackedDeviceIndex_t trackedDeviceIndex;
	float eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_Data_t data;
};

#if defined(__linux__) || defined(__APPLE__)
#pragma pack( pop )
#endif

typedef uint32_t VRComponentProperties;

enum EVRComponentProperty
{
	VRComponentProperty_IsStatic = (1 << 0),
	VRComponentProperty_IsVisible = (1 << 1),
	VRComponentProperty_IsTouched = (1 << 2),
	VRComponentProperty_IsPressed = (1 << 3),
	VRComponentProperty_IsScrolled = (1 << 4),
	VRComponentProperty_IsHighlighted = (1 << 5),
};


/** Describes state information about a render-model component, including transforms and other dynamic properties */
struct RenderModel_ComponentState_t
{
	HmdMatrix34_t mTrackingToComponentRenderModel;  // Transform required when drawing the component render model
	HmdMatrix34_t mTrackingToComponentLocal;        // Transform available for attaching to a local component coordinate system (-Z out from surface )
	VRComponentProperties uProperties;
};


enum EVRInputError
{
	VRInputError_None = 0,
	VRInputError_NameNotFound = 1,
	VRInputError_WrongType = 2,
	VRInputError_InvalidHandle = 3,
	VRInputError_InvalidParam = 4,
	VRInputError_NoSteam = 5,
	VRInputError_MaxCapacityReached = 6,
	VRInputError_IPCError = 7,
	VRInputError_NoActiveActionSet = 8,
	VRInputError_InvalidDevice = 9,
	VRInputError_InvalidSkeleton = 10,
	VRInputError_InvalidBoneCount = 11,
	VRInputError_InvalidCompressedData = 12,
	VRInputError_NoData = 13,
	VRInputError_BufferTooSmall = 14,
	VRInputError_MismatchedActionManifest = 15,
	VRInputError_MissingSkeletonData = 16,
	VRInputError_InvalidBoneIndex = 17,
	VRInputError_InvalidPriority = 18,
	VRInputError_PermissionDenied = 19,
	VRInputError_InvalidRenderModel = 20,
};

enum EVRSpatialAnchorError
{
	VRSpatialAnchorError_Success = 0,
	VRSpatialAnchorError_Internal = 1,
	VRSpatialAnchorError_UnknownHandle = 2,
	VRSpatialAnchorError_ArrayTooSmall = 3,
	VRSpatialAnchorError_InvalidDescriptorChar = 4,
	VRSpatialAnchorError_NotYetAvailable = 5,
	VRSpatialAnchorError_NotAvailableInThisUniverse = 6,
	VRSpatialAnchorError_PermanentlyUnavailable = 7,
	VRSpatialAnchorError_WrongDriver = 8,
	VRSpatialAnchorError_DescriptorTooLong = 9,
	VRSpatialAnchorError_Unknown = 10,
	VRSpatialAnchorError_NoRoomCalibration = 11,
	VRSpatialAnchorError_InvalidArgument = 12,
	VRSpatialAnchorError_UnknownDriver = 13,
};

/** The mesh to draw into the stencil (or depth) buffer to perform
* early stencil (or depth) kills of pixels that will never appear on the HMD.
* This mesh draws on all the pixels that will be hidden after distortion.
*
* If the HMD does not provide a visible area mesh pVertexData will be
* NULL and unTriangleCount will be 0. */
struct HiddenAreaMesh_t
{
	const HmdVector2_t *pVertexData;
	uint32_t unTriangleCount;
};


enum EHiddenAreaMeshType
{
	k_eHiddenAreaMesh_Standard = 0,
	k_eHiddenAreaMesh_Inverse = 1,
	k_eHiddenAreaMesh_LineLoop = 2,

	k_eHiddenAreaMesh_Max = 3,
};


/** Identifies what kind of axis is on the controller at index n. Read this type
* with pVRSystem->Get( nControllerDeviceIndex, Prop_Axis0Type_Int32 + n );
*/
enum EVRControllerAxisType
{
	k_eControllerAxis_None = 0,
	k_eControllerAxis_TrackPad = 1,
	k_eControllerAxis_Joystick = 2,
	k_eControllerAxis_Trigger = 3, // Analog trigger data is in the X axis
};


/** contains information about one axis on the controller */
struct VRControllerAxis_t
{
	float x; // Ranges from -1.0 to 1.0 for joysticks and track pads. Ranges from 0.0 to 1.0 for triggers were 0 is fully released.
	float y; // Ranges from -1.0 to 1.0 for joysticks and track pads. Is always 0.0 for triggers.
};


/** the number of axes in the controller state */
static const uint32_t k_unControllerStateAxisCount = 5;


#if defined(__linux__) || defined(__APPLE__)
// This structure was originally defined mis-packed on Linux, preserved for
// compatibility.
#pragma pack( push, 4 )
#endif

/** Holds all the state of a controller at one moment in time. */
struct VRControllerState001_t
{
	// If packet num matches that on your prior call, then the controller state hasn't been changed since
	// your last call and there is no need to process it
	uint32_t unPacketNum;

	// bit flags for each of the buttons. Use ButtonMaskFromId to turn an ID into a mask
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;

	// Axis data for the controller's analog inputs
	VRControllerAxis_t rAxis[ k_unControllerStateAxisCount ];
};
#if defined(__linux__) || defined(__APPLE__)
#pragma pack( pop )
#endif


typedef VRControllerState001_t VRControllerState_t;


/** determines how to provide output to the application of various event processing functions. */
enum EVRControllerEventOutputType
{
	ControllerEventOutput_OSEvents = 0,
	ControllerEventOutput_VREvents = 1,
};



/** Collision Bounds Style */
enum ECollisionBoundsStyle
{
	COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	COLLISION_BOUNDS_STYLE_INTERMEDIATE,
	COLLISION_BOUNDS_STYLE_SQUARES,
	COLLISION_BOUNDS_STYLE_ADVANCED,
	COLLISION_BOUNDS_STYLE_NONE,

	COLLISION_BOUNDS_STYLE_COUNT
};

/** used to refer to a single VR overlay */
typedef uint64_t VROverlayHandle_t;

static const VROverlayHandle_t k_ulOverlayHandleInvalid = 0;

/** Errors that can occur around VR overlays */
enum EVROverlayError
{
	VROverlayError_None						= 0,

	VROverlayError_UnknownOverlay			= 10,
	VROverlayError_InvalidHandle			= 11,
	VROverlayError_PermissionDenied			= 12,
	VROverlayError_OverlayLimitExceeded		= 13, // No more overlays could be created because the maximum number already exist
	VROverlayError_WrongVisibilityType		= 14,
	VROverlayError_KeyTooLong				= 15,
	VROverlayError_NameTooLong				= 16,
	VROverlayError_KeyInUse					= 17,
	VROverlayError_WrongTransformType		= 18,
	VROverlayError_InvalidTrackedDevice		= 19,
	VROverlayError_InvalidParameter			= 20,
	VROverlayError_ThumbnailCantBeDestroyed	= 21,
	VROverlayError_ArrayTooSmall			= 22,
	VROverlayError_RequestFailed			= 23,
	VROverlayError_InvalidTexture			= 24,
	VROverlayError_UnableToLoadFile			= 25,
	VROverlayError_KeyboardAlreadyInUse		= 26,
	VROverlayError_NoNeighbor				= 27,
	VROverlayError_TooManyMaskPrimitives	= 29,
	VROverlayError_BadMaskPrimitive			= 30,
	VROverlayError_TextureAlreadyLocked		= 31,
	VROverlayError_TextureLockCapacityReached = 32,
	VROverlayError_TextureNotLocked			= 33,
};

/** enum values to pass in to VR_Init to identify whether the application will
* draw a 3D scene. */
enum EVRApplicationType
{
	VRApplication_Other = 0,		// Some other kind of application that isn't covered by the other entries
	VRApplication_Scene	= 1,		// Application will submit 3D frames
	VRApplication_Overlay = 2,		// Application only interacts with overlays
	VRApplication_Background = 3,	// Application should not start SteamVR if it's not already running, and should not
									// keep it running if everything else quits.
	VRApplication_Utility = 4,		// Init should not try to load any drivers. The application needs access to utility
									// interfaces (like IVRSettings and IVRApplications) but not hardware.
	VRApplication_VRMonitor = 5,	// Reserved for vrmonitor
	VRApplication_SteamWatchdog = 6,// Reserved for Steam
	VRApplication_Bootstrapper = 7, // reserved for vrstartup
	VRApplication_WebHelper = 8,	// reserved for vrwebhelper
	VRApplication_OpenXRInstance = 9, // reserved for openxr (created instance, but not session yet)
	VRApplication_OpenXRScene = 10,	  // reserved for openxr (started session)
	VRApplication_OpenXROverlay = 11, // reserved for openxr (started overlay session)
	VRApplication_Prism = 12,		// reserved for the vrprismhost process

	VRApplication_Max
};


/** returns true if the specified application type is one of the
* OpenXR types */
inline bool IsOpenXRAppType( EVRApplicationType eType )
{
	return eType == VRApplication_OpenXRInstance
		|| eType == VRApplication_OpenXRScene
		|| eType == VRApplication_OpenXROverlay;
}


/** error codes for firmware */
enum EVRFirmwareError
{
	VRFirmwareError_None = 0,
	VRFirmwareError_Success = 1,
	VRFirmwareError_Fail = 2,
};


/** error codes for notifications */
enum EVRNotificationError
{
	VRNotificationError_OK = 0,
	VRNotificationError_InvalidNotificationId = 100,
	VRNotificationError_NotificationQueueFull = 101,
	VRNotificationError_InvalidOverlayHandle = 102,
	VRNotificationError_SystemWithUserValueAlreadyExists = 103,
};


enum EVRSkeletalMotionRange
{
	// The range of motion of the skeleton takes into account any physical limits imposed by
	// the controller itself.  This will tend to be the most accurate pose compared to the user's
	// actual hand pose, but might not allow a closed fist for example
	VRSkeletalMotionRange_WithController = 0,

	// Retarget the range of motion provided by the input device to make the hand appear to move
	// as if it was not holding a controller.  eg: map "hand grasping controller" to "closed fist"
	VRSkeletalMotionRange_WithoutController = 1,
};

enum EVRSkeletalTrackingLevel
{
	// body part location can't be directly determined by the device. Any skeletal pose provided by
	// the device is estimated by assuming the position required to active buttons, triggers, joysticks,
	// or other input sensors.
	// E.g. Vive Controller, Gamepad
	VRSkeletalTracking_Estimated = 0,

	// body part location can be measured directly but with fewer degrees of freedom than the actual body
	// part. Certain body part positions may be unmeasured by the device and estimated from other input data.
	// E.g. Index Controllers, gloves that only measure finger curl
	VRSkeletalTracking_Partial = 1,

	// Body part location can be measured directly throughout the entire range of motion of the body part.
	// E.g. Mocap suit for the full body, gloves that measure rotation of each finger segment
	VRSkeletalTracking_Full = 2,

	VRSkeletalTrackingLevel_Count,
	VRSkeletalTrackingLevel_Max = VRSkeletalTrackingLevel_Count - 1
};


/** Type used for referring to bones by their index */
typedef int32_t BoneIndex_t;
const BoneIndex_t k_unInvalidBoneIndex = -1;


/** error codes returned by Vr_Init */

// Please add adequate error description to https://developer.valvesoftware.com/w/index.php?title=Category:SteamVRHelp
enum EVRInitError
{
	VRInitError_None	= 0,
	VRInitError_Unknown = 1,

	VRInitError_Init_InstallationNotFound			= 100,
	VRInitError_Init_InstallationCorrupt			= 101,
	VRInitError_Init_VRClientDLLNotFound			= 102,
	VRInitError_Init_FileNotFound					= 103,
	VRInitError_Init_FactoryNotFound				= 104,
	VRInitError_Init_InterfaceNotFound				= 105,
	VRInitError_Init_InvalidInterface				= 106,
	VRInitError_Init_UserConfigDirectoryInvalid		= 107,
	VRInitError_Init_HmdNotFound					= 108,
	VRInitError_Init_NotInitialized					= 109,
	VRInitError_Init_PathRegistryNotFound			= 110,
	VRInitError_Init_NoConfigPath					= 111,
	VRInitError_Init_NoLogPath						= 112,
	VRInitError_Init_PathRegistryNotWritable		= 113,
	VRInitError_Init_AppInfoInitFailed				= 114,
	VRInitError_Init_Retry							= 115, // Used internally to cause retries to vrserver
	VRInitError_Init_InitCanceledByUser				= 116, // The calling application should silently exit. The user canceled app startup
	VRInitError_Init_AnotherAppLaunching			= 117,
	VRInitError_Init_SettingsInitFailed				= 118,
	VRInitError_Init_ShuttingDown					= 119,
	VRInitError_Init_TooManyObjects					= 120,
	VRInitError_Init_NoServerForBackgroundApp		= 121,
	VRInitError_Init_NotSupportedWithCompositor		= 122,
	VRInitError_Init_NotAvailableToUtilityApps		= 123,
	VRInitError_Init_Internal				 		= 124,
	VRInitError_Init_HmdDriverIdIsNone		 		= 125,
	VRInitError_Init_HmdNotFoundPresenceFailed 		= 126,
	VRInitError_Init_VRMonitorNotFound				= 127,
	VRInitError_Init_VRMonitorStartupFailed			= 128,
	VRInitError_Init_LowPowerWatchdogNotSupported	= 129,
	VRInitError_Init_InvalidApplicationType			= 130,
	VRInitError_Init_NotAvailableToWatchdogApps		= 131,
	VRInitError_Init_WatchdogDisabledInSettings		= 132,
	VRInitError_Init_VRDashboardNotFound			= 133,
	VRInitError_Init_VRDashboardStartupFailed		= 134,
	VRInitError_Init_VRHomeNotFound					= 135,
	VRInitError_Init_VRHomeStartupFailed			= 136,
	VRInitError_Init_RebootingBusy					= 137,
	VRInitError_Init_FirmwareUpdateBusy				= 138,
	VRInitError_Init_FirmwareRecoveryBusy			= 139,
	VRInitError_Init_USBServiceBusy					= 140,
	VRInitError_Init_VRWebHelperStartupFailed		= 141,
	VRInitError_Init_TrackerManagerInitFailed		= 142,
	VRInitError_Init_AlreadyRunning					= 143,
	VRInitError_Init_FailedForVrMonitor				= 144,
	VRInitError_Init_PropertyManagerInitFailed		= 145,
	VRInitError_Init_WebServerFailed				= 146,
	VRInitError_Init_IllegalTypeTransition			= 147,
	VRInitError_Init_MismatchedRuntimes				= 148,
	VRInitError_Init_InvalidProcessId				= 149,
	VRInitError_Init_VRServiceStartupFailed			= 150,
	VRInitError_Init_PrismNeedsNewDrivers			= 151,
	VRInitError_Init_PrismStartupTimedOut			= 152,
	VRInitError_Init_CouldNotStartPrism				= 153,
	VRInitError_Init_CreateDriverDirectDeviceFailed = 154,
	VRInitError_Init_PrismExitedUnexpectedly		= 155,

	VRInitError_Driver_Failed						= 200,
	VRInitError_Driver_Unknown						= 201,
	VRInitError_Driver_HmdUnknown					= 202,
	VRInitError_Driver_NotLoaded					= 203,
	VRInitError_Driver_RuntimeOutOfDate				= 204,
	VRInitError_Driver_HmdInUse						= 205,
	VRInitError_Driver_NotCalibrated				= 206,
	VRInitError_Driver_CalibrationInvalid			= 207,
	VRInitError_Driver_HmdDisplayNotFound			= 208,
	VRInitError_Driver_TrackedDeviceInterfaceUnknown = 209,
	// VRInitError_Driver_HmdDisplayNotFoundAfterFix = 210, // not needed: here for historic reasons
	VRInitError_Driver_HmdDriverIdOutOfBounds		= 211,
	VRInitError_Driver_HmdDisplayMirrored			= 212,
	VRInitError_Driver_HmdDisplayNotFoundLaptop		= 213,
	// Never make error 259 because we return it from main and it would conflict with STILL_ACTIVE

	VRInitError_IPC_ServerInitFailed				= 300,
	VRInitError_IPC_ConnectFailed					= 301,
	VRInitError_IPC_SharedStateInitFailed			= 302,
	VRInitError_IPC_CompositorInitFailed			= 303,
	VRInitError_IPC_MutexInitFailed					= 304,
	VRInitError_IPC_Failed							= 305,
	VRInitError_IPC_CompositorConnectFailed			= 306,
	VRInitError_IPC_CompositorInvalidConnectResponse = 307,
	VRInitError_IPC_ConnectFailedAfterMultipleAttempts = 308,
	VRInitError_IPC_ConnectFailedAfterTargetExited = 309,
	VRInitError_IPC_NamespaceUnavailable			 = 310,

	VRInitError_Compositor_Failed												= 400,
	VRInitError_Compositor_D3D11HardwareRequired								= 401,
	VRInitError_Compositor_FirmwareRequiresUpdate								= 402,
	VRInitError_Compositor_OverlayInitFailed									= 403,
	VRInitError_Compositor_ScreenshotsInitFailed								= 404,
	VRInitError_Compositor_UnableToCreateDevice									= 405,
	VRInitError_Compositor_SharedStateIsNull									= 406,
	VRInitError_Compositor_NotificationManagerIsNull							= 407,
	VRInitError_Compositor_ResourceManagerClientIsNull							= 408,
	VRInitError_Compositor_MessageOverlaySharedStateInitFailure					= 409,
	VRInitError_Compositor_PropertiesInterfaceIsNull							= 410,
	VRInitError_Compositor_CreateFullscreenWindowFailed							= 411,
	VRInitError_Compositor_SettingsInterfaceIsNull								= 412,
	VRInitError_Compositor_FailedToShowWindow									= 413,
	VRInitError_Compositor_DistortInterfaceIsNull								= 414,
	VRInitError_Compositor_DisplayFrequencyFailure								= 415,
	VRInitError_Compositor_RendererInitializationFailed							= 416,
	VRInitError_Compositor_DXGIFactoryInterfaceIsNull							= 417,
	VRInitError_Compositor_DXGIFactoryCreateFailed								= 418,
	VRInitError_Compositor_DXGIFactoryQueryFailed								= 419,
	VRInitError_Compositor_InvalidAdapterDesktop								= 420,
	VRInitError_Compositor_InvalidHmdAttachment									= 421,
	VRInitError_Compositor_InvalidOutputDesktop									= 422,
	VRInitError_Compositor_InvalidDeviceProvided								= 423,
	VRInitError_Compositor_D3D11RendererInitializationFailed					= 424,
	VRInitError_Compositor_FailedToFindDisplayMode								= 425,
	VRInitError_Compositor_FailedToCreateSwapChain								= 426,
	VRInitError_Compositor_FailedToGetBackBuffer								= 427,
	VRInitError_Compositor_FailedToCreateRenderTarget							= 428,
	VRInitError_Compositor_FailedToCreateDXGI2SwapChain							= 429,
	VRInitError_Compositor_FailedtoGetDXGI2BackBuffer							= 430,
	VRInitError_Compositor_FailedToCreateDXGI2RenderTarget						= 431,
	VRInitError_Compositor_FailedToGetDXGIDeviceInterface						= 432,
	VRInitError_Compositor_SelectDisplayMode									= 433,
	VRInitError_Compositor_FailedToCreateNvAPIRenderTargets						= 434,
	VRInitError_Compositor_NvAPISetDisplayMode									= 435,
	VRInitError_Compositor_FailedToCreateDirectModeDisplay						= 436,
	VRInitError_Compositor_InvalidHmdPropertyContainer							= 437,
	VRInitError_Compositor_UpdateDisplayFrequency								= 438,
	VRInitError_Compositor_CreateRasterizerState								= 439,
	VRInitError_Compositor_CreateWireframeRasterizerState						= 440,
	VRInitError_Compositor_CreateSamplerState									= 441,
	VRInitError_Compositor_CreateClampToBorderSamplerState						= 442,
	VRInitError_Compositor_CreateAnisoSamplerState								= 443,
	VRInitError_Compositor_CreateOverlaySamplerState							= 444,
	VRInitError_Compositor_CreatePanoramaSamplerState							= 445,
	VRInitError_Compositor_CreateFontSamplerState								= 446,
	VRInitError_Compositor_CreateNoBlendState									= 447,
	VRInitError_Compositor_CreateBlendState										= 448,
	VRInitError_Compositor_CreateAlphaBlendState								= 449,
	VRInitError_Compositor_CreateBlendStateMaskR								= 450,
	VRInitError_Compositor_CreateBlendStateMaskG								= 451,
	VRInitError_Compositor_CreateBlendStateMaskB								= 452,
	VRInitError_Compositor_CreateDepthStencilState								= 453,
	VRInitError_Compositor_CreateDepthStencilStateNoWrite						= 454,
	VRInitError_Compositor_CreateDepthStencilStateNoDepth						= 455,
	VRInitError_Compositor_CreateFlushTexture									= 456,
	VRInitError_Compositor_CreateDistortionSurfaces								= 457,
	VRInitError_Compositor_CreateConstantBuffer									= 458,
	VRInitError_Compositor_CreateHmdPoseConstantBuffer							= 459,
	VRInitError_Compositor_CreateHmdPoseStagingConstantBuffer					= 460,
	VRInitError_Compositor_CreateSharedFrameInfoConstantBuffer					= 461,
	VRInitError_Compositor_CreateOverlayConstantBuffer							= 462,
	VRInitError_Compositor_CreateSceneTextureIndexConstantBuffer				= 463,
	VRInitError_Compositor_CreateReadableSceneTextureIndexConstantBuffer		= 464,
	VRInitError_Compositor_CreateLayerGraphicsTextureIndexConstantBuffer		= 465,
	VRInitError_Compositor_CreateLayerComputeTextureIndexConstantBuffer			= 466,
	VRInitError_Compositor_CreateLayerComputeSceneTextureIndexConstantBuffer	= 467,
	VRInitError_Compositor_CreateComputeHmdPoseConstantBuffer					= 468,
	VRInitError_Compositor_CreateGeomConstantBuffer								= 469,
	VRInitError_Compositor_CreatePanelMaskConstantBuffer						= 470,
	VRInitError_Compositor_CreatePixelSimUBO									= 471,
	VRInitError_Compositor_CreateMSAARenderTextures								= 472,
	VRInitError_Compositor_CreateResolveRenderTextures							= 473,
	VRInitError_Compositor_CreateComputeResolveRenderTextures					= 474,
	VRInitError_Compositor_CreateDriverDirectModeResolveTextures				= 475,
	VRInitError_Compositor_OpenDriverDirectModeResolveTextures					= 476,
	VRInitError_Compositor_CreateFallbackSyncTexture							= 477,
	VRInitError_Compositor_ShareFallbackSyncTexture								= 478,
	VRInitError_Compositor_CreateOverlayIndexBuffer								= 479,
	VRInitError_Compositor_CreateOverlayVertexBuffer							= 480,
	VRInitError_Compositor_CreateTextVertexBuffer								= 481,
	VRInitError_Compositor_CreateTextIndexBuffer								= 482,
	VRInitError_Compositor_CreateMirrorTextures									= 483,
	VRInitError_Compositor_CreateLastFrameRenderTexture							= 484,
	VRInitError_Compositor_CreateMirrorOverlay									= 485,
	VRInitError_Compositor_FailedToCreateVirtualDisplayBackbuffer				= 486,
	VRInitError_Compositor_DisplayModeNotSupported								= 487,
	VRInitError_Compositor_CreateOverlayInvalidCall								= 488,
	VRInitError_Compositor_CreateOverlayAlreadyInitialized						= 489,
	VRInitError_Compositor_FailedToCreateMailbox								= 490,
	VRInitError_Compositor_WindowInterfaceIsNull								= 491,
	VRInitError_Compositor_SystemLayerCreateInstance							= 492,
	VRInitError_Compositor_SystemLayerCreateSession								= 493,

	VRInitError_VendorSpecific_UnableToConnectToOculusRuntime		= 1000,
	VRInitError_VendorSpecific_WindowsNotInDevMode					= 1001,

	VRInitError_VendorSpecific_HmdFound_CantOpenDevice 				= 1101,
	VRInitError_VendorSpecific_HmdFound_UnableToRequestConfigStart	= 1102,
	VRInitError_VendorSpecific_HmdFound_NoStoredConfig 				= 1103,
	VRInitError_VendorSpecific_HmdFound_ConfigTooBig 				= 1104,
	VRInitError_VendorSpecific_HmdFound_ConfigTooSmall 				= 1105,
	VRInitError_VendorSpecific_HmdFound_UnableToInitZLib 			= 1106,
	VRInitError_VendorSpecific_HmdFound_CantReadFirmwareVersion 	= 1107,
	VRInitError_VendorSpecific_HmdFound_UnableToSendUserDataStart	= 1108,
	VRInitError_VendorSpecific_HmdFound_UnableToGetUserDataStart	= 1109,
	VRInitError_VendorSpecific_HmdFound_UnableToGetUserDataNext		= 1110,
	VRInitError_VendorSpecific_HmdFound_UserDataAddressRange		= 1111,
	VRInitError_VendorSpecific_HmdFound_UserDataError				= 1112,
	VRInitError_VendorSpecific_HmdFound_ConfigFailedSanityCheck		= 1113,
	VRInitError_VendorSpecific_OculusRuntimeBadInstall				= 1114,

	VRInitError_Steam_SteamInstallationNotFound = 2000,

	// Strictly a placeholder
	VRInitError_LastError
};

enum EVRScreenshotType
{
	VRScreenshotType_None = 0,
	VRScreenshotType_Mono = 1, // left eye only
	VRScreenshotType_Stereo = 2,
	VRScreenshotType_Cubemap = 3,
	VRScreenshotType_MonoPanorama = 4,
	VRScreenshotType_StereoPanorama = 5
};

enum EVRScreenshotPropertyFilenames
{
	VRScreenshotPropertyFilenames_Preview = 0,
	VRScreenshotPropertyFilenames_VR = 1,
};

enum EVRTrackedCameraError
{
	VRTrackedCameraError_None                       = 0,
	VRTrackedCameraError_OperationFailed            = 100,
	VRTrackedCameraError_InvalidHandle              = 101,
	VRTrackedCameraError_InvalidFrameHeaderVersion  = 102,
	VRTrackedCameraError_OutOfHandles               = 103,
	VRTrackedCameraError_IPCFailure                 = 104,
	VRTrackedCameraError_NotSupportedForThisDevice  = 105,
	VRTrackedCameraError_SharedMemoryFailure        = 106,
	VRTrackedCameraError_FrameBufferingFailure      = 107,
	VRTrackedCameraError_StreamSetupFailure         = 108,
	VRTrackedCameraError_InvalidGLTextureId         = 109,
	VRTrackedCameraError_InvalidSharedTextureHandle = 110,
	VRTrackedCameraError_FailedToGetGLTextureId     = 111,
	VRTrackedCameraError_SharedTextureFailure       = 112,
	VRTrackedCameraError_NoFrameAvailable           = 113,
	VRTrackedCameraError_InvalidArgument            = 114,
	VRTrackedCameraError_InvalidFrameBufferSize     = 115,
};

enum EVRTrackedCameraFrameLayout
{
	EVRTrackedCameraFrameLayout_Mono				= 0x0001,
	EVRTrackedCameraFrameLayout_Stereo				= 0x0002,
	EVRTrackedCameraFrameLayout_VerticalLayout		= 0x0010,	// Stereo frames are Top/Bottom (left/right)
	EVRTrackedCameraFrameLayout_HorizontalLayout	= 0x0020,	// Stereo frames are Left/Right
};

enum EVRTrackedCameraFrameType
{
	VRTrackedCameraFrameType_Distorted = 0,			// This is the camera video frame size in pixels, still distorted.
	VRTrackedCameraFrameType_Undistorted,			// In pixels, an undistorted inscribed rectangle region without invalid regions. This size is subject to changes shortly.
	VRTrackedCameraFrameType_MaximumUndistorted,	// In pixels, maximum undistorted with invalid regions. Non zero alpha component identifies valid regions.
	MAX_CAMERA_FRAME_TYPES
};

enum EVRDistortionFunctionType
{
	VRDistortionFunctionType_None,
	VRDistortionFunctionType_FTheta,
	VRDistortionFunctionType_Extended_FTheta,
	MAX_DISTORTION_FUNCTION_TYPES,
};

static const uint32_t k_unMaxDistortionFunctionParameters = 8;

typedef uint64_t TrackedCameraHandle_t;
#define INVALID_TRACKED_CAMERA_HANDLE	((vr::TrackedCameraHandle_t)0)

struct CameraVideoStreamFrameHeader_t
{
	EVRTrackedCameraFrameType eFrameType;

	uint32_t nWidth;
	uint32_t nHeight;
	uint32_t nBytesPerPixel;

	uint32_t nFrameSequence;

	TrackedDevicePose_t trackedDevicePose;

	uint64_t ulFrameExposureTime;						// mid-point of the exposure of the image in host system ticks
};

// Screenshot types
typedef uint32_t ScreenshotHandle_t;

static const uint32_t k_unScreenshotHandleInvalid = 0;

/** Compositor frame timing reprojection flags. */
const uint32_t VRCompositor_ReprojectionReason_Cpu = 0x01;
const uint32_t VRCompositor_ReprojectionReason_Gpu = 0x02;
const uint32_t VRCompositor_ReprojectionAsync = 0x04;	// This flag indicates the async reprojection mode is active,
															// but does not indicate if reprojection actually happened or not.
															// Use the ReprojectionReason flags above to check if reprojection
															// was actually applied (i.e. scene texture was reused).
															// NumFramePresents > 1 also indicates the scene texture was reused,
															// and also the number of times that it was presented in total.

const uint32_t VRCompositor_ReprojectionMotion = 0x08;	// This flag indicates whether or not motion smoothing was triggered for this frame

const uint32_t VRCompositor_PredictionMask = 0xF0;	// The runtime may predict more than one frame (up to four) ahead if
															// it detects the application is taking too long to render. These two
															// bits will contain the count of additional frames (normally zero).
															// Use the VR_COMPOSITOR_ADDITIONAL_PREDICTED_FRAMES macro to read from
															// the latest frame timing entry.

const uint32_t VRCompositor_ThrottleMask = 0xF00;	// Number of frames the compositor is throttling the application.
															// Use the VR_COMPOSITOR_NUMBER_OF_THROTTLED_FRAMES macro to read from
															// the latest frame timing entry.

#define VR_COMPOSITOR_ADDITIONAL_PREDICTED_FRAMES( timing ) ( ( ( timing ).m_nReprojectionFlags & vr::VRCompositor_PredictionMask ) >> 4 )
#define VR_COMPOSITOR_NUMBER_OF_THROTTLED_FRAMES( timing ) ( ( ( timing ).m_nReprojectionFlags & vr::VRCompositor_ThrottleMask ) >> 8 )

/** Provides a single frame's timing information to the app */
struct Compositor_FrameTiming
{
	uint32_t m_nSize; // Set to sizeof( Compositor_FrameTiming )
	uint32_t m_nFrameIndex;
	uint32_t m_nNumFramePresents; // number of times this frame was presented
	uint32_t m_nNumMisPresented; // number of times this frame was presented on a vsync other than it was originally predicted to
	uint32_t m_nNumDroppedFrames; // number of additional times previous frame was scanned out
	uint32_t m_nReprojectionFlags;

	/** Absolute time reference for comparing frames.  This aligns with the vsync that running start is relative to. */
	double m_flSystemTimeInSeconds;

	/** These times may include work from other processes due to OS scheduling.
	* The fewer packets of work these are broken up into, the less likely this will happen.
	* GPU work can be broken up by calling Flush.  This can sometimes be useful to get the GPU started
	* processing that work earlier in the frame. */
	float m_flPreSubmitGpuMs; // time spent rendering the scene (gpu work submitted between WaitGetPoses and second Submit)
	float m_flPostSubmitGpuMs; // additional time spent rendering by application (e.g. companion window)
	float m_flTotalRenderGpuMs; // time between work submitted immediately after present (ideally vsync) until the end of compositor submitted work
	float m_flCompositorRenderGpuMs; // time spend performing distortion correction, rendering chaperone, overlays, etc.
	float m_flCompositorRenderCpuMs; // time spent on cpu submitting the above work for this frame
	float m_flCompositorIdleCpuMs; // time spent waiting for running start (application could have used this much more time)

	/** Miscellaneous measured intervals. */
	float m_flClientFrameIntervalMs; // time between calls to WaitGetPoses
	float m_flPresentCallCpuMs; // time blocked on call to present (usually 0.0, but can go long)
	float m_flWaitForPresentCpuMs; // time spent spin-waiting for frame index to change (not near-zero indicates wait object failure)
	float m_flSubmitFrameMs; // time spent in IVRCompositor::Submit (not near-zero indicates driver issue)

	/** The following are all relative to this frame's SystemTimeInSeconds */
	float m_flWaitGetPosesCalledMs;
	float m_flNewPosesReadyMs;
	float m_flNewFrameReadyMs; // second call to IVRCompositor::Submit
	float m_flCompositorUpdateStartMs;
	float m_flCompositorUpdateEndMs;
	float m_flCompositorRenderStartMs;

	vr::TrackedDevicePose_t m_HmdPose; // pose used by app to render this frame

	uint32_t m_nNumVSyncsReadyForUse;
	uint32_t m_nNumVSyncsToFirstView;
};

/** Provides compositor benchmark results to the app */
struct Compositor_BenchmarkResults
{
	float m_flMegaPixelsPerSecond; // Measurement of GPU MP/s performed by compositor benchmark
	float m_flHmdRecommendedMegaPixelsPerSecond; // Recommended default MP/s given the HMD resolution, refresh, and panel mask.
};

/** Frame timing data provided by direct mode drivers. */
struct DriverDirectMode_FrameTiming
{
	uint32_t m_nSize; // Set to sizeof( DriverDirectMode_FrameTiming )
	uint32_t m_nNumFramePresents; // number of times frame was presented
	uint32_t m_nNumMisPresented; // number of times frame was presented on a vsync other than it was originally predicted to
	uint32_t m_nNumDroppedFrames; // number of additional times previous frame was scanned out (i.e. compositor missed vsync)
	uint32_t m_nReprojectionFlags;
};

/** These flags will be set on DriverDirectMode_FrameTiming::m_nReprojectionFlags when IVRDriverDirectModeComponent::GetFrameTiming is called for drivers to optionally respond to. */
const uint32_t VRCompositor_ReprojectionMotion_Enabled = 0x100; // Motion Smoothing is enabled in the UI for the currently running application
const uint32_t VRCompositor_ReprojectionMotion_ForcedOn = 0x200; // Motion Smoothing is forced on in the UI for the currently running application
const uint32_t VRCompositor_ReprojectionMotion_AppThrottled = 0x400; // Application is requesting throttling via ForceInterleavedReprojectionOn


enum EVSync
{
	VSync_None,
	VSync_WaitRender,	// block following render work until vsync
	VSync_NoWaitRender,	// do not block following render work (allow to get started early)
};

enum EVRMuraCorrectionMode
{
	EVRMuraCorrectionMode_Default = 0,
	EVRMuraCorrectionMode_NoCorrection
};

/** raw IMU data provided by IVRIOBuffer from paths to tracked devices with IMUs */
enum Imu_OffScaleFlags
{
	OffScale_AccelX	= 0x01,
	OffScale_AccelY	= 0x02,
	OffScale_AccelZ	= 0x04,
	OffScale_GyroX	= 0x08,
	OffScale_GyroY	= 0x10,
	OffScale_GyroZ	= 0x20,
};

struct ImuSample_t
{
	double fSampleTime;
	HmdVector3d_t vAccel;
	HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
};

#pragma pack( pop )

// figure out how to import from the VR API dll
#if defined(_WIN32)

  #if !defined(OPENVR_BUILD_STATIC)
    #ifdef VR_API_EXPORT
      #define VR_INTERFACE extern "C" __declspec( dllexport )
    #else
      #define VR_INTERFACE extern "C" __declspec( dllimport )
    #endif
  #else
    #define VR_INTERFACE extern "C"
  #endif

#elif defined(__GNUC__) || defined(COMPILER_GCC) || defined(__APPLE__)

#ifdef VR_API_EXPORT
  #define VR_INTERFACE extern "C" __attribute__((visibility("default")))
#else
  #define VR_INTERFACE extern "C"
#endif

#else
  #error "Unsupported Platform."
#endif


#if defined( _WIN32 )
  #define VR_CALLTYPE __cdecl
#else
  #define VR_CALLTYPE
#endif

} // namespace vr

