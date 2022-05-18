#include "s21_math_test.h"

START_TEST(fmod_loop_test) {
    double x = fRand(-1e11 + 1, 1e11 - 1);
    if (rand() % 2)
        x = -x;
    double y = fRand(-1e11 + 1, 1e11 - 1);
    if (rand() % 3)
        y = -y;

    ck_assert_ldouble_eq(s21_fmod(x, y), fmod(x, y));
}
END_TEST

START_TEST(test_inf) {
    ck_assert_ldouble_nan(s21_fmod(INFINITY, INFINITY));
    ck_assert_ldouble_nan(fmod(INFINITY, INFINITY));
}
END_TEST

START_TEST(test_nan) {
    ck_assert_ldouble_nan(s21_fmod(NAN, NAN));
    ck_assert_ldouble_nan(fmod(NAN, NAN));
}
END_TEST

START_TEST(test_y_zero) {
    ck_assert_ldouble_nan(s21_fmod(2.45, 0));
    ck_assert_ldouble_nan(fmod(2.45, 0));
}
END_TEST

START_TEST(test_x_zero) {
    ck_assert_ldouble_nan(s21_fmod(0, 0));
    ck_assert_ldouble_nan(fmod(0, 0));
}
END_TEST

START_TEST(test_x_inf_y_zero) {
    ck_assert_ldouble_nan(s21_fmod(INFINITY, 0));
    ck_assert_ldouble_nan(fmod(INFINITY, 0));
}
END_TEST
Suite *suite_s21_fmod(void) {
    Suite *s = suite_create("s21_fmod");
    TCase *tc = tcase_create("s21_fmod_tc");

    tcase_add_loop_test(tc, fmod_loop_test, 0, 10000);
    tcase_add_test(tc, test_inf);
    tcase_add_test(tc, test_nan);
    tcase_add_test(tc, test_y_zero);
    tcase_add_test(tc, test_x_zero);
    tcase_add_test(tc, test_x_inf_y_zero);

    suite_add_tcase(s, tc);
    return s;
}
