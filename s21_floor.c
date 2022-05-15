#include "s21_math.h"

long double s21_floor(double x) {
    if (!is_finite(x) || fabs(x) >= TWO52)
        return x;

    long long val = x;

    if (x != val && val > 0) {
        val -= 1;
    }

    return val;
}
