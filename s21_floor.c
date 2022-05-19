#include "s21_math.h"

long double s21_floor(double x) {
    if (is_nan(x))
        return S21_NAN;

    if (!is_finite(x) || s21_fabs(x) >= TWO52)
        return x;

    long long val = x;

    if (x != val && s21_fabs(val) > EPS)
        val -= 1;

    return val;
}
