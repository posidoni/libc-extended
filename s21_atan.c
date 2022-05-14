#include "s21_math.h"

long double s21_atan(double x) {
    long double res = 0.0;
    long double sign = -1.0;
    long double n = (long double)x;

    long double magic = 3;
    long double exp = 3;

    for (int i = 0; exp < 16; i++) {
        res += sign * (powl(n, exp) / magic);
        exp += 2;
        magic += 2;
        sign = -sign;
    }

    return res;
}
