#include "s21_math.h"

// long double s21_sin(double x) {
//     long double res = 0.0;
//     long double sign = 1.0;
//     long double n = (long double)x;
//     long double m = 1;
//     if (n < 0) {
//         n = -n;
//         m = -1;
//     }

//     n = fmodl(n, (long double)(2.0 * S21_M_PI));

//     if (n > (S21_M_PI / 2.0) && n <= S21_M_PI) {
//         n = S21_M_PI - n;
//     } else if (n > S21_M_PI && n <= S21_M_PI * 3.0 / 2.0) {
//         n = (n - S21_M_PI);
//         m = -m;
//     } else if (n > (S21_M_PI * 3.0) / 2.0 && n <= 2.0 * S21_M_PI) {
//         n = 2 * S21_M_PI - n;
//         m = -m;
//     }

//     for (int i = 0; (2 * i + 1) <= 20; i++) {
//         res += sign * (powl(n, 2 * i + 1) / (long double)factorials[2 * i + 1]);  // s21_pow (!)
//         sign = -sign;
//     }
//     return m * res;
// }

long double s21_sin(double x) {
    if (x == S21_NAN || x == S21_INF || x == -S21_INF) return S21_NAN;

    int m = 1;
    x = s21_fmod(x, 2 * S21_M_PI);

    if (x > (S21_M_PI / 2.0) && x <= S21_M_PI) {
        x = S21_M_PI - x;
    } else if (x > S21_M_PI && x <= S21_M_PI * 3.0 / 2.0) {
        x = (x - S21_M_PI);
        m = -m;
    } else if (x > (S21_M_PI * 3.0) / 2.0 && x <= 2.0 * S21_M_PI) {
        x = 2 * S21_M_PI - x;
        m = -m;
    }

    long double t, s;
    s = (long double)x;
    t = (long double)x;
    int p = 0;
    while (s21_fabs(t / s) > 1e-100) {
        p++;
        t = (-t * x * x) / ((2.0 * p + 1) * (2.0 * p));
        s += t;
    }
    return s * m;
}