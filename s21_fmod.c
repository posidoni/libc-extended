#include "s21_math.h"

long double s21_fmod(double x, double y) {
    // returns a NaN for x infinite or y zero.
    if (is_nan(x) || is_nan(y) || (is_inf(x) && is_inf(y)) || (is_inf(x) || y == 0)) return S21_NAN;

    // fmod(+-0, y) returns +-0 if y is neither 0 nor NaN
    if (x == 0 && !is_nan(y) && y != 0) return 0;
    // fmod(x, +-infinity) returns x for x not infinite.
    if (is_inf(y) && !is_inf(x)) return x;

    long double lx = x;
    long double ly = y;
    long long div = x / y;
    return lx - div * ly;
}
