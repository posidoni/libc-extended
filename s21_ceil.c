#include "s21_math.h"

long double s21_ceil(double x) {
    // TODO Remove unnecessary returns
    if (!is_finite(x) || s21_fabs(x) >= TWO52)
        return x;

    long double val = (long long)x;

    // TODO Replace the comparison of doubles
    if (x != val && val > 0) {
        if (val != DBL_MAX)
            val += 1;
        else
            return val = S21_INF;
    }

    return val;
}
