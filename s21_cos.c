#include "s21_math.h"

long double s21_cos(double x) {
<<<<<<< HEAD
    if (is_nan(x) || !is_finite(x)) return S21_NAN;
=======
    // TODO Replace the comparison of doubles
    if (x == S21_NAN || x == S21_INF || x == -S21_INF) return S21_NAN;
>>>>>>> 85ddb17 (Add TODO)

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

<<<<<<< HEAD
    long double sum = 1.0;
    long double tailor = 1.0;
<<<<<<< HEAD:s21_cos.c
=======

>>>>>>> 3b6eab5 (Minor fix, uncommented targets in makefile, removed math.h, GCOV untested):src/s21_cos.c
    for (int p = 1; s21_fabs(tailor / sum) > 1e-100; p++) {
        tailor = (-tailor * x * x) / ((2.0 * p - 1) * (2.0 * p));
        sum += tailor;
=======
    int p = 0;
    s = 1.0;
    t = 1.0;
    // TODO Move to constant
    while (s21_fabs(t / s) > 1e-100) {
        p++;
        t = (-t * x * x) / ((2 * p - 1) * (2 * p));
        s += t;
>>>>>>> 85ddb17 (Add TODO)
    }
    return sum * sign;
}
