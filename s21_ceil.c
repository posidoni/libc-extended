#include "s21_math.h"
#include <stdio.h>

long double s21_ceil(double x) {
    if (!is_finite(x) || fabs(x) >= TWO52)
        return x;

    long double val = (long long)x;

    if (x != val && val > 0) {
        if (val != DBL_MAX)
            val += 1;
        else
            return val = S21_INF;
    }

    return val;
}
