#include "s21_math_test.h"


START_TEST(basic_test) {
    long double base;
    long double exp;
    for (int i = -666; i < 666; i++) {
        base = ((double)rand()/(double)RAND_MAX);
        exp = ((double)rand()/(double)RAND_MAX) * (rand() % 11 ? 1 : -1);
        ck_assert_double_eq_tol(s21_pow(base, exp), pow(base, exp), EPS);
    }
} END_TEST

START_TEST(base_niga) {
    long double base = -16.161435;
    long double exp = 11;
    ck_assert_double_nan(s21_pow(base, exp));
} END_TEST

START_TEST(all_niga) {
    long double base = -10.1261;
    long double exp = -0.72;
    ck_assert_double_nan(s21_pow(base, exp));
} END_TEST

Suite *suite_s21_pow(void) {
    Suite *s = suite_create("suite_s21_pow");
    TCase *tc = tcase_create("s21_add_tc");

     tcase_add_test(tc, basic_test);
     tcase_add_test(tc, base_niga);
     tcase_add_test(tc, all_niga);

    suite_add_tcase(s, tc);
    return s;
}
