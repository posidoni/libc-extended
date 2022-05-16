#include "s21_math_test.h"

START_TEST(acos_test_1_rand) {
    double x = RandomReal(-1e10, 1e10);

    if (x == 0) {
        ck_assert_ldouble_eq_tol(s21_acos(x), 0.0, 1e-6);
        ck_assert_ldouble_eq_tol(acos(x), 0.0, 1e-6);
    } else if (fabsl(x) > 1.0) {
        /* Errno should be EDOM (error domain error) */
        ck_assert_ldouble_nan(s21_acos(x));
        ck_assert_int_eq(errno, EDOM);
        ck_assert_ldouble_nan(acos(x));
        ck_assert_int_eq(errno, EDOM);
    } else {
        ck_assert_ldouble_eq_tol(s21_acos(x), acos(x), 1e-6);
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
    ck_assert_ldouble_eq_tol(s21_acos(1.0), acos(1.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_acos(-1.0), acos(-1.0), 1e-6);
}
END_TEST

START_TEST(acos_test_5_zero) {
    ck_assert_ldouble_eq_tol(s21_acos(0.0), acos(0.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_acos(-0.0), acos(-0.0), 1e-6);
}
END_TEST

Suite *suite_s21_acos(void) {
    Suite *s = suite_create("suite_s21_acos");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_loop_test(tc, acos_test_1_rand, 0, 10000);
    tcase_add_test(tc, acos_test_2_inf);
    tcase_add_test(tc, acos_test_3_nan);
    tcase_add_test(tc, acos_test_4_one);
    tcase_add_test(tc, acos_test_5_zero);

    suite_add_tcase(s, tc);
    return s;
}
