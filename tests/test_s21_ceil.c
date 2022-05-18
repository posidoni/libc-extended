#include "s21_math_test.h"

START_TEST(ceil_loop_test) {
    double n = fRand(DBL_MIN, DBL_MAX);
    if (rand() % 2)
        n = -n;
    ck_assert_ldouble_eq(s21_ceil(n), ceil(n));
}
END_TEST

START_TEST(test_inf) {
    ck_assert_ldouble_infinite(s21_ceil(INFINITY));
    ck_assert_ldouble_infinite(ceil(INFINITY));
}
END_TEST

START_TEST(test_nan) {
    ck_assert_ldouble_nan(s21_ceil(NAN));
    ck_assert_ldouble_nan(ceil(NAN));
}
END_TEST

START_TEST(test_y_zero) { ck_assert_ldouble_eq(s21_ceil(0), ceil(0)); }
END_TEST

START_TEST(test_x_inf_y_zero) {
    double x = 87435174713754713577135713757.4134143134134134;
    ck_assert_ldouble_eq(s21_ceil(x), ceil(x));
}

Suite *suite_s21_ceil(void) {
    Suite *s = suite_create("s21_ceil");
    TCase *tc = tcase_create("s21_ceil_tc");

    tcase_add_test(tc, test_inf);
    tcase_add_test(tc, test_nan);
    tcase_add_test(tc, test_y_zero);
    tcase_add_test(tc, test_x_inf_y_zero);
    tcase_add_loop_test(tc, ceil_loop_test, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
