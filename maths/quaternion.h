#ifndef QUATERNION_H
#define QUATERNION_H

/* May need to have a normal check due to FPE */

void quat_new_versor(float* out, float x, float y, float z, float angle); // angle in radians
void quat_normalise(float* quat);
void quat_mul(float* out, float* quat1, float* quat2);
void quat_to_matrix(float* quat, float* mat);

#endif
