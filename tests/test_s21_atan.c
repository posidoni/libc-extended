#include "s21_math_test.h"

// Errors are reported as specified in math_errhandling.

// If the implementation supports IEEE floating-point arithmetic (IEC 60559),

// If the argument is ±0, it is returned unmodified
// If the argument is +∞, +π/2 is returned
// If the argument is -∞, -π/2 is returned
// if the argument is NaN, NaN is returned

START_TEST(atan_test_1) {
    double x = RandomReal(-1e10, 1e10);

    ck_assert_ldouble_eq_tol(s21_atan(x), atan(x), 1e-6);
}
END_TEST

Suite *suite_s21_atan(void) {
    Suite *s = suite_create("suite_s21_atan");
    TCase *tc = tcase_create("s21_add_tc");

    // tcase_add_test(tc, );
    tcase_add_loop_test(tc, atan_test_1, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
