#include <math.h>

#include "quaternion.h"

void quat_new_versor(float* out, float x, float y, float z, float angle)
{
	float sina = (float)sin(angle/2.0);
	out[0] = sina * x;
	out[1] = sina * y;
	out[2] = sina * z;
	out[3] = (float)cos(angle/2.0);
}

#define x  (quat[0])
#define y  (quat[1])
#define z  (quat[2])
#define w  (quat[3])
#define x1 (quat1[0])
#define y1 (quat1[1])
#define z1 (quat1[2])
#define w1 (quat1[3])
#define x2 (quat2[0])
#define y2 (quat2[1])
#define z2 (quat2[2])
#define w2 (quat2[3])

void quat_normalise(float* quat)
{
	float mag = (float)sqrt(x*x + y*y + z*z + w*w);
	quat[0] = x/mag;
	quat[1] = y/mag;
	quat[2] = z/mag;
	quat[3] = w/mag;
}

void quat_mul(float* out, float* quat1, float* quat2)
{
	out[0] = x1*y2 + y1*x2 - z1*w2 + w1*z2;
	out[1] = x1*z2 + y1*w2 + z1*x2 - w1*y2;
	out[2] = x1*w2 - y1*z2 + z1*y2 + w1*x2;
	out[3] = x1*x2 - y1*y2 - z1*z2 - w1*w2;
}

void quat_to_matrix(float* quat, float* mat)
{
	mat[0]  = 1.0f - 2.0f*y*y - 2.0f*z*z;
	mat[1]  =        2.0f*x*y - 2.0f*w*z;
	mat[2]  =        2.0f*x*z + 2.0f*w*x;
	mat[3]  = 0.0f;

	mat[4]  =        2.0f*x*y + 2.0f*w*z;
	mat[5]  = 1.0f - 2.0f*x*x - 2.0f*z*z;
	mat[6]  =        2.0f*y*z - 2.0f*w*x;
	mat[7]  = 0.0f;

	mat[8]  =        2.0f*x*z - 2.0f*w*y;
	mat[9]  =        2.0f*y*z + 2.0f*w*x;
	mat[10] = 1.0f - 2.0f*x*x - 2.0f*y*y;
	mat[11] = 0.0f;

	mat[12] = w;
	mat[13] = w;
	mat[14] = w;
	mat[15] = 1.0f;
}

#undef x
#undef y
#undef z
#undef w
#undef x1
#undef y1
#undef z1
#undef w1
#undef x2
#undef y2
#undef z2
#undef w2
