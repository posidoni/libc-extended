#include "s21_math_test.h"

START_TEST(sqrt_test_1) {
    double x = RandomReal(10e-16, 10e+16);

    if (x < 0) {
        /* CPPLINT doesn't allow this! */
        ck_assert_ldouble_nan(s21_sqrt(x));
        // ck_assert_ldouble_nan(sqrt(x));
    } else {
        ck_assert_ldouble_eq_tol(s21_sqrt(x), sqrtl(x), 1e-06);
    }
}
END_TEST

START_TEST(sqrt_test_2) {
    double x = RandomReal(-10, 10);

    if (x < 0) {
        /* CPPLINT doesn't allow this! */
        ck_assert_ldouble_nan(s21_sqrt(x));
        // ck_assert_ldouble_nan(sqrt(x));
    } else {
        ck_assert_ldouble_eq_tol(s21_sqrt(x), sqrtl(x), 1e-06);
    }
}
END_TEST

START_TEST(sqrt_test_2_inf) {
    ck_assert_ldouble_infinite(s21_sqrt(INFINITY));
    ck_assert_ldouble_infinite(sqrt(INFINITY));
}
END_TEST

START_TEST(sqrt_test_3_nan) {
    ck_assert_ldouble_nan(s21_sqrt(NAN));
    ck_assert_ldouble_nan(sqrt(NAN));
}
END_TEST

START_TEST(sqrt_test_4_one) {
    ck_assert_ldouble_eq_tol(s21_sqrt(1.0), sqrt(1.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(1.1), sqrt(1.1), 1e-6);
}
END_TEST

START_TEST(sqrt_test_5_zero) {
    ck_assert_ldouble_eq_tol(s21_sqrt(0.0), sqrt(0.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(-0.0), sqrt(-0.0), 1e-6);
}
END_TEST

START_TEST(sqrt_test_6_large) {
    ck_assert_ldouble_eq_tol(s21_sqrt(10e+16), sqrt(10e+16), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(1.312e+16), sqrt(1.312e+16), 1e-6);
}
END_TEST

Suite *suite_s21_sqrt(void) {
    Suite *s = suite_create("s21_sqrt");
    TCase *tc = tcase_create("s21_sqrt_tc");

    tcase_add_loop_test(tc, sqrt_test_1, 0, 10000);
    tcase_add_loop_test(tc, sqrt_test_2, 0, 10000);
    tcase_add_test(tc, sqrt_test_2_inf);
    tcase_add_test(tc, sqrt_test_3_nan);
    tcase_add_test(tc, sqrt_test_4_one);
    tcase_add_test(tc, sqrt_test_5_zero);
    tcase_add_test(tc, sqrt_test_6_large);

    suite_add_tcase(s, tc);
    return s;
}
