#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrextendeddisplay.h

namespace vr
{
namespace IVRExtendedDisplay_001
{

	/** NOTE: Use of this interface is not recommended in production applications. It will not work for displays which use
	* direct-to-display mode. Creating our own window is also incompatible with the VR compositor and is not available when the compositor is running. */
	class IVRExtendedDisplay
	{
	public:

		/** Size and position that the window needs to be on the VR display. */
		virtual void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;

		/** Gets the viewport in the frame buffer to draw the output of the distortion into */
		virtual void GetEyeOutputViewport( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;

		/** [D3D10/11 Only]
		* Returns the adapter index and output index that the user should pass into EnumAdapters and EnumOutputs
		* to create the device and swap chain in DX10 and DX11. If an error occurs both indices will be set to -1.
		*/
		virtual void GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex ) = 0;

	};

	static const char * const IVRExtendedDisplay_Version = "IVRExtendedDisplay_001";

}


} // Close custom namespace
