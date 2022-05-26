#include "s21_math_test.h"

START_TEST(log_test_1_rand) {
    double x = RandomReal(1e-10, 1e+10);

    if (x == 0.0) {
        ck_assert_ldouble_nan(s21_log(x));
        ck_assert_int_eq(errno, ERANGE);
        errno = 0;
        ck_assert_int_eq(errno, ERANGE);
        ck_assert_ldouble_nan(log(x));
    } else if (x < 0.0) {
        ck_assert_ldouble_nan(s21_log(x));
        ck_assert_int_eq(errno, EINVAL);
        errno = 0;
        ck_assert_int_eq(errno, EINVAL);
        ck_assert_ldouble_nan(log(x));
    } else {
        ck_assert_ldouble_eq_tol(s21_log(x), log(x), 1e-6);
    }
}
END_TEST

START_TEST(log_test_2_inf) {
    ck_assert_ldouble_infinite(s21_log(INFINITY));
    ck_assert_ldouble_infinite(log(INFINITY));

    ck_assert_ldouble_nan(s21_log(-INFINITY));
    ck_assert_ldouble_nan(log(-INFINITY));
}
END_TEST

START_TEST(log_test_3_nan) {
    ck_assert_ldouble_nan(s21_log(NAN));
    ck_assert_ldouble_nan(log(NAN));
}
END_TEST

START_TEST(log_test_4_one) {
    ck_assert_ldouble_eq_tol(s21_log(1.0), log(1.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_log(1.1), log(1.1), 1e-6);
}
END_TEST

Suite *
suite_s21_log(void) {
    Suite *s = suite_create("s21_log");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_loop_test(tc, log_test_1_rand, 0, 1000);
    tcase_add_test(tc, log_test_2_inf);
    tcase_add_test(tc, log_test_3_nan);
    tcase_add_test(tc, log_test_4_one);
    /* Commented out because of cpplint */
    // tcase_add_test(tc, log_test_5_zero);

    suite_add_tcase(s, tc);
    return s;
}
