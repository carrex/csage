#ifndef VECTOR_H
#define VECTOR_H

/* Vector expansion macros (for arguments) */
#define VEC4(x, y, z, w) ((float[]){ x, y, z, w })
#define VEC4_VEC4(v)     ((float[]){ v[0], v[1], v[2], v[3] })
#define VEC4_VEC3(v, w)  ((float[]){ v[0], v[1], v[2], w })
#define VEC3(x, y, z)    ((float[]){ x, y, z })
#define VEC3_VEC3(v)     ((float[]){ v[0], v[1], v[2] })

#define VEC2_ZERO ((float[]){ 0.0f, 0.0f })
#define VEC3_ZERO ((float[]){ 0.0f, 0.0f, 0.0f })
#define VEC4_ZERO ((float[]){ 0.0f, 0.0f, 0.0f, 0.0f })

/* CBLAS wrapppers */
/* v = u */
#define vec2_copy(v, u) (cblas_scopy(2, u, 1, v, 1))
#define vec3_copy(v, u) (cblas_scopy(3, u, 1, v, 1))
#define vec4_copy(v, u) (cblas_scopy(4, u, 1, v, 1))
/* v <-> u */
#define vec2_swap(v, u) (cblas_sswap(2, u, 1, v, 1))
#define vec3_swap(v, u) (cblas_sswap(3, u, 1, v, 1))
#define vec4_swap(v, u) (cblas_sswap(4, u, 1, v, 1))
/* v = sv */
#define vec2_scale(v, x) (cblas_sscal(2, x, v, 1))
#define vec3_scale(v, x) (cblas_sscal(3, x, v, 1))
#define vec4_scale(v, x) (cblas_sscal(4, x, v, 1))
/* v = v + xu */
#define vec2_add(v, u, x) (cblas_saxpy(2, x, u, 1, v, 1))
#define vec3_add(v, u, x) (cblas_saxpy(3, x, u, 1, v, 1))
#define vec4_add(v, u, x) (cblas_saxpy(4, x, u, 1, v, 1))
/* = (v^T)u */
#define vec2_dot(v, u) (cblas_sdot(2, v, 1, u, 1))
#define vec3_dot(v, u) (cblas_sdot(3, v, 1, u, 1))
#define vec4_dot(v, u) (cblas_sdot(4, v, 1, u, 1))
/* = ||v|| */
#define vec2_mag(v) (cblas_snrm2(2, v, 1))
#define vec3_mag(v) (cblas_snrm2(3, v, 1))
#define vec4_mag(v) (cblas_snrm2(4, v, 1))

void  vec2_print(float* v);
void  vec3_print(float* v);
void  vec4_print(float* v);
bool  vec2_equal(float* v, float* u);
bool  vec3_equal(float* v, float* u);
bool  vec4_equal(float* v, float* u);
void  vec2_normalise(float* v);
void  vec3_normalise(float* v);
void  vec4_normalise(float* v);
float vec2_angle(float* v, float* u);
float vec3_angle(float* v, float* u);
float vec4_angle(float* v, float* u);
void  vec3_cross(float* out, float* v, float* u);
float vec3_triple(float* v, float* u, float* v3);

void vec3_from_dir(float* v, enum Direction dir);

#endif
