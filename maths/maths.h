#ifndef MATHS_H
#define MATHS_H

#include <stdlib.h>
#include <math.h>
#include <float.h>

#include <cblas.h>

#include "common.h"
#include "vector.h"
#include "matrix.h"
#include "quaternion.h"

#define PI 3.14159265358979323846
#define E  2.71828182845904523536

#define radians(deg) ((deg / 360.0) * (2.0 * PI))
#define degrees(rad) ((rad / (2.0 * PI)) * 360.0)

#define is_equal(a, b) (bool)(_Generic((a),          \
	float : ((fabsf(a)) - (fabsf(b)) < FLT_EPSILON), \
    double: ((fabs(a))  - (fabs(b))  < DBL_EPSILON)))

#endif
