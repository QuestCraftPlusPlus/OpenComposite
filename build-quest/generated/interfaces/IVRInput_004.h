#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrinput.h
namespace vr
{
namespace IVRInput_004
{

	static const uint32_t k_unMaxActionNameLength = 64;
	static const uint32_t k_unMaxActionSetNameLength = 64;
	static const uint32_t k_unMaxActionOriginCount = 16;

	struct InputAnalogActionData_t
	{
		// Whether or not this action is currently available to be bound in the active action set
		bool bActive;

		// The origin that caused this action's current state
		VRInputValueHandle_t activeOrigin;

		// The current state of this action; will be delta updates for mouse actions
		float x, y, z;

		// Deltas since the previous call to UpdateActionState()
		float deltaX, deltaY, deltaZ;
	
		// Time relative to now when this event happened. Will be negative to indicate a past time.
		float fUpdateTime;
	};

	struct InputDigitalActionData_t
	{
		// Whether or not this action is currently available to be bound in the active action set
		bool bActive;

		// The origin that caused this action's current state
		VRInputValueHandle_t activeOrigin;

		// The current state of this action; will be true if currently pressed
		bool bState;

		// This is true if the state has changed since the last frame
		bool bChanged;

		// Time relative to now when this event happened. Will be negative to indicate a past time.
		float fUpdateTime;
	};

	struct InputPoseActionData_t
	{
		// Whether or not this action is currently available to be bound in the active action set
		bool bActive;

		// The origin that caused this action's current state
		VRInputValueHandle_t activeOrigin;

		// The current state of this action
		TrackedDevicePose_t pose;
	};

	struct InputSkeletalActionData_t
	{
		// Whether or not this action is currently available to be bound in the active action set
		bool bActive;

		// The origin that caused this action's current state
		VRInputValueHandle_t activeOrigin;

		// The number of bones in the skeletal data
		uint32_t boneCount;
	};

	enum EVRSkeletalTransformSpace
	{
		VRSkeletalTransformSpace_Model = 0,
		VRSkeletalTransformSpace_Parent = 1,
		VRSkeletalTransformSpace_Additive = 2,
	};

	enum EVRInputFilterCancelType
	{
		VRInputFilterCancel_Timers = 0,
		VRInputFilterCancel_Momentum = 1,
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
		virtual EVRInputError GetSkeletalActionData( VRActionHandle_t action, InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice ) = 0;

		// --------------- Skeletal Bone Data ------------------- //

		/** Reads the state of the skeletal bone data associated with this action and copies it into the given buffer. */
		virtual EVRInputError GetSkeletalBoneData( VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT( unTransformArrayCount ) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount, VRInputValueHandle_t ulRestrictToDevice ) = 0;

		/** Reads the state of the skeletal bone data in a compressed form that is suitable for
		* sending over the network. The required buffer size will never exceed ( sizeof(VR_BoneTransform_t)*boneCount + 2).
		* Usually the size will be much smaller. */
		virtual EVRInputError GetSkeletalBoneDataCompressed( VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT( unCompressedSize ) void *pvCompressedData, uint32_t unCompressedSize, uint32_t *punRequiredCompressedSize, VRInputValueHandle_t ulRestrictToDevice ) = 0;

		/** Turns a compressed buffer from GetSkeletalBoneDataCompressed and turns it back into a bone transform array. */
		virtual EVRInputError DecompressSkeletalBoneData( void *pvCompressedBuffer, uint32_t unCompressedBufferSize, EVRSkeletalTransformSpace *peTransformSpace, VR_ARRAY_COUNT( unTransformArrayCount ) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount ) = 0;

		// --------------- Haptics ------------------- //

		/** Triggers a haptic event as described by the specified action */
		virtual EVRInputError TriggerHapticVibrationAction( VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, VRInputValueHandle_t ulRestrictToDevice ) = 0;

		// --------------- Action Origins ---------------- //

		/** Retrieve origin handles for an action */
		virtual EVRInputError GetActionOrigins( VRActionSetHandle_t actionSetHandle, VRActionHandle_t digitalActionHandle, VR_ARRAY_COUNT( originOutCount ) VRInputValueHandle_t *originsOut, uint32_t originOutCount ) = 0;

		/** Retrieves the name of the origin in the current language */
		virtual EVRInputError GetOriginLocalizedName( VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize ) = 0;

		/** Retrieves useful information for the origin of this action */
		virtual EVRInputError GetOriginTrackedDeviceInfo( VRInputValueHandle_t origin, InputOriginInfo_t *pOriginInfo, uint32_t unOriginInfoSize ) = 0;

		/** Shows the current binding for the action in-headset */
		virtual EVRInputError ShowActionOrigins( VRActionSetHandle_t actionSetHandle, VRActionHandle_t ulActionHandle ) = 0;

		/** Shows the current binding all the actions in the specified action sets */
		virtual EVRInputError ShowBindingsForActionSet( VR_ARRAY_COUNT( unSetCount ) VRActiveActionSet_t *pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, VRInputValueHandle_t originToHighlight ) = 0;
	};

	static const char * const IVRInput_Version = "IVRInput_004";

} // namespace vr

} // Close custom namespace
