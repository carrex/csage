#ifndef QUATERNION_H
#define QUATERNION_H

#define QUAT_NORM_EPSILON 0.005f // 0.995 < |q| < 1.005

void quat_print(float* q);                                          // [Quaternion(mag|deg): w|x|y|z]
void quat_new_versor(float* q, float w, float x, float y, float z); // q = (w, x, y, z)
void quat_new_versor_v(float* q, float w, float* v);                // q = (w, v)
void quat_copy(float* q, float* p);                                 // p = q

float quat_angle(float* q);               // 2*acos(w)
float quat_magnitude(float* q);           // |q|
void  quat_normalise(float* q);           // |q| = 1 (+- QUAT_NORM_EPSILON)
void  quat_conjugate(float* q, float* p); // p = ~q

void quat_multiply(float* q, float* p);    // p = (q)(p)
void quat_multiply_qv(float* q, float* v); // v = (q)(v)
void quat_multiply_vq(float* v, float* q); // v = (v)(q)

void quat_rotate(float* q, float* p);   // p = (q)(p)(~q)
void quat_rotate_v(float* q, float* v); // v = (q)(v)(~q)

void quat_to_vector(float* q, float* v); // truncates w component
void quat_to_matrix(float* q, float* a); // creates a rotation matrix

#endif
