#ifndef MATHS_H
#define MATHS_H

#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "vector.h"
#include "matrix.h"

#define PI 3.14159265358979
#define E  2.71828182845904

#define sq(x) ((x) * (x))
#define radians(deg) ((deg / 360.0) * (2.0 * PI))
#define degrees(rad) ((rad / (2.0 * PI)) * 360.0)

#endif
