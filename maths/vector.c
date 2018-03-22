#include <stdio.h>
#include <math.h>

#include "common.h"
#include "maths.h"
#include "vector.h"

void vec_print_2d(Vec2D v) { DEBUG("[Vec2D(%.2f): %.2f|%.2f]\n", vec_mag_2d(v), v[0], v[1]); }
void vec_print_3d(Vec3D v) { DEBUG("[Vec3D(%.2f): %.2f|%.2f|%.2f]\n", vec_mag_3d(v), v[0], v[1], v[2]); }
void vec_print_4d(Vec4D v) { DEBUG("[Vec4D(%.2f): %.2f|%.2f|%.2f|%.2f]\n", vec_mag_4d(v), v[0], v[1], v[2], v[3]); }
/*********************************************************/
void vec_copy_2d(Vec2D v1, Vec2D v2) { v1[0] = v2[0]; v1[1] = v2[1]; }
void vec_copy_3d(Vec3D v1, Vec3D v2) { v1[0] = v2[0]; v1[1] = v2[1]; v1[2] = v2[2]; }
void vec_copy_4d(Vec4D v1, Vec4D v2) { v1[0] = v2[0]; v1[1] = v2[1]; v1[2] = v2[2]; v1[3] = v2[3]; }
/*********************************************************/
void vec_add_2d(Vec2D v1, Vec2D v2) { v1[0] += v2[0]; v1[1] += v2[1]; }
void vec_add_3d(Vec3D v1, Vec3D v2) { v1[0] += v2[0]; v1[1] += v2[1]; v1[2] += v2[2]; }
void vec_add_4d(Vec4D v1, Vec4D v2) { v1[0] += v2[0]; v1[1] += v2[1]; v1[2] += v2[2]; v1[3] += v2[3]; }
/*********************************************************/
void vec_sub_2d(Vec2D v1, Vec2D v2) { v1[0] -= v2[0]; v1[1] -= v2[1]; }
void vec_sub_3d(Vec3D v1, Vec3D v2) { v1[0] -= v2[0]; v1[1] -= v2[1]; v1[2] -= v2[2]; }
void vec_sub_4d(Vec4D v1, Vec4D v2) { v1[0] -= v2[0]; v1[1] -= v2[1]; v1[2] -= v2[2]; v1[3] -= v2[3]; }
/*********************************************************/
void vec_mul_2d(Vec2D v, float s) { v[0] *= s; v[1] *= s; }
void vec_mul_3d(Vec3D v, float s) { v[0] *= s; v[1] *= s; v[2] *= s; }
void vec_mul_4d(Vec4D v, float s) { v[0] *= s; v[1] *= s; v[2] *= s; v[3] *= s; }
/*********************************************************/
void vec_div_2d(Vec2D v, float s) { v[0] /= s;	v[1] /= s; }
void vec_div_3d(Vec3D v, float s) { v[0] /= s;	v[1] /= s; v[2] /= s; }
void vec_div_4d(Vec4D v, float s) { v[0] /= s;	v[1] /= s; v[2] /= s; v[3] /= s; }
/*********************************************************/
void vec_norm_2d(Vec2D v) { vec_div_2d(v, vec_mag_2d(v)); }
void vec_norm_3d(Vec3D v) { vec_div_3d(v, vec_mag_3d(v)); }
void vec_norm_4d(Vec4D v) { vec_div_4d(v, vec_mag_4d(v)); }
/*********************************************************/
float vec_mag_2d(Vec2D v) { return (float)sqrt(sq(v[0]) + sq(v[1])); }
float vec_mag_3d(Vec3D v) { return (float)sqrt(sq(v[0]) + sq(v[1]) + sq(v[2])); }
float vec_mag_4d(Vec4D v) { return (float)sqrt(sq(v[0]) + sq(v[1]) + sq(v[2]) + sq(v[3])); }
/*********************************************************/
float vec_dot_2d(Vec2D v1, Vec2D v2) { return v1[0]*v2[0] + v1[1]*v2[1]; }
float vec_dot_3d(Vec3D v1, Vec3D v2) { return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]; }
float vec_dot_4d(Vec4D v1, Vec4D v2) { return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] + v1[3]*v2[3]; }
/*********************************************************/
float vec_angle_2d(Vec2D v1, Vec2D v2) { return (float)acos(vec_dot_2d(v1, v2) / (vec_mag_2d(v1) * vec_mag_2d(v2))); }
float vec_angle_3d(Vec3D v1, Vec3D v2) { return (float)acos(vec_dot_3d(v1, v2) / (vec_mag_3d(v1) * vec_mag_3d(v2))); }
float vec_angle_4d(Vec4D v1, Vec4D v2) { return (float)acos(vec_dot_4d(v1, v2) / (vec_mag_4d(v1) * vec_mag_4d(v2))); }
/*********************************************************/
// void vec_proj_2d(Vec2D v1, Vec2D v2)
// {
// 	Vec2D n;
// 	vec_copy_2d(n, v2);
// 	vec_norm_2d(n);

// 	float dot = vec_dot_2d(v1, n);
// 	vec_copy_2d(v1, n);
// 	vec_mul_2d(v1, dot);
// }
// void vec_proj_3d(Vec3D v1, Vec3D v2)
// {
// 	Vec3D n;
// 	vec_copy_3d(n, v2);
// 	vec_norm_3d(n);

// 	float dot = vec_dot_3d(v1, n);
// 	vec_copy_3d(v1, n);
// 	vec_mul_3d(v1, dot);
// }
// void vec_proj_4d(Vec4D v1, Vec4D v2)
// {
// 	Vec4D n;
// 	vec_copy_4d(n, v2);
// 	vec_norm_4d(n);

// 	float dot = vec_dot_4d(v1, n);
// 	vec_copy_4d(v1, n);
// 	vec_mul_4d(v1, dot);
// }
// /*********************************************************/
// void vec_scale_2d(Vec2D v, float k, Vec2D n)
// {
// 	Vec2D res;
// 	Mat2x2 scale = { (k - 1)*n[0]*n[0] + 1, (k - 1)*n[0]*n[1]    ,
// 	                 (k - 1)*n[0]*n[1]    , (k - 1)*n[1]*n[1] + 1, };
// 	mat_multiply(v, scale, res, 2, 1);
// 	vec_copy_2d(v, res);
// }
// void vec_scale_3d(Vec3D v, float k, Vec3D n)
// {
// 	Vec3D res;
// 	Mat3x3 scale = { (k - 1)*n[0]*n[0] + 1, (k - 1)*n[0]*n[1]    , (k - 1)*n[0]*n[2]    ,
// 	                 (k - 1)*n[0]*n[1]    , (k - 1)*n[1]*n[1] + 1, (k - 1)*n[1]*n[2]    ,
// 	                 (k - 1)*n[0]*n[2]    , (k - 1)*n[1]*n[2]    , (k - 1)*n[2]*n[2] + 1, };
// 	mat_multiply(v, scale, res, 3, 1);
// 	vec_copy_3d(v, res);
// }
// /*********************************************************/
// void vec_rot2d(Vec2D v, float rad)
// {
// 	Vec2D res;
// 	Mat2x2 rot = {  (float)cos(rad), (float)sin(rad),
// 	               -(float)sin(rad), (float)cos(rad), };
// 	mat_multiply(v, rot, res, 2, 1);
// 	vec_copy_2d(v, res);
// }
// void vec_rot3d(Vec3D v, float rad, Vec3D n)
// {
// 	Vec3D res;
// 	float cosr = (float)cos(rad);
// 	float sinr = (float)sin(rad);
// 	vec_norm_3d(n);
// 	Mat3x3 rot = { n[0]*n[0]*(1 - cosr) +      cosr, n[0]*n[1]*(1 - cosr) + n[2]*sinr, n[0]*n[2]*(1 - cosr) - n[1]*sinr,
// 	               n[0]*n[1]*(1 - cosr) - n[2]*sinr, n[1]*n[1]*(1 - cosr) +      cosr, n[1]*n[2]*(1 - cosr) + n[0]*sinr,
// 	               n[0]*n[2]*(1 - cosr) + n[1]*sinr, n[1]*n[2]*(1 - cosr) - n[0]*sinr, n[2]*n[2]*(1 - cosr) +      cosr, };
// 	mat_multiply(v, rot, res, 3, 1);
// 	vec_copy_3d(v, res);
// }
/*********************************************************/
void vec_cross(Vec3D out, Vec3D v1, Vec3D v2)
{
	out[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	out[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	out[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
}
/*********************************************************/
float vec_triple(Vec3D v1, Vec3D v2, Vec3D v3)
{
	Vec3D tmp;
	vec_cross(tmp, v1, v2);

	return vec_dot_3d(tmp, v3);
}
