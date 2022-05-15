#include "s21_math_test.h"

START_TEST(sqrt_test_1) {
    double x = RandomReal(DBL_MIN, DBL_MAX);

    if (x < 0) {
        ck_assert_ldouble_nan(s21_sqrt(x));
        ck_assert_ldouble_nan(sqrt(x));
    } else {
        ck_assert_double_eq_tol(s21_sqrt(x), sqrt(x), 1e-06);
    }
}
END_TEST

Suite *suite_s21_sqrt(void) {
    Suite *s = suite_create("s21_sqrt");
    TCase *tc = tcase_create("s21_sqrt_tc");

    tcase_add_loop_test(tc, sqrt_test_1, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}
