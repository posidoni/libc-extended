#include "s21_math_test.h"

START_TEST(acos_test_1_rand) {
    double x = RandomReal(-1, 1);

    if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_acos(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(acos(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_acos(x), acos(x), EPS);
    }
}
END_TEST

START_TEST(acos_test_2_rand) {
    double x = RandomReal(-0.9, 1);

    if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_acos(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(acos(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_acos(x), acos(x), EPS);
    }
}
END_TEST

START_TEST(acos_test_3_rand) {
    double x = RandomReal(-1e-6, 1e-6);

    if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_acos(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(acos(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_acos(x), acos(x), EPS);
    }
}
END_TEST

START_TEST(acos_test_4_rand) {
    double x = RandomReal(DBL_MIN, DBL_MAX);

    if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_acos(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(acos(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_acos(x), acos(x), EPS);
    }
}
END_TEST

START_TEST(acos_test_5_rand) {
    double x = RandomReal(-0.9, 0.9);

    if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_acos(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(acos(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_acos(x), acos(x), EPS);
    }
}
END_TEST

START_TEST(acos_test_2_inf) {
    ck_assert_ldouble_nan(s21_acos(NAN));
    ck_assert_ldouble_nan(acos(NAN));
}
END_TEST

START_TEST(acos_test_3_nan) {
    ck_assert_ldouble_nan(s21_acos(NAN));
    ck_assert_ldouble_nan(acos(NAN));
}
END_TEST

START_TEST(acos_test_4_one) {
    ck_assert_ldouble_eq_tol(s21_acos(1.0), acos(1.0), EPS);
    ck_assert_ldouble_eq_tol(s21_acos(-1.0), acos(-1.0), EPS);
}
END_TEST

START_TEST(acos_test_5_zero) {
    ck_assert_ldouble_eq_tol(s21_acos(0.0), acos(0.0), EPS);
    ck_assert_ldouble_eq_tol(s21_acos(-0.0), acos(-0.0), EPS);
}
END_TEST

Suite *suite_s21_acos(void) {
    Suite *s = suite_create("s21_acos");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_loop_test(tc, acos_test_1_rand, 0, 5);
    tcase_add_loop_test(tc, acos_test_2_rand, 0, 100);
    tcase_add_loop_test(tc, acos_test_3_rand, 0, 100);
    tcase_add_loop_test(tc, acos_test_4_rand, 0, 100);
    tcase_add_loop_test(tc, acos_test_5_rand, 0, 100);
    tcase_add_test(tc, acos_test_2_inf);
    tcase_add_test(tc, acos_test_3_nan);
    tcase_add_test(tc, acos_test_4_one);
    tcase_add_test(tc, acos_test_5_zero);

    suite_add_tcase(s, tc);
    return s;
}
