#include "s21_math.h"

static long double handle_special_cases(double n, long double root);

long double s21_sqrt(double n) {
    long double x = n;
    long double root = 0.0;

    if (n > EPS && is_normal(n)) {
        while (1) {
            root = 0.5 * (x + (n / x));

            if (s21_fabs(root - x) < 1e-12)
                break;

            x = root;
        }
    } else {
        errno = EDOM;
    }

    if (n < EPS && n > -EPS)
        return 0.0;

    return (n > EPS) ? handle_special_cases(n, root) : S21_NAN;
}

static long double handle_special_cases(double n, long double root) {
    return is_nan(n) ? S21_NAN : is_finite(n) ? root
                                              : S21_INF;
}
