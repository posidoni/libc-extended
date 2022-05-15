#include "s21_math.h"
#include <stdio.h>

long double s21_ceil(double x) {
    if (!is_finite(x))
        return x;

    long long val = x;
    if (x != (double)val) {
        if (val > 0) {
            if (val != DBL_MAX)
                val += 1;
            else
                val = S21_INF;
        }
    }

    return val;
}
