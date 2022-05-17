#include "s21_math.h"

long double s21_exp(double x) {
    // Error handling
    if (x == NAN) return NAN;
    if (x == -INFINITY) return 0;
    if (x == INFINITY) return INFINITY;
    if (x == 0) return 1;

    long double t, s;
    int p;
    p = 0;
    long double arg = (long double)x;
    s = (long double)1;
    t = (long double)1;
    while (fabsl(t / s) > 1e-100) {
        p++;
        t = (t * arg) / p;
        s += t;
    }
    return s;
}
