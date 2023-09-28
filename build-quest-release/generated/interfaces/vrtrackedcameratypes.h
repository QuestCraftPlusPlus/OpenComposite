#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
// vrtrackedcameratypes.h
#ifndef _VRTRACKEDCAMERATYPES_H
#define _VRTRACKEDCAMERATYPES_H 

namespace vr
{

#if defined(__linux__) || defined(__APPLE__) 
	// The 32-bit version of gcc has the alignment requirement for uint64 and double set to
	// 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
	// The 64-bit version of gcc has the alignment requirement for these types set to
	// 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
	// The 64-bit structure packing has to match the 32-bit structure packing for each platform.
	#pragma pack( push, 4 )
#else
	#pragma pack( push, 8 )
#endif

enum ECameraVideoStreamFormat
{
	CVS_FORMAT_UNKNOWN = 0,
	CVS_FORMAT_RAW10 = 1,		// 10 bits per pixel
	CVS_FORMAT_NV12 = 2,		// 12 bits per pixel
	CVS_FORMAT_RGB24 = 3,		// 24 bits per pixel
	CVS_MAX_FORMATS
};

#ifdef _MSC_VER
#define VR_CAMERA_DECL_ALIGN( x ) __declspec( align( x ) )
#else
#define VR_CAMERA_DECL_ALIGN( x ) //
#endif

VR_CAMERA_DECL_ALIGN( 8 ) struct CameraVideoStreamFrame_t
{
	ECameraVideoStreamFormat m_nStreamFormat;

	uint32_t m_nWidth;
	uint32_t m_nHeight;

	uint32_t m_nFrameSequence;			// Starts from 0 when stream starts.
	uint32_t m_nTimeStamp;				// Driver provided time stamp per driver centric time base

	uint32_t m_nBufferIndex;			// Identifies which buffer the image data is hosted
	uint32_t m_nBufferCount;			// Total number of configured buffers

	uint32_t m_nImageDataSize;			// Based on stream format, width, height

	double m_flFrameElapsedTime;		// Starts from 0 when stream starts. In seconds.
	double m_flFrameCaptureTime;		// Relative to when the frame was exposed/captured.

	bool m_bPoseIsValid;				// Supplied by HMD layer when used as a tracked camera
	vr::HmdMatrix34_t m_matDeviceToAbsoluteTracking;	

	float m_Pad[4];

	void *m_pImageData;
};

#pragma pack( pop )

}

#endif // _VRTRACKEDCAMERATYPES_H
