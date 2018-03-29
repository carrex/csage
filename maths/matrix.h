#ifndef MATRIX_H
#define MATRIX_H

enum Axis {
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
};

#define MAT4_ZERO ((float[]){ 0.0f, 0.0f, 0.0f, 0.0f, \
                              0.0f, 0.0f, 0.0f, 0.0f, \
                              0.0f, 0.0f, 0.0f, 0.0f, \
                              0.0f, 0.0f, 0.0f, 0.0f, })
#define I2 { 1.0f, 0.0f, \
             0.0f, 1.0f, }
#define I3 { 1.0f, 0.0f, 0.0f, \
             0.0f, 1.0f, 0.0f, \
             0.0f, 0.0f, 1.0f, }
#define I4 { 1.0f, 0.0f, 0.0f, 0.0f, \
             0.0f, 1.0f, 0.0f, 0.0f, \
             0.0f, 0.0f, 1.0f, 0.0f, \
             0.0f, 0.0f, 0.0f, 1.0f, }
#define I2A ((float[])I2)
#define I3A ((float[])I3)
#define I4A ((float[])I4)

/* CBLAS wrappers */
#define mat4_copy(a, b) (cblas_scopy(16, b, 1, a, 1))
/* a = a + xb */
#define mat4_add(a, b, x) (cblas_saxpy(16, x, b, 1, a, 1))
#define mat4_scalar_mul(a, s) (cblas_scal(16, s, a, 1))
#define mat4_vec4_mul(a, v) (cblas_sgemv(CblasRowMajor, CblasNoTrans, 4, 4, 1.0, a, 4, v, 1, 0.0, NULL, 1))
/* a = b*c */
#define mat4_mul(a, b, c) (cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 4, 4, 4, 1.0, b, 4, c, 4, 0.0, a, 4))

void mat_print(float* a, uint8 dim);

/* `mat*_new_*` do not zero matrices, they only set the appropriate values */
void mat4_new_scale(float* a, float* v);
void mat4_new_translate(float* a, float* v);

void mat4_new_perspective(float* a, float aspect, float fov, float znear, float zfar);
void mat4_new_orthogonal(float* a, float znear, float zfar);

/* Vectors are used to change transformation matrices and are not affected
 */
void mat4_translate(float* a, float* v);
void mat4_scale(float* a, float* v);

#endif
