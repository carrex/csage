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

// void mat_new_orthogonal(float* a);
void mat_new_perspective(float* a, float fov, float aspect, float near, float far);
void mat_new_lookat(float* a, float* pos, float* up, float* eye);
void mat_print(float* a, uint8 dim);
void mat_copy(float* a, float* b, uint8 dim); // a = b

void mat_transpose(float* a, uint8 dim);
void mat_translate(float* a, float* vec, uint8 dim);
void mat_rotate(float* a, float angle, uint8 dim, enum Axis axis);
void mat_multiply(float* a, float* b, float* out, uint8 dim);
void mat_multiply_s(float* a, float s, uint8 dim);
void mat_multiply_vec(float* vec, float* a, uint8 dim);


#endif
