#include "s21_math.h"

long double s21_cos(double x) {
    long double res = 0.0;
    long double sign = 1.0;
    long double n = (long double)x;
    long double m = 1;
    if (n < 0) {
        n = -n;
        // m = -1;
    }

    n = fmodl(n, (long double)(2.0 * M_PI));

    if (n > (M_PI / 2.0) && n <= M_PI) {
        n = M_PI - n;
        m = -m;
    } else if (n > M_PI && n <= M_PI * 3.0 / 2.0) {
        n = (n - M_PI);
        m = -m;
    } else if (n > (M_PI * 3.0) / 2.0 && n <= 2.0 * M_PI) {
        n = 2 * M_PI - n;
        // m = -m;
    }

    for (int i = 0; 2 * i <= 20; i++) {
        res += sign * (powl(n, 2 * i) / (long double)factorials[2 * i]);  // s21_pow (!)
        sign = -sign;
    }
    return m * res;
}