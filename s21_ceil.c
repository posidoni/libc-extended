#include "s21_math.h"

long double s21_ceil(double x) {
    if (!is_finite(x) || s21_fabs(x) >= TWO52)
        return x;

    long double val = (long long)x;

    if (x != val && s21_fabs(val) > EPS) {
        if (val != DBL_MAX)
            val += 1;
        else
            return val = S21_INF;
    }

    return val;
}
