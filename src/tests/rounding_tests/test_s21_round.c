#include "../s21_decimal_test.h"

START_TEST(gcc_128_bits) {
    /* get random value */
    __int128_t a = llabs(get_random_ll() * rand());

    /* discard fraction */
    int exp = get_rand(3, 10);
    __int128_t b = int128_pow(10, exp);
    __int128_t rounded = a / b;

    /* round */
    rounded = int128_round(rounded);

    /*  return it with zeroes*/
    rounded = rounded * b;

    /* get expected */
    s21_decimal expected = bigint_to_decimal(rounded);
    set_exponent(&expected, exp);

    s21_decimal val = bigint_to_decimal(a);
    set_exponent(&val, exp);
    s21_decimal got = {0};
    int ret = s21_round(val, &got);

    ck_assert_int_eq(s21_is_equal(expected, got), 0);
    ck_assert_int_eq(ret, CONVERTATION_OK);
}
END_TEST

Suite *suite_s21_round(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_round"));
    TCase *tc = tcase_create("s21_round_tc");

    tcase_add_loop_test(tc, gcc_128_bits, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}
