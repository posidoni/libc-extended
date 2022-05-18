#include "s21_math.h"

long double s21_fabs(double x) {
    // TODO Remove unnecessary returns
    if (is_nan(x))
        return S21_NAN;
    if (!is_finite(x)) {
        return x;
    }

    // TODO Replace the comparison of doubles
    return x < 0 ? -x : x;
}
