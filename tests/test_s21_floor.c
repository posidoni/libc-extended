#include "s21_math_test.h"

START_TEST(floor_loop_test) {
    double n = fRand(DBL_MIN, DBL_MAX);
    if (rand() % 2)
        n = -n;
    ck_assert_ldouble_eq(s21_floor(n), floor(n));
}
END_TEST

START_TEST(test_inf) {
    ck_assert_ldouble_infinite(s21_floor(INFINITY));
    ck_assert_ldouble_infinite(floor(INFINITY));
}
END_TEST

START_TEST(test_nan) {
    ck_assert_ldouble_nan(s21_floor(NAN));
    ck_assert_ldouble_nan(floor(NAN));
}
END_TEST

START_TEST(test_y_zero) { ck_assert_ldouble_eq(s21_floor(0), floor(0)); }
END_TEST

START_TEST(test_x_inf_y_zero) {
    double x = 87435174713754713577135713757.4134143134134134;
    ck_assert_ldouble_eq(s21_floor(x), floor(x));
}

Suite *suite_s21_floor(void) {
    Suite *s = suite_create("s21_floor");
    TCase *tc = tcase_create("s21_floor_tc");

    tcase_add_loop_test(tc, floor_loop_test, 0, 10000);
    tcase_add_test(tc, test_inf);
    tcase_add_test(tc, test_nan);
    tcase_add_test(tc, test_y_zero);
    tcase_add_test(tc, test_x_inf_y_zero);

    suite_add_tcase(s, tc);
    return s;
}
