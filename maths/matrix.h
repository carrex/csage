#ifndef MATRIX_H
#define MATRIX_H

enum Axis {
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
};

/* Change to const matI*  */
#define I2 (float[]){ 1.0f, 0.0f, \
                      0.0f, 1.0f, }
#define I3 (float[]){ 1.0f, 0.0f, 0.0f, \
                      0.0f, 1.0f, 0.0f, \
                      0.0f, 0.0f, 1.0f, }
#define I4 (float[]){ 1.0f, 0.0f, 0.0f, 0.0f, \
                      0.0f, 1.0f, 0.0f, 0.0f, \
                      0.0f, 0.0f, 1.0f, 0.0f, \
                      0.0f, 0.0f, 0.0f, 1.0f, }

typedef float Mat2x2[2][2];
typedef float Mat3x3[3][3];
typedef float Mat4x4[4][4];

#define mat_print(mat, dim) _mat_print((float*)mat, dim)
#define mat_copy(mat1, mat2, dim) _mat_copy((float*)mat1, (float*)mat2, dim)
#define mat_transpose(mat, dim) _mat_transpose((float*)mat, dim)
#define mat_multiplys(mat, s, dim) _mat_multiplys((float*)mat, s, dim)
#define mat_multiply(mat1, mat2, out, dim1, dim2) _mat_multiply((float*)mat1, (float*)mat2, (float*)out, dim1, dim2)
#define mat_translate(mat, vec, dim) _mat_translate((float*)mat, (float*)vec, dim)
#define mat_rotate(mat, angle, dim, axis) _mat_rotate((float*)mat, angle, dim, axis)

void _mat_print(float* mat, uint8 dim);
void _mat_copy(float* mat1, float* mat2, uint8 dim);
void _mat_transpose(float* mat, uint8 dim);
void _mat_multiplys(float* mat, float s, uint8 dim);
void _mat_multiply(float* mat1, float* mat2, float* out, uint8 dim1, uint8 dim2);
void _mat_translate(float* mat, float* vec, uint8 dim);
void _mat_rotate(float* mat, float angle, uint8 dim, enum Axis axis);

#endif
