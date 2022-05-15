#ifndef S21_MATH
#define S21_MATH

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sets the value to INF
#define S21_INF (__builtin_inff())
// sets the value to NAN
#define S21_NAN (__builtin_nanf(""))
// returns non zero if not NAN or +-INF
#define is_finite(x) __builtin_isfinite(x)
// check if NAN
#define is_nan(x) __builtin_isnan(x)
// check for INF
#define is_inf(x) __builtin_isinf(x)

#define TWO52 0x1.0p52 /* 2^52 */

// [!] UNUSED VARIABLE DANGER
static const long double factorials[30] = {
    [0] = 1,
    [1] = 1,
    [2] = 2,
    [3] = 6,
    [4] = 24,
    [5] = 120,
    [6] = 720,
    [7] = 5040,
    [8] = 40320,
    [9] = 362880,
    [10] = 3628800,
    [11] = 39916800,
    [12] = 479001600,
    [13] = 6227020800,
    [14] = 87178291200,
    [15] = 1307674368000,
    [16] = 20922789888000,
    [17] = 355687428096000,
    [18] = 6402373705728000,
    [19] = 121645100408832000,
    [20] = 2432902008176640000,
    /*[21] = 51090942171709440000,
    [22] = 1124000727777607680000,
    [23] = 25852016738884976640000,
    [24] = 620448401733239439360000,
    [25] = 15511210043330985984000000,
    [26] = 403291461126605635584000000,
    [27] = 10888869450418352160768000000,
    [28] = 304888344611713860501504000000,
    [29] = 8841761993739701954543616000000,*/
};

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

// helpers
long double s21_trunc(double val);
#endif  //  S21_MATH
