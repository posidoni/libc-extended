#include "s21_math.h"

long double s21_atan(double x) {
    long double res = 0.0;
    /* Sqrt of square looks a bit reduntant, but the formula was like that (?) */
    long double magic = (M_PI * sqrt(x * x)) / (2 * x);
    long double n = x;
    int modulo_x = (fabs(x) < 0);

    for (int i = 0; i < 20; i++) {
        if (modulo_x) {
            res += (pow(-1, i) * pow(x, 1 + 2 * i)) / (1 + 2 * i);
        } else {
            res += (pow(-1, i) * pow(x, (-1 - 2 * i))) / (1 + 2 * i);
        }
    }

    return (modulo_x < 0) ? res : magic - res;
}
