#ifndef MATRIX_H
#define MATRIX_H

enum Axis {
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
};

#define I2 { 1.0f, 0.0f, \
             0.0f, 1.0f, }
#define I3 { 1.0f, 0.0f, 0.0f, \
             0.0f, 1.0f, 0.0f, \
             0.0f, 0.0f, 1.0f, }
#define I4 { 1.0f, 0.0f, 0.0f, 0.0f, \
             0.0f, 1.0f, 0.0f, 0.0f, \
             0.0f, 0.0f, 1.0f, 0.0f, \
             0.0f, 0.0f, 0.0f, 1.0f, }

void mat_print(float* mat, uint8 dim);
void mat_copy(float* mat1, float* mat2, uint8 dim);
void mat_transpose(float* mat, uint8 dim);
void mat_multiplys(float* mat, float s, uint8 dim);
void mat_multiply(float* mat1, float* mat2, float* out, uint8 dim1, uint8 dim2);
void mat_translate(float* mat, float* vec, uint8 dim);
void mat_rotate(float* mat, float angle, uint8 dim, enum Axis axis);

#endif
