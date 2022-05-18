#include "s21_math.h"

long double s21_floor(double x) {
    // TODO Remove unnecessary returns
    if (is_nan(x))
        return S21_NAN;
    if (!is_finite(x) || s21_fabs(x) >= TWO52)
        return x;

    long long val = x;

    // TODO Replace the comparison of doubles
    if (x != val && val > 0)
        val -= 1;

    return val;
}
