#include "../s21_decimal_test.h"

/* START_TEST(add_test1) { */
/*     mpz_t mpz_val1; */
/*     mpz_init(mpz_val1); */
/*     mpz_set_ui(mpz_val1, 0); */

/*     mpz_t mpz_val2; */
/*     mpz_init(mpz_val2); */
/*     mpz_set_ui(mpz_val2, 0); */

/*     mpz_t mpz_res; */
/*     mpz_init(mpz_res); */
/*     mpz_set_ui(mpz_res, 0); */

/*     s21_decimal val1 = {0}; */
/*     get_random_pair(&val1, &mpz_val1, 2); */
/*     s21_decimal val2 = {0}; */
/*     get_random_pair(&val2, &mpz_val2, 3); */
/*     s21_decimal res = {0}; */

/*     /1* add abs because mpz negative leads to seg fault *1/ */
/* #define DEBUG */
/* #ifdef DEBUG */
/*     printf("EXP = %2d: ", get_exponent(val1)); */
/*     print_bits_r(val1); */
/*     printf("EXP = %2d: ", get_exponent(val2)); */
/*     print_bits_r(val2); */
/*     // printf("mpz_val1:\n"); */
/*     // print_bits_r(convert_gmp_to_decimal(mpz_val1)); */
/*     // printf("mpz_val2:\n"); */
/*     // print_bits_r(convert_gmp_to_decimal(mpz_val2)); */
/* #endif */

/*     /1* NOTE: GMP library works incorrectly or other functioned needed *1/ */
/*     mpz_add(mpz_res, mpz_val1, mpz_val2); */
/*     int code = s21_add(val1, val2, &res); */

/* #ifdef DEBUG */
/*     // printf("%90s", "-------------RESULT----------------\n"); */
/*     // printf("mpz_res:\n"); */
/*     // print_bits_r(convert_gmp_to_decimal(mpz_res)); */
/*     printf("EXP = %2d: ", get_exponent(res)); */
/*     print_bits_r(res); */
/* #endif */
/*     printf("CODE = %d\n", code); */
/*     if (code == 0) { */
/*         ck_assert_int_eq(s21_is_equal(res, convert_gmp_to_decimal(mpz_res)),
 * TRUE); */
/*     } */
/*     printf("\n"); */
/* } */
/* END_TEST */

START_TEST(gcc_128_bits) {
    long long long_a = get_random_ll() * rand();
    long long long_b = get_random_ll() * rand();

    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t sum = a + b;
    s21_decimal res128 = bigint_to_decimal(sum);

    s21_decimal dec_a = ll_to_decimal(long_a);
    s21_decimal dec_b = ll_to_decimal(long_b);
    s21_decimal dec_sum = {0};

    s21_add(dec_a, dec_b, &dec_sum);
    /* print_bits_r(dec_sum); */

    ck_assert_int_eq(s21_is_equal(res128, dec_sum), TRUE);
}

Suite *suite_s21_add(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_add"));
    TCase *tc = tcase_create("s21_add_tc");

    /* tcase_add_loop_test(tc, add_test1, 0, 1); */
    tcase_add_loop_test(tc, gcc_128_bits, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
