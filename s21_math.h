#ifndef S21_MATH
#define S21_MATH

#define s21_true 1
#define s21_false 0
#define s21_bool int

#include <errno.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 1e-6
#define EPS_8 1e-7
#define S21_M_PI 3.14159265358979323846264338327950288
#define S21_M_PI_2 1.57079632679489661923132169163975144

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
#define is_normal(x) __builtin_isnormal(x)

#define TWO52 0x1.0p52 /* 2^52 */

/* Lib */

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

/* Helpers */
long double s21_trunc(double val);
s21_bool s21_ldeq(long double a, long double b);
long double s21_atan_custom(double x);

#endif  //  S21_MATH
