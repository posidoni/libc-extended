#include "s21_math.h"

long double s21_exp(double x) {
    if (x == S21_NAN)
        return S21_NAN;
    if (x == -S21_INF)
        return 0;
    if (x == S21_INF)
        return S21_INF;

    long double arg = (long double)x;
    long double sum = 1.0;
    long double tailor = 1.0;

    for (int p = 1; s21_fabs(tailor / sum) > 1e-100; p++) {
        tailor = (tailor * arg) / p;
        sum += tailor;
    }
    return sum;
}
