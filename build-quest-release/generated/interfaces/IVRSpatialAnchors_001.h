#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrspatialanchors.h

namespace vr
{
namespace IVRSpatialAnchors_001
{
	static const SpatialAnchorHandle_t k_ulInvalidSpatialAnchorHandle = 0;

	struct SpatialAnchorPose_t
	{
		HmdMatrix34_t mAnchorToAbsoluteTracking;
	};

	class IVRSpatialAnchors
	{
	public:

		/** Returns a handle for an spatial anchor described by "descriptor".  On success, pHandle
		* will contain a handle valid for this session.  Caller can wait for an event or occasionally
		* poll GetSpatialAnchorPose() to find the virtual coordinate associated with this anchor. */
		virtual EVRSpatialAnchorError CreateSpatialAnchorFromDescriptor( const char *pchDescriptor, SpatialAnchorHandle_t *pHandleOut ) = 0;

		/** Returns a handle for an new spatial anchor at pPose.  On success, pHandle
		* will contain a handle valid for this session.  Caller can wait for an event or occasionally
		* poll GetSpatialAnchorDescriptor() to find the permanent descriptor for this pose.
		* The result of GetSpatialAnchorPose() may evolve from this initial position if the driver chooses
		* to update it.
		* The anchor will be associated with the driver that provides unDeviceIndex, and the driver may use that specific
		* device as a hint for how to best create the anchor.
		* The eOrigin must match whatever tracking origin you are working in (seated/standing/raw).
		* This should be called when the user is close to (and ideally looking at/interacting with) the target physical
		* location.  At that moment, the driver will have the most information about how to recover that physical point
		* in the future, and the quality of the anchor (when the descriptor is re-used) will be highest.
		* The caller may decide to apply offsets from this initial pose, but is advised to stay relatively close to the
		* original pose location for highest fidelity. */
		virtual EVRSpatialAnchorError CreateSpatialAnchorFromPose( TrackedDeviceIndex_t unDeviceIndex, ETrackingUniverseOrigin eOrigin, SpatialAnchorPose_t *pPose, SpatialAnchorHandle_t *pHandleOut ) = 0;

		/** Get the pose for a given handle.  This is intended to be cheap enough to call every frame (or fairly often)
		* so that the driver can refine this position when it has more information available. */
		virtual EVRSpatialAnchorError GetSpatialAnchorPose( SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, SpatialAnchorPose_t *pPoseOut ) = 0;

		/** Get the descriptor for a given handle.  This will be empty for handles where the driver has not
		* yet built a descriptor.  It will be the application-supplied descriptor for previously saved anchors
		* that the application is requesting poses for.  If the driver has called UpdateSpatialAnchorDescriptor()
		* already in this session, it will be the descriptor provided by the driver.
		* Returns true if the descriptor fits into the buffer, else false.  Buffer size should be at least
		* k_unMaxSpatialAnchorDescriptorSize. */
		virtual EVRSpatialAnchorError GetSpatialAnchorDescriptor( SpatialAnchorHandle_t unHandle, VR_OUT_STRING() char *pchDescriptorOut, uint32_t *punDescriptorBufferLenInOut ) = 0;

	};

	static const char * const IVRSpatialAnchors_Version = "IVRSpatialAnchors_001";

} // namespace vr

} // Close custom namespace
