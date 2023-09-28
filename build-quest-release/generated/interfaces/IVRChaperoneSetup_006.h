#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrchaperonesetup.h

namespace vr
{
namespace IVRChaperoneSetup_006
{

enum EChaperoneConfigFile
{
	EChaperoneConfigFile_Live = 1,		// The live chaperone config, used by most applications and games
	EChaperoneConfigFile_Temp = 2,		// The temporary chaperone config, used to live-preview collision bounds in room setup
};

enum EChaperoneImportFlags
{
	EChaperoneImport_BoundsOnly = 0x0001,
};

/** Manages the working copy of the chaperone info. By default this will be the same as the
* live copy. Any changes made with this interface will stay in the working copy until
* CommitWorkingCopy() is called, at which point the working copy and the live copy will be
* the same again. */
class IVRChaperoneSetup
{
public:

	/** Saves the current working copy to disk */
	virtual bool CommitWorkingCopy( EChaperoneConfigFile configFile ) = 0;

	/** Reverts the working copy to match the live chaperone calibration.
	* To modify existing data this MUST be do WHILE getting a non-error ChaperoneCalibrationStatus.
	* Only after this should you do gets and sets on the existing data. */
	virtual void RevertWorkingCopy() = 0;

	/** Returns the width and depth of the Play Area (formerly named Soft Bounds) in X and Z from the working copy.
	* Tracking space center (0,0,0) is the center of the Play Area. */
	virtual bool GetWorkingPlayAreaSize( float *pSizeX, float *pSizeZ ) = 0;

	/** Returns the 4 corner positions of the Play Area (formerly named Soft Bounds) from the working copy.
	* Corners are in clockwise order.
	* Tracking space center (0,0,0) is the center of the Play Area.
	* It's a rectangle.
	* 2 sides are parallel to the X axis and 2 sides are parallel to the Z axis.
	* Height of every corner is 0Y (on the floor). **/
	virtual bool GetWorkingPlayAreaRect( HmdQuad_t *rect ) = 0;

	/** Returns the number of Quads if the buffer points to null. Otherwise it returns Quads
	* into the buffer up to the max specified from the working copy. */
	virtual bool GetWorkingCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) = 0;

	/** Returns the number of Quads if the buffer points to null. Otherwise it returns Quads
	* into the buffer up to the max specified. */
	virtual bool GetLiveCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) = 0;

	/** Returns the preferred seated position from the working copy. */
	virtual bool GetWorkingSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose ) = 0;

	/** Returns the standing origin from the working copy. */
	virtual bool GetWorkingStandingZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose ) = 0;

	/** Sets the Play Area in the working copy. */
	virtual void SetWorkingPlayAreaSize( float sizeX, float sizeZ ) = 0;

	/** Sets the Collision Bounds in the working copy. Note: ceiling height is ignored. */
	virtual void SetWorkingCollisionBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount ) = 0;

	/** Sets the Collision Bounds in the working copy. */
	virtual void SetWorkingPerimeter( VR_ARRAY_COUNT( unPointCount ) HmdVector2_t *pPointBuffer, uint32_t unPointCount ) = 0;

	/** Sets the preferred seated position in the working copy. */
	virtual void SetWorkingSeatedZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose ) = 0;

	/** Sets the preferred standing position in the working copy. */
	virtual void SetWorkingStandingZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose ) = 0;

	/** Tear everything down and reload it from the file on disk */
	virtual void ReloadFromDisk( EChaperoneConfigFile configFile ) = 0;

	/** Returns the preferred seated position. */
	virtual bool GetLiveSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose ) = 0;

	virtual bool ExportLiveToBuffer( VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength ) = 0;
	virtual bool ImportFromBufferToWorking( const char *pBuffer, uint32_t nImportFlags ) = 0;

	/** Shows the chaperone data in the working set to preview in the compositor.*/
	virtual void ShowWorkingSetPreview() = 0;

	/** Hides the chaperone data in the working set to preview in the compositor (if it was visible).*/
	virtual void HideWorkingSetPreview() = 0;

	/** Fire an event that the tracking system can use to know room setup is about to begin. This lets the tracking
	 * system make any last minute adjustments that should be incorporated into the new setup.  If the user is adjusting
	 * live in HMD using a tweak tool, keep in mind that calling this might cause the user to see the room jump. */
	virtual void RoomSetupStarting() = 0;
};

static const char * const IVRChaperoneSetup_Version = "IVRChaperoneSetup_006";


}

} // Close custom namespace
