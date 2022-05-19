#include "s21_math.h"

long double s21_acos(double x) {
    // TODO Move the definition below
    const long double zero_acos = 1.5707963267948966;
    long double res = 0.0;

    if (s21_ldeq(x, 0.0))
        return zero_acos;

    s21_bool mod = (s21_fabs(x) > 1.0);
    s21_bool sign = (x > 0.0);

    /* These inputs DO NOT raise errno (unlike |x| > 1.0) */
    s21_bool invalid = ((is_nan(x) || !is_finite(x)) && !s21_ldeq(x, 0.0));

    if (!sign && !invalid && !s21_ldeq(x, 0.0)) {
        return (S21_M_PI - s21_acos(x * -1.0));
    }

    if (!invalid) {
        mod = (s21_fabs(x) > 1.0);
        if (mod) {
            errno = EDOM;
        } else if (s21_ldeq(x, 1.0)) {
            res = 0.0;
        } else if (s21_ldeq(x, -1.0)) {
            res = S21_M_PI;
        } else if (s21_fabs(x) > 0.0) {
            if (s21_ldeq(x, 0.0))
                res = zero_acos;
            else
                res += s21_atan_custom(s21_sqrt(1 - x * x) / x);
        }
    }

    return (mod || invalid) ? S21_NAN : res;
}
