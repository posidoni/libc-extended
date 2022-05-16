#include "s21_math_test.h"

START_TEST(asin_test_1_rand) {
    double x = RandomReal(-1e10, 1e10);

    if (x == 0) {
        ck_assert_ldouble_eq_tol(s21_asin(x), 0.0, 1e-6);
        ck_assert_ldouble_eq_tol(asin(x), 0.0, 1e-6);
    } else if (fabsl(x) > 1.0 || isnan(x)) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_asin(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(asin(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_asin(x), asin(x), 1e-6);
    }
}
END_TEST

START_TEST(asin_test_2_inf) {
    ck_assert_ldouble_nan(s21_asin(NAN));
    ck_assert_int_eq(errno, EDOM);
    ck_assert_ldouble_nan(asin(NAN));
    ck_assert_int_eq(errno, EDOM);
}
END_TEST

START_TEST(asin_test_3_nan) {
    ck_assert_ldouble_nan(s21_asin(NAN));
    ck_assert_ldouble_nan(asin(NAN));
}
END_TEST

START_TEST(asin_test_4_one) {
    ck_assert_ldouble_eq_tol(s21_asin(1.0), asin(1.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_asin(-1.0), asin(-1.0), 1e-6);
}
END_TEST

Suite *suite_s21_asin(void) {
    Suite *s = suite_create("suite_s21_asin");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_loop_test(tc, asin_test_1_rand, 0, 10000);
    tcase_add_test(tc, asin_test_2_inf);
    tcase_add_test(tc, asin_test_3_nan);
    tcase_add_test(tc, asin_test_4_one);

    suite_add_tcase(s, tc);
    return s;
}
