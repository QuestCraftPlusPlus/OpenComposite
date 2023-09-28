#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrdrivermanager.h

namespace vr
{
namespace IVRDriverManager_001
{

class IVRDriverManager
{
public:
	virtual uint32_t GetDriverCount() const = 0;

	/** Returns the length of the number of bytes necessary to hold this string including the trailing null. */
	virtual uint32_t GetDriverName( DriverId_t nDriver, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;

	virtual DriverHandle_t GetDriverHandle( const char *pchDriverName ) = 0;

	virtual bool IsEnabled( DriverId_t nDriver ) const = 0;
};

static const char * const IVRDriverManager_Version = "IVRDriverManager_001";

} // namespace vr



} // Close custom namespace
