#include "s21_math.h"

long double s21_asin(double x) {
    const long double one_asin = 1.5707963267948966;
    long double res = 0.0;
    int mod = 0;

    /* These inputs DO NOT raise errno (unlike |x| > 1.0) */
    int invalid = (is_nan(x) || !is_finite(x));

    if (!invalid) {
        mod = (s21_fabs(x) > 1);

        if (mod) {
            errno = EDOM;
        } else {
            /* Not sure are we allowed to compare them like that */
            if (x == 1.0) res = one_asin;
            if (x == -1.0) res = -one_asin;

            if (x != 0.0 && s21_fabs(res) != one_asin) { res += s21_atan(x / s21_sqrt(1 - x * x)); }
        }
    }

    return (mod || invalid) ? S21_NAN : res;
}
