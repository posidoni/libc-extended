#include "s21_math.h"

long double s21_fmod(double x, double y) {
    /* if (is_nan(x) || is_nan(y)) */
    /*     return S21_NAN; */

    /* if ((x == 0 || is_inf(x)) || (is_inf(x) && is_inf(y))) */
    /*     return S21_NAN; */

    /* if (!is_nan(y) && y != 0) */
    /*     return 0; */

    /* if (is_inf(y)) */
    /*     return x; */

    long double lx = x;
    long double ly = y;
    long double div = trunc(x / y);

    return lx - div * ly;
}

long double s21_trunc(double val) {
    if (val > 0)
        val = s21_floor(val);
    else
        val = s21_ceil(val);
    return val;
}
