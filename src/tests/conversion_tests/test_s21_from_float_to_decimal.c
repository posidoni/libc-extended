#include "../s21_decimal_test.h"

START_TEST(float_to_dec) {
    s21_decimal res = {0};
    float val = 12345689.10111213;
    s21_from_float_to_decimal(val, &res);

    mpf_t mpf_val;
    mpf_init(mpf_val);
    mpf_set_d(mpf_val, val);

    printf("mpf in decimal =");
    mpf_out_str(stdout, 10, 6, mpf_val);
    puts("");

    mpz_t mpz_res;
    mpz_init(mpz_res);
    convert_decimal_to_gmp(&mpz_res, &res);

    printf("mpf_res =");
    print_mpz_decimal(mpz_res);
    puts("");

    print_bits_r(res);
    mpf_clear(mpf_val);
    mpz_clear(mpz_res);
}
END_TEST

Suite *suite_s21_from_float_to_decimal(void) {
    Suite *s = suite_create("suite_s21_from_float_to_decimal");
    TCase *tc = tcase_create("s21_from_float_to_decimal_tc");

    tcase_add_test(tc, float_to_dec);

    suite_add_tcase(s, tc);
    return s;
}
