#include "s21_math.h"

long double s21_log(double x) {
    long double res = 0.0L;
    const long double ln2 = 0.6931471805599453L;

    /* Special cases */

    // if (x == 1.0)
    if (fabs(x - 1.0) < EPS) {
        return 0.0L;
    }

    if (is_nan(x)) {
        return NAN;
    }

    if (!is_finite(x) && x > 0) {
        return INFINITY;
    }

    if (x == 0.0L) {
        errno = ERANGE;
        return -INFINITY;
    }

    if (x < 0.0) {
        errno = EINVAL;
        return NAN;
    }

    /* Special cases END */

    if (x < 2.0) {
        for (int i = 1; i < 100000; i++) {
            long double a = (i % 2) ? -1 : 1;
            long double b = pow((x - 1), i);
            res -= (a * b) / i;
        }
    } else {
        long double m = 0.0L;
        long double p = 0.0L;

        while (x > 2.0) {
            m = x / 2.0;
            x /= 2.0;
            p++;
        }

        res = s21_log(m) + p * ln2;
    }

    return res;
}

// make static function for checking special value
