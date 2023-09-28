#pragma once
#include "openvr.h"
#include "version.h"
// public_vrtypes.h


namespace vr
{
#pragma pack( push, 8 )

// right-handed system
// +y is up
// +x is to the right
// -z is forward
// Distance unit is  meters
struct HmdMatrix34_t
{
	float m[3][4];
};

struct HmdMatrix33_t
{
	float m[3][3];
};

struct HmdMatrix44_t
{
	float m[4][4];
};

struct HmdVector3_t
{
	float v[3];
};

struct HmdVector4_t
{
	float v[4];
};

struct HmdVector3d_t
{
	double v[3];
};

struct HmdVector2_t
{
	float v[2];
};

struct HmdQuaternion_t
{
	double w, x, y, z;
};

struct HmdQuaternionf_t
{
	float w, x, y, z;
};

struct HmdColor_t
{
	float r, g, b, a;
};

struct HmdQuad_t
{
	HmdVector3_t vCorners[ 4 ];
};

struct HmdRect2_t
{
	HmdVector2_t vTopLeft;
	HmdVector2_t vBottomRight;
};

/** Holds the transform for a single bone */
struct VRBoneTransform_t
{
	HmdVector4_t position;
	HmdQuaternionf_t orientation;
};

#pragma pack( pop )

} // namespace vr

// Uncommented include guard ifdef was here, removed while splitting

