#include <stdio.h>

#include "maths.h"

void vec2_print(float* v)
{
	double m = (double)vec2_mag(v),
	       x = (double)v[0],
	       y = (double)v[1];
	printf("[Vec2D(%.3f): %.3f|%.3f]\n", m, x, y);
}

void vec3_print(float* v)
{
	double m = (double)vec3_mag(v),
	       x = (double)v[0],
	       y = (double)v[1],
	       z = (double)v[2];
	printf("[Vec3D(%.3f): %.3f|%.3f|%.3f]\n", m, x, y, z);
}

void vec4_print(float* v)
{
	double m = (double)vec4_mag(v),
	       x = (double)v[0],
	       y = (double)v[1],
	       z = (double)v[2],
	       w = (double)v[3];
	printf("[Vec4D(%.3f): %.3f|%.3f|%.3f|%.3f]\n", m, x, y, z, w);
}
/*********************************************************/
bool vec2_equal(float* v, float* u)
{
	bool v0 = is_equal(v[0], u[0]);
	bool v1 = is_equal(v[1], u[1]);
	return v0 && v1;
}
bool vec3_equal(float* v, float* u)
{
	bool v0 = is_equal(v[0], u[0]);
	bool v1 = is_equal(v[1], u[1]);
	bool v2 = is_equal(v[2], u[2]);
	return v0 && v1 && v2;
}
bool vec4_equal(float* v, float* u)
{
	bool v0 = is_equal(v[0], u[0]);
	bool v1 = is_equal(v[1], u[1]);
	bool v2 = is_equal(v[2], u[2]);
	bool v3 = is_equal(v[3], u[3]);
	return v0 && v1 && v2 && v3;
}
/*********************************************************/
void vec2_normalise(float* v)
{
	vec2_scale(v, vec2_mag(v));
}

void vec3_normalise(float* v)
{
	vec3_scale(v, vec3_mag(v));
}

void vec4_normalise(float* v)
{
	vec4_scale(v, vec4_mag(v));
}
/*********************************************************/
float vec2_angle(float* v, float* u)
{
	return (float)acos(vec2_dot(v, u) / (vec2_mag(v) * vec2_mag(u)));
}

float vec3_angle(float* v, float* u)
{
	return (float)acos(vec3_dot(v, u) / (vec3_mag(v) * vec3_mag(u)));
}

float vec4_angle(float* v, float* u)
{
	return (float)acos(vec4_dot(v, u) / (vec4_mag(v) * vec4_mag(u)));
}
/*********************************************************/
void vec3_cross(float* v, float* u, float* w)
{
	v[0] = (u[1] * w[2]) - (u[2] * w[1]);
	v[1] = (u[2] * w[0]) - (u[0] * w[2]);
	v[2] = (u[0] * w[1]) - (u[1] * w[0]);
}
/*********************************************************/
float vec3_triple(float* v, float* u, float* w)
{
	float tmp[3];
	vec3_cross(tmp, v, u);

	return vec3_dot(tmp, w);
}
/*********************************************************/
void vec3_from_dir(float* v, enum Direction dir)
{
	vec3_copy(v, VEC3_ZERO);
	switch (dir) {
		case DIR_NONE    : return;
		case DIR_RIGHT   : v[0] =  1.0f; break;
		case DIR_LEFT    : v[0] = -1.0f; break;
		case DIR_UP      : v[1] =  1.0f; break;
		case DIR_DOWN    : v[1] = -1.0f; break;
		case DIR_BACKWARD: v[2] =  1.0f; break;
		case DIR_FORWARD : v[2] = -1.0f; break;
		default: ERROR("[MATHS] Invalid direction");
	}
}
/*********************************************************/
// void vec_proj_2d(float* v, float* u)
// {
// 	float* n;
// 	vec_copy_2d(n, u);
// 	vec_norm_2d(n);

// 	float dot = vec_dot_2d(v, n);
// 	vec_copy_2d(v, n);
// 	vec_mul_2d(v, dot);
// }
// void vec_proj_3d(float* v, float* u)
// {
// 	float* n;
// 	vec_copy_3d(n, u);
// 	vec_norm_3d(n);

// 	float dot = vec_dot_3d(v, n);
// 	vec_copy_3d(v, n);
// 	vec_mul_3d(v, dot);
// }
// void vec_proj_4d(float* v, float* u)
// {
// 	float* n;
// 	vec_copy_4d(n, u);
// 	vec_norm_4d(n);

// 	float dot = vec_dot_4d(v, n);
// 	vec_copy_4d(v, n);
// 	vec_mul_4d(v, dot);
// }
// /*********************************************************/
// void vec_scale_2d(float* v, float k, float* n)
// {
// 	float* res;
// 	Mat2x2 scale = { (k - 1)*n[0]*n[0] + 1, (k - 1)*n[0]*n[1]    ,
// 	                 (k - 1)*n[0]*n[1]    , (k - 1)*n[1]*n[1] + 1, };
// 	mat_multiply(v, scale, res, 2, 1);
// 	vec_copy_2d(v, res);
// }
// void vec_scale_3d(float* v, float k, float* n)
// {
// 	float* res;
// 	Mat3x3 scale = { (k - 1)*n[0]*n[0] + 1, (k - 1)*n[0]*n[1]    , (k - 1)*n[0]*n[2]    ,
// 	                 (k - 1)*n[0]*n[1]    , (k - 1)*n[1]*n[1] + 1, (k - 1)*n[1]*n[2]    ,
// 	                 (k - 1)*n[0]*n[2]    , (k - 1)*n[1]*n[2]    , (k - 1)*n[2]*n[2] + 1, };
// 	mat_multiply(v, scale, res, 3, 1);
// 	vec_copy_3d(v, res);
// }
// /*********************************************************/
// void vec_rot2d(float* v, float rad)
// {
// 	float* res;
// 	Mat2x2 rot = {  (float)cos(rad), (float)sin(rad),
// 	               -(float)sin(rad), (float)cos(rad), };
// 	mat_multiply(v, rot, res, 2, 1);
// 	vec_copy_2d(v, res);
// }
// void vec_rot3d(float* v, float rad, float* n)
// {
// 	float* res;
// 	float cosr = (float)cos(rad);
// 	float sinr = (float)sin(rad);
// 	vec_norm_3d(n);
// 	Mat3x3 rot = { n[0]*n[0]*(1 - cosr) +      cosr, n[0]*n[1]*(1 - cosr) + n[2]*sinr, n[0]*n[2]*(1 - cosr) - n[1]*sinr,
// 	               n[0]*n[1]*(1 - cosr) - n[2]*sinr, n[1]*n[1]*(1 - cosr) +      cosr, n[1]*n[2]*(1 - cosr) + n[0]*sinr,
// 	               n[0]*n[2]*(1 - cosr) + n[1]*sinr, n[1]*n[2]*(1 - cosr) - n[0]*sinr, n[2]*n[2]*(1 - cosr) +      cosr, };
// 	mat_multiply(v, rot, res, 3, 1);
// 	vec_copy_3d(v, res);
// }
