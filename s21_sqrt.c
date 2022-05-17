#include "s21_math.h"

// If a domain error occurs, an implementation-defined value is returned (NaN where supported)

// If a range error occurs due to underflow, the correct result (after rounding) is returned.

// Error handling
// Errors are reported as specified in math_errhandling

// Domain error occurs if arg is less than zero.

// If the implementation supports IEEE floating-point arithmetic (IEC 60559),

// If the argument is less than -0, FE_INVALID is raised and NaN is returned.
// If the argument is +∞ or ±0, it is returned, unmodified.
// If the argument is NaN, NaN is returned

static long double handle_special_cases(double n, long double root);

long double s21_sqrt(double n) {
    long double x = n;
    long double root = 0.0;

    if (n > 0.0 && isnormal(n)) {
        while (1) {
            root = 0.5 * (x + (n / x));

            if (fabsl(root - x) < 1e-12)
                break;

            x = root;
        }
    } else {
        errno = EDOM;
    }

    if (n == 0.0)
        return 0.0;

    return (n > 0) ? handle_special_cases(n, root) : NAN;
}

static long double handle_special_cases(double n, long double root) {
    long double res = root;
    return isnan(n) ? NAN : isfinite(n) ? res
                                        : INFINITY;
}
