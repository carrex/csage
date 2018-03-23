#include "maths.h"

void mat_print(float* a, uint8 dim)
{
	printf("Mat%dx%d:\n", dim, dim);
	for (uint8 j = 0; j < dim; j++) {
		printf((j % (dim-1) == 0? "   [": "   |"));
		for (uint8 i = 0; i < dim; i++) {
			printf("%5.2f ", a[j*dim + i]);
		}
		printf("\b%s\n", (j % (dim-1) == 0? " ]": " |"));
	}
}

void mat_copy(float* out, float* a, uint8 dim)
{
	for (uint8 j = 0; j < dim; j++)
		for (uint8 i = 0; i < dim; i++)
			out[j*dim + i] = a[j*dim + i];
}

void mat_transpose(float* a, uint8 dim)
{
	float* tmp = malloc(sq((size_t)dim) * sizeof(float));
	if (!tmp)
		ERROR("[MATHS] Failed to allocate memory");
	mat_copy(tmp, a, dim);
	for (uint8 j = 0; j < dim; j++)
		for (uint8 i = 0; i < dim; i++)
			a[j*dim + i] = tmp[i*dim + j];
	free(tmp);
}

void mat_multiply(float* out, float* a, float* b, uint8 dim)
{
	for (uint8 j = 0; j < dim; j++) {
	    for (uint8 i = 0; i < dim; i++) {
	        out[j*dim + i] = 0.0f;
	        for (uint8 k = 0; k < dim; k++)
	            out[j*dim + i] += a[j*dim + k] * b[k*dim + i];
	    }
	}
}

void mat_multiply_s(float* a, float s, uint8 dim)
{
	for (uint8 j = 0; j < dim; j++)
		for (uint8 i = 0; i < dim; i++)
			a[j*dim + i] *= s;
}

void mat_multiply_vec(float* v, float* a, uint8 dim)
{
	for (uint8 j = 0; j < dim; j++) {
	    v[j] = 0.0f;
	    for (uint8 i = 0; i < dim; i++)
	    	v[j] += a[i*dim + j];
	}
}

void mat_scale(float* out, float* v, uint8 dim)
{
	if (dim != 4)
		ERROR("dim(%u) must be 4", dim);

	out[0]  = v[0];
	out[5]  = v[1];
	out[10] = v[2];
}

void mat_translate(float* out, float* v, uint8 dim)
{
	if (dim != 4)
		ERROR("dim(%u) must be 4", dim);

	out[12] = v[0];
	out[13] = v[1];
	out[14] = v[2];
}

void mat_rotate(float* out, float angle, uint8 dim, enum Axis axis)
{
	if (dim != 4)
		ERROR("dim(%d) must be 4", dim);

	float sina = (float)sin(angle);
	float cosa = (float)cos(angle);
	switch (axis) {
		case X_AXIS:
			out[5]  *=  cosa;
			out[6]  *=  sina;
			out[9]  *= -sina;
			out[10] *=  cosa;
			break;
		case Y_AXIS:
			out[0]  *=  cosa;
			out[2]  *= -sina;
			out[8]  *=  sina;
			out[10] *=  cosa;
			break;
		case Z_AXIS:
			out[0] *=  cosa;
			out[1] *=  sina;
			out[4] *= -sina;
			out[5] *=  cosa;
			break;
	}
}
