#include "../s21_decimal_test.h"


START_TEST(no_exp_decimals_to_int) {
    int got = rand();
    int expected;

    s21_decimal input = get_random_int_decimal();
    expected = reverse_bits(input.bits[0]);
    int code = s21_from_decimal_to_int(input, &got);
    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_int_eq(got, expected);
}
END_TEST;

START_TEST(exp_decimals_to_int_hardcoded1) {
    int got1 = 1;

    s21_decimal a1 = {0};

    /* All bit values are reversed (!) */
    /* https://onlinestringtools.com/split-string */
    a1.bits[0] = 0b00011111111110111011011010100011; /* Dec: 3312312.312 */
    set_exponent(&a1, 3);

    int code = s21_from_decimal_to_int(a1, &got1);
    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_int_eq(got1, 3312312);
}
END_TEST;

START_TEST(exp_decimals_to_int_hardcoded2) {
    int got2 = 2;
    s21_decimal a2 = {0};

    a2.bits[0] =
        0b11001100011100011100011100011010; /* Dec: 8.8888888888888888888888883
                                             */
    a2.bits[1] = 0b00101111011101110001111001001010;
    a2.bits[2] = 0b00101111011000011001001000000000;
    set_exponent(&a2, 25);

    int code = s21_from_decimal_to_int(a2, &got2);
    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_int_eq(got2, 8);
}
END_TEST;

START_TEST(exp_decimals_to_int_hardcoded3) {
    int got3 = 3;
    s21_decimal a3 = {0};

    a3.bits[0] = 0b11001101110011100000000000000000; /* Dec: 123123123.123123 */
    a3.bits[1] = 0b00010000001101011010111111111011; /* Dec: 555 */
    set_exponent(&a3, 6);
    int code = s21_from_decimal_to_int(a3, &got3);
    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_int_eq(got3, 123123123);
}
END_TEST;

START_TEST(exp_decimals_to_int_gmp) {
    int got = 1;
    s21_decimal in = {0};
    mpz_t in_mpz_copy;
    mpz_init(in_mpz_copy);
    bool flag = get_random_pair(&in, &in_mpz_copy, 3);

    if (!flag) {
        int expected = 13333333;
        expected = mpz_get_si(in_mpz_copy);
        mpz_clear(in_mpz_copy);

        int code = s21_from_decimal_to_int(in, &got);

        ck_assert_int_eq(code, ARITHMETIC_OK);
        ck_assert_int_eq(got, expected);
    } else {
        mpz_clear(in_mpz_copy);
    }
}
END_TEST;

Suite *suite_s21_from_decimal_to_int(void) {
    Suite *s = suite_create("suite_s21_from_decimal_to_int");
    TCase *tc = tcase_create("s21_from_decimal_to_int_tc");

    /* Quite often decimals with exponent are converted to 0 */
    /* This is correct, as we may have no integer part (only fractional) */
    tcase_add_loop_test(tc, no_exp_decimals_to_int, 0, 100);
    tcase_add_loop_test(tc, exp_decimals_to_int_gmp, 0, 5);
    tcase_add_test(tc, exp_decimals_to_int_hardcoded1);
    tcase_add_test(tc, exp_decimals_to_int_hardcoded2);
    tcase_add_test(tc, exp_decimals_to_int_hardcoded3);

    suite_add_tcase(s, tc);
    return s;
}
