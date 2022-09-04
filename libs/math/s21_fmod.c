#include "s21_math.h"

long double s21_fmod(double x, double y) {
    if (is_nan(x) || is_nan(y) || is_inf(x) || s21_fabs(y) < EPS ||
        (is_inf(x) && is_inf(y)))
        return S21_NAN;
    if (s21_fabs(x) < EPS)
        return 0;
    if (is_inf(y))
        return x;

    long double lx = x;
    long double ly = y;
    long long div = x / y;
    return lx - div * ly;
}
