#include "s21_math_test.h"

START_TEST(abs_test_1) {
    int n = -110;
	int a = s21_abs(n);
	int b = abs(n);
    ck_assert_int_eq(a, b);
}
END_TEST

Suite *suite_s21_abs(void) {
    Suite *s = suite_create("suite_s21_add");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_test(tc, abs_test_1);

    suite_add_tcase(s, tc);
    return s;
}
