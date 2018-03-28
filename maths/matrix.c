#include "maths.h"

void matrix_print(float* a, uint8 dim)
{
	printf("Matrix%dx%d:\n", dim, dim);
	for (uint8 j = 0; j < dim; j++) {
		printf((j % (dim-1) == 0? "   [": "   |"));
		for (uint8 i = 0; i < dim; i++) {
			printf("%5.2f ", a[j*dim + i]);
		}
		printf("\b%s\n", (j % (dim-1) == 0? " ]": " |"));
	}
}

void matrix_copy(float* a, float* b, uint8 dim)
{
	for (uint8 j = 0; j < dim; j++)
		for (uint8 i = 0; i < dim; i++)
			a[j*dim + i] = b[j*dim + i];
}

void matrix_transpose(float* a, uint8 dim)
{
	float* tmp = malloc(sq((size_t)dim) * sizeof(float));
	if (!tmp)
		ERROR("[MATHS] Failed to allocate memory");
	matrix_copy(tmp, a, dim);
	for (uint8 j = 0; j < dim; j++)
		for (uint8 i = 0; i < dim; i++)
			a[j*dim + i] = tmp[i*dim + j];
	free(tmp);
}

void matrix_multiply(float* out, float* a, float* b, uint8 dim)
{
	for (uint8 j = 0; j < dim; j++) {
	    for (uint8 i = 0; i < dim; i++) {
	        out[j*dim + i] = 0.0f;
	        for (uint8 k = 0; k < dim; k++)
	            out[j*dim + i] += a[j*dim + k] * b[k*dim + i];
	    }
	}
}

void matrix_multiply_s(float* a, float s, uint8 dim)
{
	for (uint8 j = 0; j < dim; j++)
		for (uint8 i = 0; i < dim; i++)
			a[j*dim + i] *= s;
}

void matrix_multiply_v(float* v, float* a, uint8 dim)
{
	for (uint8 j = 0; j < dim; j++) {
	    v[j] = 0.0f;
	    for (uint8 i = 0; i < dim; i++)
	    	v[j] += a[i*dim + j];
	}
}

/*****************************************************************************/

// void matrix_orthogonal(float* a)
// {

// }

/* https://stackoverflow.com/questions/1638355/function-for-perspective-projection-of-a-matrix-in-c */
void matrix_perspective(float* a, float fov, float aspect, float near, float far)
{
	// float sz = far / (near - far);
	// float sy = (float)(1.0 / tan(fov / 2.0));
	// float sx = sy / aspect;
	// float pw = (near * far) / (near - far);

	// matrix_copy(a, (float[]){ sx  , 0.0f, 0.0f,  0.0f,
	//                           0.0f, sy  , 0.0f,  0.0f,
	//                           0.0f, 0.0f, sz  , -1.0f,
	//                           0.0f, 0.0f, pw  ,  0.0f, }, 4);
	// float sx = aspect * (1.0f / (float)tan(fov / 2.0f));
	// float sy = 1.0f / (float)tan(fov / 2.0f);
	// float sz = -(far + near) / (far - near);
	// float pz = -2.0f * near * far / (far - near);

	// matrix_copy(a, (float[]){ sx  , 0.0f, 0.0f,  0.0f,
	//                           0.0f, sy  , 0.0f,  0.0f,
	//                           0.0f, 0.0f, sz  , -1.0f,
	//                           0.0f, 0.0f, pz  ,  0.0f, }, 4);
	float top   = near * tan(fov / 2.0);
	float right = top * aspect;
	matrix_frustum(a, near, far, -right, right, -top, top);
}

/* -View Matrix-
 * r.x u.x e.x 0
 * r.y u.y e.y 0
 * r.z u.z e.z 0
 *  A   B   C  1
 */
void matrix_view(float* a, float* pos, float* front, float* up, float* right)
{
	matrix_copy(a, (float[]){ right[0], up[0]  , front[0], 0.0f,
	                          right[1], up[1]  , front[1], 0.0f,
	                          right[2], up[2]  , front[2], 0.0f,
	                          -pos[0] , -pos[1], -pos[2] , 1.0f, }, 4);
}

/* rename */
void matrix_frustum(float* a, float n, float f, float l, float r, float b, float t)
{
   a[0]  = (2.0 * n) / (r - l);
   a[1]  = 0.0;
   a[2]  = 0.0;
   a[3]  = 0.0;
   a[4]  = 0.0;
   a[5]  = (2.0 * n) / (t - b);
   a[6]  = 0.0;
   a[7]  = 0.0;
   a[8]  =  (r + l) / (r - l);
   a[9]  =  (t + b) / (t - b);
   a[10] = -(f + n) / (f - n);
   a[11] = -1.0;
   a[12] = 0.0;
   a[13] = 0.0;
   a[14] = -(2.0 * f * n) / (f - n);
   a[15] = 0.0;
}

/* https://stackoverflow.com/questions/349050/calculating-a-lookat-matrix */
void matrix_lookat(float* a, float* pos, float* up, float* eye)
{
	float x[3], y[3], z[3], wx, wy, wz, neye[4];
	vec_copy_3d(neye, eye);
	vec_mul_3d(neye, -1.0f);
	vec_difference_3d(z, pos, neye);
	vec_cross(x, up, z);
	vec_cross(y, z, x);
	wx = -vec_dot_3d(x, neye);
	wy = -vec_dot_3d(y, neye);
	wz = -vec_dot_3d(z, neye);

	vec_normal_3d(x);
	vec_normal_3d(y);
	vec_normal_3d(z);
	matrix_copy(a, (float[]){ x[0], y[0], z[0], 0.0f,
	                       x[1], y[1], z[1], 0.0f,
	                       x[2], y[2], z[2], 0.0f,
	                       wx  , wy  , wz  , 1.0f, }, 4);
}

void matrix_scale(float* a, float* v)
{
	a[0]  = v[0];
	a[5]  = v[1];
	a[10] = v[2];
}

void matrix_translate(float* a, float* v)
{
	a[12] = v[0];
	a[13] = v[1];
	a[14] = v[2];
}

void matrix_translate_sub(float* a, float* v)
{
	a[12] -= v[0];
	a[13] -= v[1];
	a[14] -= v[2];
}

void matrix_translate_add(float* a, float* v)
{
	a[12] += v[0];
	a[13] += v[1];
	a[14] += v[2];
}

void matrix_rotate(float* a, float angle, enum Axis axis)
{
	float sina = (float)sin(angle);
	float cosa = (float)cos(angle);
	switch (axis) {
		case X_AXIS:
			a[5]  *=  cosa;
			a[6]  *=  sina;
			a[9]  *= -sina;
			a[10] *=  cosa;
			break;
		case Y_AXIS:
			a[0]  *=  cosa;
			a[2]  *= -sina;
			a[8]  *=  sina;
			a[10] *=  cosa;
			break;
		case Z_AXIS:
			a[0] *=  cosa;
			a[1] *=  sina;
			a[4] *= -sina;
			a[5] *=  cosa;
			break;
	}
}
