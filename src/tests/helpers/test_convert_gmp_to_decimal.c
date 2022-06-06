#include "../s21_decimal_test.h"

START_TEST(convert_test) {
    s21_decimal expected = {0};
    mpz_t mpz_val;
    mpz_init(mpz_val);
    mpz_set_ui(mpz_val, 0);

    get_random_pair(&expected, &mpz_val, 3);
    tmp_normalize_exponent(&expected);

    s21_decimal got = convert_gmp_to_decimal(mpz_val);
    mpz_clear(mpz_val);

    ck_assert_int_eq(s21_is_equal(got, expected), true);
}
END_TEST

Suite *suite_convert_gmp_to_decimal(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_convert_gmp_to_decimal"));
    TCase *tc = tcase_create("s21_convert_gmp_to_decimal");

    tcase_add_loop_test(tc, convert_test, 0, 30);

    suite_add_tcase(s, tc);
    return s;
}
