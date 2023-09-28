#pragma once
#include "openvr.h"
#include "version.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrinput.h
namespace vr
{
namespace IVRInput_005
{
	static const uint32_t k_unMaxActionNameLength = 64;
	static const uint32_t k_unMaxActionSetNameLength = 64;
	static const uint32_t k_unMaxActionOriginCount = 16;
	static const uint32_t k_unMaxBoneNameLength = 32;

	enum EVRSkeletalTransformSpace
	{
		VRSkeletalTransformSpace_Model = 0, 
		VRSkeletalTransformSpace_Parent = 1
	};

	enum EVRSkeletalReferencePose
	{
		VRSkeletalReferencePose_BindPose = 0,
		VRSkeletalReferencePose_OpenHand,
		VRSkeletalReferencePose_Fist,
		VRSkeletalReferencePose_GripLimit
	};

	enum EVRFinger
	{
		VRFinger_Thumb = 0,
		VRFinger_Index,
		VRFinger_Middle,
		VRFinger_Ring,
		VRFinger_Pinky,
		VRFinger_Count
	};

	enum EVRFingerSplay
	{
		VRFingerSplay_Thumb_Index = 0,
		VRFingerSplay_Index_Middle,
		VRFingerSplay_Middle_Ring,
		VRFingerSplay_Ring_Pinky,
		VRFingerSplay_Count
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
		// E.g. Knuckles, gloves that only measure finger curl
		VRSkeletalTracking_Partial,
		
		// Body part location can be measured directly throughout the entire range of motion of the body part. 
		// E.g. Mocap suit for the full body, gloves that measure rotation of each finger segment
		VRSkeletalTracking_Full,
		
		VRSkeletalTrackingLevel_Count,
		VRSkeletalTrackingLevel_Max = VRSkeletalTrackingLevel_Count - 1
	};

	enum EVRInputFilterCancelType
	{
		VRInputFilterCancel_Timers = 0,
		VRInputFilterCancel_Momentum = 1,
	};

	enum EVRInputStringBits
	{
		VRInputString_Hand = 0x01,
		VRInputString_ControllerType = 0x02,
		VRInputString_InputSource = 0x04,

		VRInputString_All = 0xFFFFFFFF
	};

	struct InputAnalogActionData_t
	{
		/** Whether or not this action is currently available to be bound in the active action set */
		bool bActive;

		/** The origin that caused this action's current state */
		VRInputValueHandle_t activeOrigin;

		/** The current state of this action; will be delta updates for mouse actions */
		float x, y, z;

		/** Deltas since the previous call to UpdateActionState() */
		float deltaX, deltaY, deltaZ;
	
		/** Time relative to now when this event happened. Will be negative to indicate a past time. */
		float fUpdateTime;
	};

	struct InputDigitalActionData_t
	{
		/** Whether or not this action is currently available to be bound in the active action set */
		bool bActive;

		/** The origin that caused this action's current state */
		VRInputValueHandle_t activeOrigin;

		/** The current state of this action; will be true if currently pressed */
		bool bState;

		/** This is true if the state has changed since the last frame */
		bool bChanged;

		/** Time relative to now when this event happened. Will be negative to indicate a past time. */
		float fUpdateTime;
	};

	struct InputPoseActionData_t
	{
		/** Whether or not this action is currently available to be bound in the active action set */
		bool bActive;

		/** The origin that caused this action's current state */
		VRInputValueHandle_t activeOrigin;

		/** The current state of this action */
		TrackedDevicePose_t pose;
	};

	struct InputSkeletalActionData_t
	{
		/** Whether or not this action is currently available to be bound in the active action set */
		bool bActive;

		/** The origin that caused this action's current state */
		VRInputValueHandle_t activeOrigin;
	};

	struct InputOriginInfo_t
	{
		VRInputValueHandle_t devicePath;
		TrackedDeviceIndex_t trackedDeviceIndex;
		char rchRenderModelComponentName[128];
	};

	struct VRActiveActionSet_t
	{
		/** This is the handle of the action set to activate for this frame. */
		VRActionSetHandle_t ulActionSet;

		/** This is the handle of a device path that this action set should be active for. To
		* activate for all devices, set this to k_ulInvalidInputValueHandle. */
		VRInputValueHandle_t ulRestrictedToDevice;

		/** The action set to activate for all devices other than ulRestrictedDevice. If 
		* ulRestrictedToDevice is set to k_ulInvalidInputValueHandle, this parameter is 
		* ignored. */
		VRActionSetHandle_t ulSecondaryActionSet;

		// This field is ignored
		uint32_t unPadding;

		/** The priority of this action set relative to other action sets. Any inputs
		* bound to a source (e.g. trackpad, joystick, trigger) will disable bindings in
		* other active action sets with a smaller priority. */
		int32_t nPriority;
	};

	/** Contains summary information about the current skeletal pose */
	struct VRSkeletalSummaryData_t
	{
		/** The amount that each finger is 'curled' inwards towards the palm.  In the case of the thumb,
		* this represents how much the thumb is wrapped around the fist.  
		* 0 means straight, 1 means fully curled */
		float	flFingerCurl[ VRFinger_Count ];

		/** The amount that each pair of adjacent fingers are separated.  
		* 0 means the digits are touching, 1 means they are fully separated.
		*/
		float	flFingerSplay[ VRFingerSplay_Count ];
	};


	class IVRInput
	{
	public:

		// ---------------  Handle management   --------------- //

		/** Sets the path to the action manifest JSON file that is used by this application. If this information
		* was set on the Steam partner site, calls to this function are ignored. If the Steam partner site
		* setting and the path provided by this call are different, VRInputError_MismatchedActionManifest is returned. 
		* This call must be made before the first call to UpdateActionState or IVRSystem::PollNextEvent. */
		virtual EVRInputError SetActionManifestPath( const char *pchActionManifestPath ) = 0;

		/** Returns a handle for an action set. This handle is used for all performance-sensitive calls. */
		virtual EVRInputError GetActionSetHandle( const char *pchActionSetName, VRActionSetHandle_t *pHandle ) = 0;

		/** Returns a handle for an action. This handle is used for all performance-sensitive calls. */
		virtual EVRInputError GetActionHandle( const char *pchActionName, VRActionHandle_t *pHandle ) = 0;

		/** Returns a handle for any path in the input system. E.g. /user/hand/right */
		virtual EVRInputError GetInputSourceHandle( const char *pchInputSourcePath, VRInputValueHandle_t  *pHandle ) = 0;

		// --------------- Reading action state ------------------- //

		/** Reads the current state into all actions. After this call, the results of Get*Action calls 
		* will be the same until the next call to UpdateActionState. */
		virtual EVRInputError UpdateActionState( VR_ARRAY_COUNT( unSetCount ) VRActiveActionSet_t *pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount ) = 0;

		/** Reads the state of a digital action given its handle. This will return VRInputError_WrongType if the type of
		* action is something other than digital */
		virtual EVRInputError GetDigitalActionData( VRActionHandle_t action, InputDigitalActionData_t *pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice ) = 0;

		/** Reads the state of an analog action given its handle. This will return VRInputError_WrongType if the type of
		* action is something other than analog */
		virtual EVRInputError GetAnalogActionData( VRActionHandle_t action, InputAnalogActionData_t *pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice ) = 0;

		/** Reads the state of a pose action given its handle. */
		virtual EVRInputError GetPoseActionData( VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, InputPoseActionData_t *pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice ) = 0;

		/** Reads the state of a skeletal action given its handle. */
		virtual EVRInputError GetSkeletalActionData( VRActionHandle_t action, InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize ) = 0;

		// ---------------  Static Skeletal Data ------------------- //

		/** Reads the number of bones in skeleton associated with the given action */
		virtual EVRInputError GetBoneCount( VRActionHandle_t action, uint32_t* pBoneCount ) = 0;

		/** Fills the given array with the index of each bone's parent in the skeleton associated with the given action */
		virtual EVRInputError GetBoneHierarchy( VRActionHandle_t action, VR_ARRAY_COUNT( unIndexArayCount ) BoneIndex_t* pParentIndices, uint32_t unIndexArayCount ) = 0;

		/** Fills the given buffer with the name of the bone at the given index in the skeleton associated with the given action */
		virtual EVRInputError GetBoneName( VRActionHandle_t action, BoneIndex_t nBoneIndex, VR_OUT_STRING() char* pchBoneName, uint32_t unNameBufferSize ) = 0;

		/** Fills the given buffer with the transforms for a specific static skeletal reference pose */
		virtual EVRInputError GetSkeletalReferenceTransforms( VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, VR_ARRAY_COUNT( unTransformArrayCount ) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount ) = 0;

		/** Reads the level of accuracy to which the controller is able to track the user to recreate a skeletal pose */
		virtual EVRInputError GetSkeletalTrackingLevel( VRActionHandle_t action, EVRSkeletalTrackingLevel* pSkeletalTrackingLevel ) = 0;

		// ---------------  Dynamic Skeletal Data ------------------- //

		/** Reads the state of the skeletal bone data associated with this action and copies it into the given buffer. */
		virtual EVRInputError GetSkeletalBoneData( VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT( unTransformArrayCount ) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount ) = 0;

		/** Reads summary information about the current pose of the skeleton associated with the given action.   */
		virtual EVRInputError GetSkeletalSummaryData( VRActionHandle_t action, VRSkeletalSummaryData_t * pSkeletalSummaryData ) = 0;

		/** Reads the state of the skeletal bone data in a compressed form that is suitable for
		* sending over the network. The required buffer size will never exceed ( sizeof(VR_BoneTransform_t)*boneCount + 2).
		* Usually the size will be much smaller. */
		virtual EVRInputError GetSkeletalBoneDataCompressed( VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT( unCompressedSize ) void *pvCompressedData, uint32_t unCompressedSize, uint32_t *punRequiredCompressedSize ) = 0;

		/** Turns a compressed buffer from GetSkeletalBoneDataCompressed and turns it back into a bone transform array. */
		virtual EVRInputError DecompressSkeletalBoneData( const void *pvCompressedBuffer, uint32_t unCompressedBufferSize, EVRSkeletalTransformSpace eTransformSpace, VR_ARRAY_COUNT( unTransformArrayCount ) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount ) = 0;

		// --------------- Haptics ------------------- //

		/** Triggers a haptic event as described by the specified action */
		virtual EVRInputError TriggerHapticVibrationAction( VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, VRInputValueHandle_t ulRestrictToDevice ) = 0;

		// --------------- Action Origins ---------------- //

		/** Retrieve origin handles for an action */
		virtual EVRInputError GetActionOrigins( VRActionSetHandle_t actionSetHandle, VRActionHandle_t digitalActionHandle, VR_ARRAY_COUNT( originOutCount ) VRInputValueHandle_t *originsOut, uint32_t originOutCount ) = 0;

		/** Retrieves the name of the origin in the current language. unStringSectionsToInclude is a bitfield of values in EVRInputStringBits that allows the 
			application to specify which parts of the origin's information it wants a string for. */
		virtual EVRInputError GetOriginLocalizedName( VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude ) = 0;

		/** Retrieves useful information for the origin of this action */
		virtual EVRInputError GetOriginTrackedDeviceInfo( VRInputValueHandle_t origin, InputOriginInfo_t *pOriginInfo, uint32_t unOriginInfoSize ) = 0;

		/** Shows the current binding for the action in-headset */
		virtual EVRInputError ShowActionOrigins( VRActionSetHandle_t actionSetHandle, VRActionHandle_t ulActionHandle ) = 0;

		/** Shows the current binding all the actions in the specified action sets */
		virtual EVRInputError ShowBindingsForActionSet( VR_ARRAY_COUNT( unSetCount ) VRActiveActionSet_t *pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, VRInputValueHandle_t originToHighlight ) = 0;
	};

	static const char * const IVRInput_Version = "IVRInput_005";

} // namespace vr

} // Close custom namespace
