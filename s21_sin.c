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

//     n = fmodl(n, (long double)(2.0 * M_PI));

//     if (n > (M_PI / 2.0) && n <= M_PI) {
//         n = M_PI - n;
//     } else if (n > M_PI && n <= M_PI * 3.0 / 2.0) {
//         n = (n - M_PI);
//         m = -m;
//     } else if (n > (M_PI * 3.0) / 2.0 && n <= 2.0 * M_PI) {
//         n = 2 * M_PI - n;
//         m = -m;
//     }

//     for (int i = 0; (2 * i + 1) <= 20; i++) {
//         res += sign * (powl(n, 2 * i + 1) / (long double)factorials[2 * i + 1]);  // s21_pow (!)
//         sign = -sign;
//     }
//     return m * res;
// }

long double s21_sin(double x) {
    int invalid = (isnan(x) || !isfinite(x));

    long double t, s;
    int m = 1;
    if (!invalid) {
        x = fmodl(x, 2 * M_PI);

        if (x > (M_PI / 2.0) && x <= M_PI) {
            x = M_PI - x;
        } else if (x > M_PI && x <= M_PI * 3.0 / 2.0) {
            x = (x - M_PI);
            m = -m;
        } else if (x > (M_PI * 3.0) / 2.0 && x <= 2.0 * M_PI) {
            x = 2 * M_PI - x;
            m = -m;
        }

        s = (long double)x;
        t = (long double)x;
        int p;
        p = 0;
        while (fabsl(t / s) > 1e-100) {
            p++;
            t = (-t * x * x) / ((2.0 * p + 1) * (2.0 * p));
            s += t;
        }
    }
    return invalid ? NAN : s * m;
}