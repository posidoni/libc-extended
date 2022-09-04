#include "s21_math.h"

long double s21_cos(double x) {
    if (is_nan(x) || !is_finite(x))
        return S21_NAN;

    int sign = 1;
    x = s21_fmod(x, 2 * S21_M_PI);

    if (x > (S21_M_PI / 2.0) && x <= S21_M_PI) {
        x = S21_M_PI - x;
        sign = -sign;
    } else if (x > S21_M_PI && x <= S21_M_PI * 3.0 / 2.0) {
        x -= S21_M_PI;
        sign = -sign;
    } else if (x > (S21_M_PI * 3.0) / 2.0 && x <= 2.0 * S21_M_PI) {
        x = 2 * S21_M_PI - x;
    }

    long double sum = 1.0;
    long double tailor = 1.0;

    for (int p = 1; s21_fabs(tailor / sum) > 1e-100; p++) {
        tailor = (-tailor * x * x) / ((2.0 * p - 1) * (2.0 * p));
        sum += tailor;
    }
    return sum * sign;
}
