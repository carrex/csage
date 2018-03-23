#include "math.h"

#include "maths.h"
#include "matrix.h"

void _mat_print(float* mat, uint8 dim)
{
	printf("Mat%dx%d:\n", dim, dim);
	for (uint8 j = 0; j < dim; j++) {
		printf((j % (dim-1) == 0? "   [": "   |"));
		for (uint8 i = 0; i < dim; i++) {
			printf("%5.2f ", mat[j*dim + i]);
		}
		printf("\b%s\n", (j % (dim-1) == 0? " ]": " |"));
	}
}

void _mat_copy(float* mat1, float* mat2, uint8 dim)
{
	for (uint8 j = 0; j < dim; j++)
		for (uint8 i = 0; i < dim; i++)
			mat1[j*dim + i] = mat2[j*dim + i];
}

void _mat_transpose(float* mat, uint8 dim)
{
	float* tmp = malloc(sq((uint32)dim) * (uint32)sizeof(float));
	if (!tmp)
		ERROR("[MATHS] Failed to allocate memory");
	mat_copy(tmp, mat, dim);
	for (uint8 j = 0; j < dim; j++)
		for (uint8 i = 0; i < dim; i++)
			mat[j*dim + i] = tmp[i*dim + j];
	free(tmp);
}

void _mat_multiplys(float* mat, float s, uint8 dim)
{
	for (uint8 j = 0; j < dim; j++)
		for (uint8 i = 0; i < dim; i++)
			mat[j*dim + i] *= s;
}

void _mat_multiply(float* mat1, float* mat2, float* out, uint8 dim1, uint8 dim2)
{
	for (uint8 j = 0; j < dim2; j++) {
		for (uint8 i = 0; i < dim1; i++) {
			out[i*dim1 + j] = 0.0;
			for (uint8 k = 0; k < dim2; k++) {
				out[i*dim1 + j] += mat1[i*dim1 + k] * mat2[k*dim2 + j];
			}
		}
	}
}

/* Only works for 4x4 matrices */
void _mat_translate(float* mat, float* vec, uint8 dim)
{
	mat[12] = vec[0];
	mat[13] = vec[1];
	mat[14] = vec[2];
	// for (uint8 i = 0; i < dim - 1; i++)
		// mat[12 + i] = vec[i];
}

/* Only works for 4x4 matrices */
void _mat_rotate(float* mat, float angle, uint8 dim, enum Axis axis)
{
	(void)dim;
	float sina = (float)sin(angle);
	float cosa = (float)cos(angle);
	switch (axis) {
		case X_AXIS:
			mat[5]  *=  cosa;
			mat[6]  *=  sina;
			mat[9]  *= -sina;
			mat[10] *=  cosa;
			break;
		case Y_AXIS:
			mat[0]  *=  cosa;
			mat[2]  *= -sina;
			mat[8]  *=  sina;
			mat[10] *=  cosa;
			break;
		case Z_AXIS:
			mat[0] *=  cosa;
			mat[1] *=  sina;
			mat[4] *= -sina;
			mat[5] *=  cosa;
			break;
	}
}
