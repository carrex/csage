#ifndef BLAS_H
#define BLAS_H

#include <cblas.h>

/* enum CBLAS_ORDER {CblasRowMajor=101, CblasColMajor=102};
 * enum CBLAS_TRANSPOSE {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113};
 * enum CBLAS_UPLO {CblasUpper=121, CblasLower=122};
 * enum CBLAS_DIAG {CblasNonUnit=131, CblasUnit=132};
 * enum CBLAS_SIDE {CblasLeft=141, CblasRight=142};
 */

#define mat4_vec4_mul(a, v) (cblas_gemv(CblasRowMajor, CblasNoTrans, 4, 4, 1.0, a, 4, v, 1, 0.0, NULL, 1))
// #define mat4_mat4_mul(a, b) ()

#endif
