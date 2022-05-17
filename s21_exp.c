#include "s21_math.h"

long double s21_exp(double x) {
    // Error handling
    if (x == S21_NAN) return S21_NAN;
    if (x == -S21_INF) return 0;
    if (x == S21_INF) return S21_INF;

    long double t, s;
    int p;
    p = 0;
    long double arg = (long double)x;
    s = (long double)1;
    t = (long double)1;
    while (s21_fabs(t / s) > 1e-100) {
        p++;
        t = (t * arg) / p;
        s += t;
    }
    return s;
}
