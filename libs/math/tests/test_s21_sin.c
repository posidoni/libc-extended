#include "s21_math_test.h"

START_TEST(sin_test_1) {
    double x = RandomReal(-1e10, 1e10);
    ck_assert_double_eq_tol(s21_sin(x), sinl(x), 1e-06);
}
END_TEST

START_TEST(sin_0) {
    double x = 0;
    ck_assert_double_eq_tol(s21_sin(x), sinl(x), 1e-06);
}
END_TEST

START_TEST(sin_minf) {
    ck_assert_ldouble_nan(s21_sin(-INFINITY));
    ck_assert_ldouble_nan(sinl(-INFINITY));
}
END_TEST

START_TEST(sin_inf) {
    ck_assert_ldouble_nan(s21_sin(INFINITY));
    ck_assert_ldouble_nan(sinl(INFINITY));
}
END_TEST

START_TEST(sin_nan) {
    ck_assert_ldouble_nan(s21_sin(NAN));
    ck_assert_ldouble_nan(sinl(NAN));
}
END_TEST

Suite *suite_s21_sin(void) {
    Suite *s = suite_create("s21_sin");
    TCase *tc = tcase_create("s21_sin_tc");

    tcase_add_loop_test(tc, sin_test_1, 0, 10000);
    tcase_add_test(tc, sin_0);
    tcase_add_test(tc, sin_minf);
    tcase_add_test(tc, sin_inf);
    tcase_add_test(tc, sin_nan);
    suite_add_tcase(s, tc);
    return s;
}
