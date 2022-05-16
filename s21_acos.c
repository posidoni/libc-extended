#include "s21_math.h"

long double s21_acos(double x) {
    const long double zero_acos = 1.5707963267948966;
    long double res = 0.0;
    int mod = 0;

    /* These inputs DO NOT raise errno (unlike |x| > 1.0) */
    int invalid = (isnan(x) || !isfinite(x));

    if (!invalid) {
        mod = (fabsl(x) > 1.0);

        if (mod) {
            errno = EDOM;
        } else if (x == 1.0)  {
            res = 0.0;
        } else if (x == -1.0) {
            res = M_PI;
        } else {
            /* Not sure are we allowed to compare them like that */
            if (x == 0.0)
                res = zero_acos;

            if (x != 0.0) {
                res += s21_atan(s21_sqrt(1 - x * x) / x);
            }
        }
    }

    return (mod || invalid) ? NAN : res;
}
