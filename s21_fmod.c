#include "s21_math.h"

long double s21_fmod(double x, double y) {
    // TODO Remove unnecessary returns
    // returns a NaN for x infinite or y zero.
<<<<<<< HEAD
<<<<<<< HEAD
    if (is_nan(x) || is_nan(y) || is_inf(x) || fabs(y) < EPS ||
=======
    if (is_nan(x) || is_nan(y) || is_inf(x) || s21_fabs(y) < EPS ||
>>>>>>> 85ddb17 (Add TODO)
        (is_inf(x) && is_inf(y)))
        return S21_NAN;
    // fmod(+-0, y) returns +-0 if y is neither 0 nor NaN
    if (s21_fabs(x) < EPS)
        return 0;
    // fmod(x, +-infinity) returns x for x not infinite.
    if (is_inf(y))
=======
    if (is_nan(x) || is_nan(y) || (is_inf(x) && is_inf(y)) ||
        (is_inf(x) || y == 0))
        return S21_NAN;

    // fmod(+-0, y) returns +-0 if y is neither 0 nor NaN
    if (x == 0 && !is_nan(y) && y != 0)
        return 0;
    // fmod(x, +-infinity) returns x for x not infinite.
    if (is_inf(y) && !is_inf(x))
>>>>>>> 5030aeb (added all the nasty edge casesg)
        return x;

    long double lx = x;
    long double ly = y;
    long long div = x / y;
    return lx - div * ly;
}
