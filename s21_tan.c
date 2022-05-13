#include "s21_math.h"

long double s21_tan(double x) {
    long double res = 0.0;
    long double n = (long double)x;

    long double m = 1;
    if (n < 0) {
        n = -n;
        m = -1;
    }

    n = fmodl(n, (long double)(M_PI));

    if (n > M_PI / 2.0) {
        n = M_PI - n;
        m = -1;
    }

    res = n + (powl(n, 3.0) / 3.0) + (2.0 * powl(n, 5.0) / 15.0) + (17.0 * powl(n, 7.0) / 315.0);

    return m * res;
}
