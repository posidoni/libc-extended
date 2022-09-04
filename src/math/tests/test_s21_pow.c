#include "s21_math_test.h"

START_TEST(basic_test) {
    long double exp = RandomReal(-4, 4) * (rand() % 11 ? 1 : -1);
    long double base = RandomReal(0, 100);
    ck_assert_double_eq_tol(s21_pow(base, exp), pow(base, exp), EPS);
}
END_TEST

START_TEST(base_neg) {
    long double base = -16.161435;
    long double exp = 9;
    ck_assert_double_eq_tol(s21_pow(base, exp), pow(base, exp), EPS);
}
END_TEST

START_TEST(all_neg) {
    long double base = -10.1261;
    long double exp = -0.72;
    ck_assert_double_nan(s21_pow(base, exp));
    ck_assert_double_nan(pow(base, exp));
}
END_TEST

START_TEST(zero_exp_neg) {
    long double base = +0;
    long double exp = -0.33;
    ck_assert_ldouble_infinite(s21_pow(base, exp));
    ck_assert_ldouble_infinite(pow(base, exp));
}
END_TEST

START_TEST(neg_zero_exp_neg) {
    long double base = -0;
    long double exp = -0.33;
    ck_assert_ldouble_infinite(s21_pow(base, exp));
    ck_assert_ldouble_infinite(pow(base, exp));
}
END_TEST

START_TEST(zero_inf) {
    long double base = -0;
    long double exp = S21_INF;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), EPS);
}
END_TEST

START_TEST(zero_int) {
    long double base = +0;
    long double exp = 123;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(neg_zero_int) {
    long double base = -0;
    long double exp = 123;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(neg_zero_inf) {
    long double base = -0;
    long double exp = S21_INF;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(minus_one_inf) {
    long double base = -1;
    long double exp = S21_INF;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(minus_one_nan) {
    long double base = -1;
    long double exp = S21_NAN;
    ck_assert_double_nan(pow(base, exp));
    ck_assert_double_nan(s21_pow(base, exp));
}
END_TEST

START_TEST(nan_zero) {
    long double base = S21_NAN;
    long double exp = 0;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(neg_finite_nan) {
    long double base = -123;
    long double exp = S21_NAN;
    ck_assert_double_nan(s21_pow(base, exp));
    ck_assert_double_nan(pow(base, exp));
}
END_TEST

START_TEST(less_than_one_minus_inf) {
    long double base = 0.5591951;
    long double exp = -S21_INF;
    ck_assert_ldouble_infinite(pow(base, exp));
    ck_assert_ldouble_infinite(s21_pow(base, exp));
}
END_TEST

START_TEST(base_gt_one_minus_inf) {
    long double base = 1.5591951;
    long double exp = -S21_INF;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(base_less_one_plus_inf) {
    long double base = 0.5591951;
    long double exp = S21_INF;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(gt_one_plus_inf) {
    long double base = 1.5591951;
    long double exp = S21_INF;
    ck_assert_ldouble_infinite(s21_pow(base, exp));
    ck_assert_ldouble_infinite(pow(base, exp));
}
END_TEST

START_TEST(minus_inf_neg_odd) {
    long double base = -S21_INF;
    long double exp = -193491;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(minus_inf_neg_int_even) {
    long double base = -S21_INF;
    long double exp = -142;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(m_inf_positive_odd) {
    long double base = -S21_INF;
    long double exp = 141;
    ck_assert_ldouble_infinite(s21_pow(base, exp));
    ck_assert_ldouble_infinite(pow(base, exp));
}
END_TEST

START_TEST(m_inf_positive_even) {
    long double base = -S21_INF;
    long double exp = 142;
    ck_assert_ldouble_infinite(s21_pow(base, exp));
    ck_assert_ldouble_infinite(pow(base, exp));
}
END_TEST

START_TEST(inf_neg) {
    long double base = S21_INF;
    long double exp = -1;
    ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(inf_pos) {
    long double base = S21_INF;
    long double exp = 1;
    ck_assert_ldouble_infinite(s21_pow(base, exp));
    ck_assert_ldouble_infinite(pow(base, exp));
}
END_TEST

Suite *suite_s21_pow(void) {
    Suite *s = suite_create("s21_pow");
    TCase *tc = tcase_create("s21_pow_tc");

    tcase_add_loop_test(tc, basic_test, -666, 666);
    tcase_add_test(tc, basic_test);
    tcase_add_test(tc, base_neg);
    tcase_add_test(tc, all_neg);
    tcase_add_test(tc, m_inf_positive_odd);
    tcase_add_test(tc, inf_pos);
    tcase_add_test(tc, m_inf_positive_even);
    tcase_add_test(tc, inf_neg);
    tcase_add_test(tc, neg_zero_int);
    tcase_add_test(tc, zero_int);
    tcase_add_test(tc, zero_inf);
    tcase_add_test(tc, neg_zero_exp_neg);
    tcase_add_test(tc, neg_finite_nan);
    tcase_add_test(tc, less_than_one_minus_inf);
    tcase_add_test(tc, base_less_one_plus_inf);
    tcase_add_test(tc, minus_inf_neg_odd);
    tcase_add_test(tc, minus_inf_neg_int_even);
    tcase_add_test(tc, base_gt_one_minus_inf);
    tcase_add_test(tc, minus_one_inf);
    tcase_add_test(tc, neg_zero_inf);
    tcase_add_test(tc, gt_one_plus_inf);
    tcase_add_test(tc, zero_exp_neg);
    tcase_add_test(tc, minus_one_nan);
    tcase_add_test(tc, nan_zero);

    suite_add_tcase(s, tc);
    return s;
}
