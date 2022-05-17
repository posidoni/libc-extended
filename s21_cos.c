#include "s21_math.h"

long double s21_cos(double x) {
    if (x == S21_NAN || x == S21_INF || x == -S21_INF) return S21_NAN;

    long double t, s;
    int m = 1;
    x = s21_fmod(x, 2 * S21_M_PI);

    if (x > (S21_M_PI / 2.0) && x <= S21_M_PI) {
        x = S21_M_PI - x;
        m = -m;
    } else if (x > S21_M_PI && x <= S21_M_PI * 3.0 / 2.0) {
        x = (x - S21_M_PI);
        m = -m;
    } else if (x > (S21_M_PI * 3.0) / 2.0 && x <= 2.0 * S21_M_PI) {
        x = 2 * S21_M_PI - x;
    }

    int p = 0;
    s = 1.0;
    t = 1.0;
    while (s21_fabs(t / s) > 1e-100) {
        p++;
        t = (-t * x * x) / ((2 * p - 1) * (2 * p));
        s += t;
    }
    return s * m;
}