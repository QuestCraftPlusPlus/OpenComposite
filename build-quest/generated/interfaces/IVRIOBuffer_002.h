#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivriobuffer.h

namespace vr
{
namespace IVRIOBuffer_002
{

typedef uint64_t IOBufferHandle_t;
static const uint64_t k_ulInvalidIOBufferHandle = 0;

	enum EIOBufferError
	{
		IOBuffer_Success                  = 0,
		IOBuffer_OperationFailed          = 100,
		IOBuffer_InvalidHandle            = 101,
		IOBuffer_InvalidArgument          = 102,
		IOBuffer_PathExists               = 103,
		IOBuffer_PathDoesNotExist         = 104,
		IOBuffer_Permission               = 105,
	};

	enum EIOBufferMode
	{
		IOBufferMode_Read                 = 0x0001,
		IOBufferMode_Write                = 0x0002,
		IOBufferMode_Create               = 0x0200,
	};

	// ----------------------------------------------------------------------------------------------
	// Purpose:
	// ----------------------------------------------------------------------------------------------
	class IVRIOBuffer
	{
	public:
		/** opens an existing or creates a new IOBuffer of unSize bytes */
		virtual EIOBufferError Open( const char *pchPath, EIOBufferMode mode, uint32_t unElementSize, uint32_t unElements, IOBufferHandle_t *pulBuffer ) = 0;

		/** closes a previously opened or created buffer */
		virtual EIOBufferError Close( IOBufferHandle_t ulBuffer ) = 0;

		/** reads up to unBytes from buffer into *pDst, returning number of bytes read in *punRead */
		virtual EIOBufferError Read( IOBufferHandle_t ulBuffer, void *pDst, uint32_t unBytes, uint32_t *punRead ) = 0;

		/** writes unBytes of data from *pSrc into a buffer. */
		virtual EIOBufferError Write( IOBufferHandle_t ulBuffer, void *pSrc, uint32_t unBytes ) = 0;

		/** retrieves the property container of an buffer. */
		virtual PropertyContainerHandle_t PropertyContainer( IOBufferHandle_t ulBuffer ) = 0;

		/** inexpensively checks for readers to allow writers to fast-fail potentially expensive copies and writes. */
		virtual bool HasReaders( IOBufferHandle_t ulBuffer ) = 0;
	};

	static const char *IVRIOBuffer_Version = "IVRIOBuffer_002";
}

} // Close custom namespace
