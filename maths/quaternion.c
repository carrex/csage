#include <stdio.h>

#include "maths.h"

void quat_print(float* q)
{
	double m = (double)quat_magnitude(q),
	       a = degrees((double)quat_angle(q)),
	       w = q[0],
	       x = q[1],
	       y = q[2],
	       z = q[3];
	printf("[Quaternion(%.3f|%.3f*): %.3f|%.3f|%.3f|%.3f]\n", m, a, w, x, y, z);
}

void quat_new_versor(float* q, float w, float x, float y, float z)
{
	float sina = (float)sin(w/2.0f);
	q[0] = (float)cos(w/2.0f);
	q[1] = sina * x;
	q[2] = sina * y;
	q[3] = sina * z;

	quat_normalise(q);
}

void quat_new_versor_v(float* q, float w, float* v)
{
	quat_new_versor(q, w, v[0], v[1], v[2]);
}

void quat_copy(float* q, float* p)
{
	quat_normalise(q);
	p[0] = q[0];
	p[1] = q[1];
	p[2] = q[2];
	p[3] = q[3];
}

float quat_angle(float* q)
{
	return (float)(2.0*acos(q[0]));
}

float quat_magnitude(float* q)
{
	return (float)sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
}

void quat_normalise(float* q)
{
	float mag = quat_magnitude(q);
	if (mag > (1.0f + QUAT_NORM_EPSILON) || mag < (1.0f - QUAT_NORM_EPSILON)) {
		q[0] /= mag;
		q[1] /= mag;
		q[2] /= mag;
		q[3] /= mag;
	}
}

void quat_conjugate(float* q, float* p)
{
	p[0] =  q[0];
	p[1] = -q[1];
	p[2] = -q[2];
	p[3] = -q[3];
}

void quat_multiply(float* q, float* p)
{
	p[0] = p[0]*q[0] - p[1]*q[1] - p[2]*q[2] - p[3]*q[3];
	p[1] = p[0]*q[1] + p[1]*q[0] - p[2]*q[3] + p[3]*q[2];
	p[2] = p[0]*q[2] + p[1]*q[3] + p[2]*q[0] - p[3]*q[1];
	p[3] = p[0]*q[3] - p[1]*q[2] + p[2]*q[1] + p[3]*q[0];
	quat_normalise(p);
}

void quat_multiply_qv(float* q, float* v)
{
	float p[4];
	quat_new_versor_v(p, 0.0f, v);
	quat_multiply(q, p);
	quat_to_vector(p, v);
}

void quat_multiply_vq(float* v, float* q)
{
	float p[4], tmp[4];
	quat_new_versor_v(p, 0.0f, v);
	quat_copy(q, tmp);
	quat_multiply(p, tmp);
	quat_to_vector(tmp, v);
}

void quat_rotate(float* q, float* p)
{
	float qc[4];
	quat_conjugate(q, qc);
	quat_multiply(q, p);
	quat_multiply(p, qc);
}

void quat_rotate_v(float* q, float* v)
{
	float qc[4];
	quat_conjugate(q, qc);
	quat_multiply_qv(q, v);
	quat_multiply_vq(v, qc);
}

void quat_to_vector(float* q, float* v)
{
	v[0] = q[1];
	v[1] = q[2];
	v[2] = q[3];
}

void quat_to_matrix(float* q, float* a)
{
	a[0]  = 1.0f - 2.0f*q[2]*q[2] - 2.0f*q[3]*q[3];
	a[1]  =        2.0f*q[1]*q[2] - 2.0f*q[0]*q[3];
	a[2]  =        2.0f*q[1]*q[3] + 2.0f*q[0]*q[1];
	a[3]  = 0.0f;

	a[4]  =        2.0f*q[1]*q[2] + 2.0f*q[0]*q[3];
	a[5]  = 1.0f - 2.0f*q[1]*q[1] - 2.0f*q[3]*q[3];
	a[6]  =        2.0f*q[2]*q[3] - 2.0f*q[0]*q[1];
	a[7]  = 0.0f;

	a[8]  =        2.0f*q[1]*q[3] - 2.0f*q[0]*q[2];
	a[9]  =        2.0f*q[2]*q[3] + 2.0f*q[0]*q[1];
	a[10] = 1.0f - 2.0f*q[1]*q[1] - 2.0f*q[2]*q[2];
	a[11] = 0.0f;

	a[12] = q[0];
	a[13] = q[0];
	a[14] = q[0];
	a[15] = 1.0f;
}
