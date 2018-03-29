#include "maths.h"

void mat_print(float* a, uint8 dim)
{
	printf("Matrix%dx%d:\n", dim, dim);
	for (uint8 j = 0; j < dim; j++) {
		printf((j % (dim-1) == 0? "   [": "   |"));
		for (uint8 i = 0; i < dim; i++) {
			printf("%6.3f ", (double)a[j*dim + i]);
		}
		printf("\b%s\n", (j % (dim-1) == 0? " ]": " |"));
	}
}

void mat4_new_scale(float* a, float* v)
{
	a[0]  = v[0];
	a[5]  = v[1];
	a[10] = v[2];
	a[15] = 1.0f;
}

void mat4_scale(float* a, float* v)
{
	a[0]  *= v[0];
	a[5]  *= v[1];
	a[10] *= v[2];
}

void mat4_new_translate(float* a, float* v)
{
	a[0]  = 1.0f;
	a[5]  = 1.0f;
	a[10] = 1.0f;
	a[15] = 1.0f;
	a[12] = v[0];
	a[13] = v[1];
	a[14] = v[2];
}

void mat4_translate(float* a, float* v)
{
	a[12] += v[0];
	a[13] += v[1];
	a[14] += v[2];
}

void mat4_new_perspective(float* a, float aspect, float fov, float znear, float zfar)
{
	float top   = znear * (float)tan((double)fov / 2.0),
	      right = top * aspect;
	float rl = 2.0f * right,
	      tb = 2.0f * top,
	      fn = zfar - znear,
	      n2 = 2.0f * znear;
	a[0]  = (n2 / rl);
	a[5]  = (n2 / tb);
	a[10] = -(zfar + znear) / fn;
	a[11] = -1.0f;
	a[14] = -(n2 * zfar) / fn;
	a[15] = 0.0f;
}
