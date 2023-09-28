#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrheadsetview.h

namespace vr
{
namespace IVRHeadsetView_001
{
	enum HeadsetViewMode_t
	{
		HeadsetViewMode_Left = 0,
		HeadsetViewMode_Right,
		HeadsetViewMode_Both
	};

	class IVRHeadsetView
	{
	public:
		/** Sets the resolution in pixels to render the headset view. These values are clamped to k_unHeadsetViewMaxWidth
		* and k_unHeadsetViewMaxHeight respectively. For cropped views, the rendered output will be fit to aspect ratio
		* defined by the the specified dimensions. For uncropped views, the caller should use GetHeadsetViewAspectRation
		* to adjust the requested render size to avoid squashing or stretching, and then apply letterboxing to compensate
		* when displaying the results. */
		virtual void SetHeadsetViewSize( uint32_t nWidth, uint32_t nHeight ) = 0;

		/** Gets the current resolution used to render the headset view. */
		virtual void GetHeadsetViewSize( uint32_t *pnWidth, uint32_t *pnHeight ) = 0;

		/** Set the mode used to render the headset view. */
		virtual void SetHeadsetViewMode( HeadsetViewMode_t eHeadsetViewMode ) = 0;

		/** Get the current mode used to render the headset view. */
		virtual HeadsetViewMode_t GetHeadsetViewMode() = 0;

		/** Set whether or not the headset view should be rendered cropped to hide the hidden area mesh or not. */
		virtual void SetHeadsetViewCropped( bool bCropped ) = 0;

		/** Get the current cropping status of the headset view. */
		virtual bool GetHeadsetViewCropped() = 0;

		/** Get the aspect ratio (width:height) of the uncropped headset view (accounting for the current set mode). */
		virtual float GetHeadsetViewAspectRatio() = 0;

		/** Set the range [0..1] that the headset view blends across the stereo overlapped area in cropped both mode. */
		virtual void SetHeadsetViewBlendRange( float flStartPct, float flEndPct ) = 0;

		/** Get the current range [0..1] that the headset view blends across the stereo overlapped area in cropped both mode. */
		virtual void GetHeadsetViewBlendRange( float *pStartPct, float *pEndPct ) = 0;
	};

	static const uint32_t k_unHeadsetViewMaxWidth = 3840;
	static const uint32_t k_unHeadsetViewMaxHeight = 2160;
	static const char * const k_pchHeadsetViewOverlayKey = "system.HeadsetView";

	static const char * const IVRHeadsetView_Version = "IVRHeadsetView_001";

	/** Returns the current IVRHeadsetView pointer or NULL the interface could not be found. */
	VR_INTERFACE IVRHeadsetView *VR_CALLTYPE VRHeadsetView();

} // namespace vr


} // Close custom namespace
