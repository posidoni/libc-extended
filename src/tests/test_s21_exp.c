#include "s21_math_test.h"

START_TEST(exp_test_1) {
    double x = RandomReal(-23.0258509299405, 23.0258509299405);
    ck_assert_ldouble_eq_tol(s21_exp(x), expl(x), 1e-06);
}
END_TEST

START_TEST(exp_0) {
    double x = 0;
    ck_assert_ldouble_eq_tol(s21_exp(x), expl(x), 1e-06);
}
END_TEST

START_TEST(exp_minf) { ck_assert_ldouble_eq_tol(s21_exp(-INFINITY), expl(-INFINITY), 1e-06); }
END_TEST

START_TEST(exp_inf) {
    ck_assert_ldouble_infinite(s21_exp(INFINITY));
    ck_assert_ldouble_infinite(expl(INFINITY));
}
END_TEST

START_TEST(exp_nan) {
    ck_assert_ldouble_nan(s21_exp(NAN));
    ck_assert_ldouble_nan(expl(NAN));
}
END_TEST

Suite *suite_s21_exp(void) {
    Suite *s = suite_create("suite_s21_exp");
    TCase *tc = tcase_create("s21_exp_tc");

    tcase_add_loop_test(tc, exp_test_1, 0, 10000);
    tcase_add_test(tc, exp_0);
    tcase_add_test(tc, exp_minf);
    tcase_add_test(tc, exp_inf);
    tcase_add_test(tc, exp_nan);

    suite_add_tcase(s, tc);
    return s;
}
