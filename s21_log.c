#include "s21_math.h"

long double s21_log(double x) {
    // TODO Remove unnecessary returns
    long double res = 0.0L;
    // TODO Move the definition below
    const long double ln2 = 0.6931471805599453L;

    /* Special cases */

    // if (x == 1.0)
    if (s21_fabs(x - 1.0) < EPS && is_finite(x)) {
        return 0.0L;
    }


    if (!is_finite(x) && x > 0) {
        return S21_INF;
    }

    if (x < 0.0 || (!is_finite(x)) || is_nan(x)) {
        errno = EINVAL;
        return S21_NAN;
    }

    // TODO Replace the comparison of doubles
    if (x == 0.0L) {
        errno = ERANGE;
        return -S21_INF;
    }

    /* Special cases END */

    // TODO Replace the comparison of doubles
    if (x < 2.0) {
        // TODO Replace to constant
        for (int i = 1; i < 100000; i++) {
            long double a = (i % 2) ? -1 : 1;
            long double b = s21_pow((x - 1), i);
            res -= (a * b) / i;
        }
    } else {
        long double m = 0.0L;
        long double p = 0.0L;

        // TODO Replace the comparison of doubles
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
