#include "s21_math.h"

long double s21_exp(double x) {
    long double t, s;
    int p;
    p = 0;
    long double arg = (long double)x;
    s = (long double)1;
    t = (long double)1;
    while (fabs(t / s) > 1e-1000) {
        p++;
        t = (t * arg) / p;
        s += t;
    }
    // static int t_n = 0;
    // printf("TESTN%d, %Lf %Lf\n", t_n++, s, expl(x));
    return s;
}