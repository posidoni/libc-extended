#include "s21_math_test.h"

START_TEST(sin_test_1) {
    double x = RandomReal(-1e10, 1e10);
    ck_assert_double_eq_tol(s21_sin(x), sin(x), 1e-06);
}
END_TEST

Suite *suite_s21_sin(void) {
    Suite *s = suite_create("suite_s21_add");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_loop_test(tc, sin_test_1, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}