#ifndef VECTOR_H
#define VECTOR_H

#define VEC2D_ZERO { 0.0f, 0.0f }
#define VEC3D_ZERO { 0.0f, 0.0f, 0.0f }
#define VEC4D_ZERO { 0.0f, 0.0f, 0.0f, 0.0f }

typedef float Vec2D[2];
typedef float Vec3D[3];
typedef float Vec4D[4];

/* !! VEC_EXT could be more robust for errors */
// #define VEC_ERROR(...) ERROR("Invalid arguments")
#define VEC_DIM(v) ((ushort)(sizeof(v) / sizeof(float)))
#define VEC_EXT(v, ext, ...) (VEC_DIM(v) == 2? vec_##ext##_2d: \
                              VEC_DIM(v) == 3? vec_##ext##_3d: \
                              VEC_DIM(v) == 4? vec_##ext##_4d: \
                              vec_##ext##_4d)(__VA_ARGS__) // -->!
#define vec_print(v) VEC_EXT(v, print, v)
void vec_print_2d(Vec2D v);
void vec_print_3d(Vec3D v);
void vec_print_4d(Vec4D v);
#define vec_copy(v1, v2) VEC_EXT(v1, copy, v1, v2)
void vec_copy_2d(Vec2D v1, Vec2D v2);
void vec_copy_3d(Vec3D v1, Vec3D v2);
void vec_copy_4d(Vec4D v1, Vec4D v2);
#define vec_add(v1, v2) VEC_EXT(v1, add, v1, v2)
void vec_add_2d(Vec2D v1, Vec2D v2);
void vec_add_3d(Vec3D v1, Vec3D v2);
void vec_add_4d(Vec4D v1, Vec4D v2);
#define vec_sub(v1, v2) VEC_EXT(v1, sub, v1, v2)
void vec_sub_2d(Vec2D v1, Vec2D v2);
void vec_sub_3d(Vec3D v1, Vec3D v2);
void vec_sub_4d(Vec4D v1, Vec4D v2);
#define vec_mul(v1, v2) VEC_EXT(v1, mul, v1, v2)
void vec_mul_2d(Vec2D v, float s);
void vec_mul_3d(Vec3D v, float s);
void vec_mul_4d(Vec4D v, float s);
#define vec_div(v, s) VEC_EXT(v, div, v, s)
void vec_div_2d(Vec2D v, float s);
void vec_div_3d(Vec3D v, float s);
void vec_div_4d(Vec4D v, float s);
#define vec_norm(v) VEC_EXT(v, norm, v)
void vec_normal_2d(Vec2D v);
void vec_normal_3d(Vec3D v);
void vec_normal_4d(Vec4D v);
#define vec_mag(v) VEC_EXT(v, mag, v)
float vec_mag_2d(Vec2D v);
float vec_mag_3d(Vec3D v);
float vec_mag_4d(Vec4D v);
#define vec_dot(v1, v2) VEC_EXT(v1, dot, v1, v2)
float vec_dot_2d(Vec2D v1, Vec2D v2);
float vec_dot_3d(Vec3D v1, Vec3D v2);
float vec_dot_4d(Vec4D v1, Vec4D v2);
#define vec_angle(v1, v2) VEC_EXT(v1, angle, v1, v2)
float vec_angle_2d(Vec2D v1, Vec2D v2);
float vec_angle_3d(Vec3D v1, Vec3D v2);
float vec_angle_4d(Vec4D v1, Vec4D v2);
#define vec_proj(v1, v2) VEC_EXT(v1, proj, v1, v2)
void vec_proj_2d(Vec2D v1, Vec2D v2);
void vec_proj_3d(Vec3D v1, Vec3D v2);
void vec_proj_4d(Vec4D v1, Vec4D v2);
#define vec_scale(v, k, a) VEC_EXT(v, scale, v, k, a)
void vec_scale_2d(Vec2D v, float k, Vec2D axis);
void vec_scale_3d(Vec3D v, float k, Vec3D axis);
// #define vec_rot(v, r) VEC_EXT(v, rot, v, r)//, __VA_ARGS__)
void vec_rot2d(Vec2D v, float rad);
void vec_rot3d(Vec3D v, float rad, Vec3D axis);
// #define vec_cross(out, v1, v2) VEC_EXT(out, cross, out, v1, v2)
void   vec_cross(Vec3D out, Vec3D v1, Vec3D v2);
float vec_triple(Vec3D v1, Vec3D v2, Vec3D v3);
void vec_difference_3d(float* v, float* u, float* w); // v = u - w

#endif
