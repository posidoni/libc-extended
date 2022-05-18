#include "s21_math_test.h"

START_TEST(asin_test_1_rand) {
    double x = RandomReal(-1, 1);

    if (s21_ldeq(x, 0.0)) {
        ck_assert_ldouble_eq_tol(s21_asin(x), 0.0, EPS);
        ck_assert_ldouble_eq_tol(asin(x), 0.0, EPS);
    } else if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_asin(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(asin(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_asin(x), asin(x), EPS);
    }
}
END_TEST

START_TEST(asin_test_2_rand) {
    double x = RandomReal(1e-5, 2);

    if (s21_ldeq(x, 0.0)) {
        ck_assert_ldouble_eq_tol(s21_asin(x), 0.0, EPS);
        ck_assert_ldouble_eq_tol(asin(x), 0.0, EPS);
    } else if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_asin(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(asin(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_asin(x), asin(x), EPS);
    }
}
END_TEST

START_TEST(asin_test_3_rand) {
    double x = RandomReal(0.1, 0.9);

    if (s21_ldeq(x, 0.0)) {
        ck_assert_ldouble_eq_tol(s21_asin(x), 0.0, EPS);
        ck_assert_ldouble_eq_tol(asin(x), 0.0, EPS);
    } else if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_asin(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(asin(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_asin(x), asin(x), EPS);
    }
}
END_TEST

START_TEST(asin_test_4_rand) {
    double x = RandomReal(-1e-10, 5);

    if (s21_ldeq(x, 0.0)) {
        ck_assert_ldouble_eq_tol(s21_asin(x), 0.0, EPS);
        ck_assert_ldouble_eq_tol(asin(x), 0.0, EPS);
    } else if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_asin(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(asin(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_asin(x), asin(x), EPS);
    }
}
END_TEST

START_TEST(asin_test_5_rand) {
    double x = RandomReal(-0.9, 0.9);

    if (s21_ldeq(x, 0.0)) {
        ck_assert_ldouble_eq_tol(s21_asin(x), 0.0, EPS);
        ck_assert_ldouble_eq_tol(asin(x), 0.0, EPS);
    } else if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_asin(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(asin(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_asin(x), asin(x), EPS);
    }
}
END_TEST

START_TEST(asin_test_2_inf) {
    ck_assert_ldouble_nan(s21_asin(INFINITY));
    ck_assert_ldouble_nan(asin(INFINITY));
    ck_assert_ldouble_nan(s21_asin(-INFINITY));
    ck_assert_ldouble_nan(asin(-INFINITY));
}
END_TEST

START_TEST(asin_test_3_nan) {
    ck_assert_ldouble_nan(s21_asin(NAN));
    ck_assert_ldouble_nan(asin(NAN));
}
END_TEST

START_TEST(asin_test_4_one) {
    ck_assert_ldouble_eq_tol(s21_asin(1.0), asin(1.0), EPS);
    ck_assert_ldouble_eq_tol(s21_asin(-1.0), asin(-1.0), EPS);
}
END_TEST

START_TEST(asin_test_5_zero) {
    ck_assert_ldouble_eq_tol(s21_asin(0.0), asin(0.0), EPS);
    ck_assert_ldouble_eq_tol(s21_asin(-0.0), asin(-0.0), EPS);
}
END_TEST

Suite *suite_s21_asin(void) {
    Suite *s = suite_create("suite_s21_asin");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_loop_test(tc, asin_test_1_rand, 0, 100);
    tcase_add_loop_test(tc, asin_test_2_rand, 0, 100);
    tcase_add_loop_test(tc, asin_test_3_rand, 0, 100);
    tcase_add_loop_test(tc, asin_test_4_rand, 0, 100);
    tcase_add_loop_test(tc, asin_test_5_rand, 0, 300);
    tcase_add_test(tc, asin_test_2_inf);
    tcase_add_test(tc, asin_test_3_nan);
    tcase_add_test(tc, asin_test_4_one);
    tcase_add_test(tc, asin_test_5_zero);

    suite_add_tcase(s, tc);
    return s;
}
