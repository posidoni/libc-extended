#include "../s21_decimal_test.h"
#define DEBUG

START_TEST(float_to_dec) {
    s21_decimal res = {0};
    float val = 123.456789;
    s21_from_float_to_decimal(val, &res);
#ifdef DEBUG
    printf("res bits=");
    print_bits_r(res);
#endif
}

START_TEST(float_to_dec_gmp) {
    s21_decimal res = {0};
    float val = -573.10111213;
#ifdef DEBUG
    printf("val=%.8f\n", val);
#endif
    s21_from_float_to_decimal(val, &res);

    /* mpf_t mpf_val; */
    /* mpf_init(mpf_val); */
    /* mpf_set_d(mpf_val, val); */

    /*     printf("mpf in decimal="); */
    /*     mpf_out_str(stdout, 10, 6, mpf_val); */
    /*     puts(""); */
    /* TODO: We need an float_decimal_to_mpz & change all signatures to floats
     * in mpz */
    /* mpz_t mpz_res; */
    /* mpz_init(mpz_res); */
    /* convert_decimal_to_gmp(&mpz_res, &res); */

    /* printf("mpf_res(10)="); */
    /* print_mpz_decimal(mpz_res); */

    /* printf("mpf_res(2)="); */
    /* print_mpz_binary(mpz_res); */
#ifdef DEBUG
    printf("res bits=");
    print_bits_r(res);
#endif
    /* s21_decimal todecimal = convert_gmp_to_decimal(mpz_res); */
    /* printf("%d\n", s21_is_equal(todecimal, res)); */

    /* mpf_clear(mpf_val); */
    /* mpz_clear(mpz_res); */
}
END_TEST

Suite *suite_s21_from_float_to_decimal(void) {
    Suite *s = suite_create("suite_s21_from_float_to_decimal");
    TCase *tc = tcase_create("s21_from_float_to_decimal_tc");

    /* tcase_add_test(tc, float_to_dec_gmp); */
    tcase_add_test(tc, float_to_dec);

    suite_add_tcase(s, tc);
    return s;
}
