#include "../s21_decimal_test.h"
#define DEBUG

START_TEST(random_loop) {
    /* get random value */
    float x = get_random_float(-100500.123456, 100500.123456);
    s21_decimal expected = {0};
    s21_from_float_to_decimal(roundf(x), &expected);

    s21_decimal got = {0};
    s21_from_float_to_decimal(x, &got);
    s21_decimal res = {0};
    int ret = s21_round(got, &res);

    ck_assert_int_eq(s21_is_equal(expected, res), TRUE);
    ck_assert_int_eq(ret, CONVERTATION_OK);
}
END_TEST

Suite *suite_s21_round(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_round"));
    TCase *tc = tcase_create("s21_round_tc");

    tcase_add_loop_test(tc, random_loop, 0, 5);

    suite_add_tcase(s, tc);
    return s;
}
