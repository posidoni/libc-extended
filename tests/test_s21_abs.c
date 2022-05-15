#include "s21_math_test.h"

START_TEST(abs_test_1) { ck_assert_int_eq(s21_abs(0), abs(0)); }
END_TEST

START_TEST(abs_loop_test_1) {
    int n = rand();
    if (rand() % 2)
        n = -n;
    ck_assert_int_eq(s21_abs(n), abs(n));
}
END_TEST

Suite *suite_s21_abs(void) {
    Suite *s = suite_create("s21_abs");
    TCase *tc = tcase_create("suite_s21_abs");

    tcase_add_test(tc, abs_test_1);
    tcase_add_loop_test(tc, abs_loop_test_1, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
