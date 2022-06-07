#include "../../s21_decimal_test.h"

START_TEST(convert_test) {
    s21_decimal dec = {0};

    mpz_t got, expected;
    mpz_init_set_ui(got, 0);
    mpz_init_set_ui(expected, 0);

    get_random_pair(&dec, &expected, 3);
    convert_decimal_to_gmp(&got, &dec);

    int result = mpz_cmp(got, expected);

    /* This is done to avoid memory leaks in case of failed test */
    if (!result) {
        ck_assert_int_eq(result, 0);
        mpz_clear(got);
        mpz_clear(expected);
    } else {
        mpz_clear(got);
        mpz_clear(expected);
        /* Fail only after memory cleanup */
        ck_assert_int_eq(0, 1);
    }
}
END_TEST

Suite *suite_convert_decimal_to_gmp(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_convert_decimal_to_gmp"));
    TCase *tc = tcase_create("s21_convert_decimal_to_gmp");

    tcase_add_loop_test(tc, convert_test, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}
