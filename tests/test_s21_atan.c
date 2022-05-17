#include "s21_math_test.h"

START_TEST(atan_test_1_rand) {
    double x = RandomReal(1e-16, 1e+16);

    ck_assert_ldouble_eq_tol(s21_atan(x), atan(x), 1e-6);
}
END_TEST

START_TEST(atan_test_2_inf) {
    ck_assert_ldouble_eq_tol(s21_atan(INFINITY), (M_PI / 2.0), 1e-6);
    ck_assert_ldouble_eq_tol(atan(INFINITY), (M_PI / 2.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_atan((-INFINITY)), ((M_PI) / -2.0), 1e-6);
    ck_assert_ldouble_eq_tol(atan(-INFINITY), ((M_PI) / -2.0), 1e-6);
}
END_TEST

START_TEST(atan_test_3_nan) {
    ck_assert_ldouble_nan(s21_atan(NAN));
    ck_assert_ldouble_nan(atan(NAN));
}
END_TEST

START_TEST(atan_test_4_one) {
    ck_assert_ldouble_eq_tol(s21_atan(1.0), atan(1.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_atan(1.1), atan(1.1), 1e-6);
    ck_assert_ldouble_eq_tol(s21_atan(-1.0), atan(-1.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_atan(-1.1), atan(-1.1), 1e-6);
}
END_TEST

START_TEST(atan_test_5_zero) {
    ck_assert_ldouble_eq_tol(s21_atan(0.0), atan(0.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_atan(-0.0), atan(-0.0), 1e-6);
}
END_TEST

Suite *suite_s21_atan(void) {
    Suite *s = suite_create("suite_s21_atan");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_loop_test(tc, atan_test_1_rand, 0, 10000);
    tcase_add_test(tc, atan_test_2_inf);
    tcase_add_test(tc, atan_test_3_nan);
    tcase_add_test(tc, atan_test_4_one);
    tcase_add_test(tc, atan_test_5_zero);

    suite_add_tcase(s, tc);
    return s;
}