#include "../../s21_decimal_test.h"

START_TEST(loop1) {
    s21_decimal input = {0};

    int got = 0;
    int exp = get_rand(1, 5);
    int expected = get_rand(0, INT32_MAX);

    input.bits[0] = expected;

    if (rand() % 2) {
        expected = -expected;
    }

    set_exponent(&input, exp);


    expected = expected / (pow(10, exp));

    if (expected < 0)
        set_sign_neg(&input);

    int code = s21_from_decimal_to_int(input, &got);

    if (expected > INT_MIN && expected < INT_MAX) {
        ck_assert_int_eq(got, expected);
        ck_assert_int_eq(code, CONVERTATION_OK);
    } else {
        ck_assert_int_eq(code, CONVERTATION_ERROR);
    }
}
END_TEST

Suite *suite_s21_from_decimal_to_int(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_from_decimal_to_int"));
    TCase *tc = tcase_create("s21_from_decimal_to_int_tc");

    tcase_add_loop_test(tc, loop1, 0, 10);

    suite_add_tcase(s, tc);
    return s;
}
