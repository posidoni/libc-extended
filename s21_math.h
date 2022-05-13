#ifndef S21_MATH
#define S21_MATH

#include <math.h>  // (!) delete
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const unsigned long long factorials[21] = {
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

#endif  //  S21_MATH
