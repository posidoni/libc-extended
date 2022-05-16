#include "s21_math_test.h"

START_TEST(exp_test_1) {
    double x = RandomReal(-23.0258509299405, 23.0258509299405);
    ck_assert_double_eq_tol(s21_exp(x), expl(x), 1e-06);
}
END_TEST

Suite *suite_s21_exp(void) {
    Suite *s = suite_create("suite_s21_add");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_loop_test(tc, exp_test_1, 0, 100000);

    suite_add_tcase(s, tc);
    return s;
}
