#include "s21_math_test.h"

// If no errors occur, the natural (base-e) logarithm of arg (ln(arg) or log
// e(arg)) is returned.

// If a domain error occurs, an implementation-defined value is returned (NaN where supported)

// If a pole error occurs, -HUGE_VAL, -HUGE_VALF, or -HUGE_VALL is returned.

// zero , inf , - inf =>>> return the input without changes

// Pole errors occur when an operation has a result that is asymptotically infinite, such as divisions by zero, or log(0.0) . Pole error: division by zero, or some other asymptotically infinite result (from finite arguments).

// Error handling
// Errors are reported as specified in math_errhandling.

// Domain error occurs if arg is less than zero.

// Pole error may occur if arg is zero.

// If the implementation supports IEEE floating-point arithmetic (IEC 60559),

// If the argument is ±0, -∞ is returned and FE_DIVBYZERO is raised.
// If the argument is 1, +0 is returned
// If the argument is negative, NaN is returned and FE_INVALID is raised.
// If the argument is +∞, +∞ is returned
// If the argument is NaN, NaN is returned


Suite *suite_s21_log(void) {
    Suite *s = suite_create("suite_s21_add");
    TCase *tc = tcase_create("s21_add_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}
