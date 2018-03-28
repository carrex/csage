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
#define I2 ((float[]){ 1.0f, 0.0f, \
                       0.0f, 1.0f, })
#define I3 ((float[]){ 1.0f, 0.0f, 0.0f, \
                       0.0f, 1.0f, 0.0f, \
                       0.0f, 0.0f, 1.0f, })
#define I4 ((float[]){ 1.0f, 0.0f, 0.0f, 0.0f, \
                       0.0f, 1.0f, 0.0f, 0.0f, \
                       0.0f, 0.0f, 1.0f, 0.0f, \
                       0.0f, 0.0f, 0.0f, 1.0f, })

void matrix_print(float* a, uint8 dim);
void matrix_copy(float* a, float* b, uint8 dim);

void matrix_transpose(float* a, uint8 dim);
void matrix_multiply(float* a, float* b, float* out, uint8 dim);
void matrix_multiply_s(float* a, float s, uint8 dim);
void matrix_multiply_v(float* v, float* a, uint8 dim);

/* Only for 4x4 matrices */
// void matrix_orthogonal(float* a);
void matrix_perspective(float* a, float fov, float aspect, float near, float far);
void matrix_view(float* a, float* pos, float* front, float* up, float* right);
void matrix_lookat(float* a, float* pos, float* up, float* eye);
void matrix_translate(float* a, float* v);
void matrix_translate_sub(float* a, float* v);
void matrix_translate_add(float* a, float* v);
void matrix_scale(float* a, float* v);
void matrix_rotate(float* a, float angle, enum Axis axis);

void matrix_frustum(float* a, float n, float f, float l, float r, float b, float t);

#endif
