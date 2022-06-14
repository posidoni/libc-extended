#include "../s21_decimal_test.h"

START_TEST(simple_float) {
    s21_decimal a = {5, 0, 0, 0};
    s21_decimal b = {3, 0, 0, 0};
    s21_decimal c = {0, 0, 0, 0};
    s21_div(a, b, &c);
    // s21_decimal a2 = {5, 0, 0, 0};
    // s21_decimal b2 = {3, 0, 0, 0};
    // s21_decimal c2 = {0, 0, 0, 0};
    // s21_div(a2, b2, &c2);
    // s21_decimal c3 = {0, 0, 0, 0};
    // s21_add(c, c2, &c3);
}
END_TEST

Suite *suite_s21_div(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_div"));
    TCase *tc = tcase_create("s21_div_tc");

    tcase_add_loop_test(tc, simple_float, 0, 1);
    // Expected output:
    // R = 0.333333(3)
    // TODO(capricey): #58 currently float div lacks any logic with exponent.

    suite_add_tcase(s, tc);
    return s;
}
