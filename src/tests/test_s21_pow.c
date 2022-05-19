#include "s21_math_test.h"

START_TEST(basic_test) {
    long double exp = RandomReal(-4, 4) * (rand() % 11 ? 1 : -1);
    long double base = RandomReal(0, 100);
    ck_assert_double_eq_tol(s21_pow(base, exp), pow(base, exp), EPS);
}
END_TEST

START_TEST(base_neg) {
    long double base = -16.161435;
    long double exp = 9;
    ck_assert_double_eq_tol(s21_pow(base, exp), pow(base, exp), EPS);
}
END_TEST

START_TEST(all_neg) {
    long double base = -10.1261;
    long double exp = -0.72;
    ck_assert_double_nan(s21_pow(base, exp));
    ck_assert_double_nan(pow(base, exp));
}
END_TEST

Suite *suite_s21_pow(void) {
    Suite *s = suite_create("suite_s21_pow");
    TCase *tc = tcase_create("s21_pow_tc");

    tcase_add_loop_test(tc, basic_test, -666, 666);
    tcase_add_test(tc, basic_test);
    tcase_add_test(tc, base_neg);
    tcase_add_test(tc, all_neg);

    suite_add_tcase(s, tc);
    return s;
}
