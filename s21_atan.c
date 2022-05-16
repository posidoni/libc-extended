#include "s21_math.h"

long double s21_atan(double x) {
    long double res = 0.0;
    /* Warning! Replaced sqrt(x^2) with fabs(x) in the original formula */
    long double magic = (M_PI * fabs(x)) / (2 * x);
    int modulo_x = (fabs(x) < 0);

    for (int i = 0; i < 30; i++) {
        if (modulo_x) {
            res += (pow(-1, i) * pow(x, 1 + 2 * i)) / (1 + 2 * i);
        } else {
            res += (pow(-1, i) * pow(x, (-1 - 2 * i))) / (1 + 2 * i);
        }
    }

    return (modulo_x < 0) ? res : magic - res;
}
