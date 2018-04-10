#ifndef QUATERNION_H
#define QUATERNION_H

#define IQ  { 1.0f, 0.0f, 0.0f, 0.0f }
#define IQA ((float[])IQ)

void quat_print(float* q);                                   // "[Quaternion(mag|deg): w|x|y|z]"
void quat_new(float* q, float w, float x, float y, float z); // q = (w, x, y, z)
void quat_new_v(float* q, float w, float* v);                // q = (w, v)
void quat_copy(float* q, float* p);                          // p = q

float quat_angle(float* q);               // 2*acos(w)
float quat_mag(float* q);                 // ||q||
void  quat_normalise(float* q);           // ||q|| ~= 1.0
void  quat_conjugate(float* q, float* p); // p = q*

void quat_mul(float* q, float* p);    // p = (q)(p)
void quat_mul_qv(float* q, float* v); // v = (q)(v)
void quat_mul_vq(float* v, float* q); // v = (v)(q)

void quat_rotate(float* q, float* p);               // p = (q)(p)(q)
void quat_rotate_vec(float* q, float* v);           // v = (q)(v)(q*)
// void quat_rotate_dir(float* v, enum Direction dir); // v rotated 90* [dir]

void quat_to_vector(float* q, float* v); // truncates w (q[0]) component
void quat_to_matrix(float* q, float* a); // creates a rotation matrix

#endif
