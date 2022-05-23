#include "s21_math.h"

long double s21_exp(double x) {
    if (x == S21_NAN)
        return S21_NAN;
    if (x == -S21_INF)
        return 0;
    if (x == S21_INF)
        return S21_INF;

    long double arg = (long double)x;
<<<<<<< HEAD
    long double sum = 1.0;
    long double tailor = 1.0;
<<<<<<< HEAD:s21_exp.c
=======

>>>>>>> 3b6eab5 (Minor fix, uncommented targets in makefile, removed math.h, GCOV untested):src/s21_exp.c
    for (int p = 1; s21_fabs(tailor / sum) > 1e-100; p++) {
        tailor = (tailor * arg) / p;
        sum += tailor;
=======
    s = (long double)1;
    t = (long double)1;
    // TODO Replace to constant
    while (s21_fabs(t / s) > 1e-100) {
        p++;
        t = (t * arg) / p;
        s += t;
>>>>>>> 85ddb17 (Add TODO)
    }
    return sum;
}
