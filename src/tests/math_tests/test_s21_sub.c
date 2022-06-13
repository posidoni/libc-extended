#include "../s21_decimal_test.h"

/* START_TEST(sub_loop) { */
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
/*     get_random_pair(&val2, &mpz_val2, 1); */
/*     s21_decimal res = {0}; */

/* #define DEBUG */
/* #ifdef DEBUG */
/*     printf("val1 = "); */
/*     print_bits_r(val1); */
/*     printf("val2 = "); */
/*     print_bits_r(val2); */
/*     printf("mpz_val1 = "); */
/*     print_bits_r(convert_gmp_to_decimal(mpz_val1)); */
/*     printf("mpz_val2 = "); */
/*     print_bits_r(convert_gmp_to_decimal(mpz_val2)); */
/* #endif */

/*     /1* NOTE: GMP library works incorrectly or other functioned needed *1/ */
/*     mpz_sub(mpz_res, mpz_val1, mpz_val2); */
/*     s21_sub(val1, val2, &res); */

/* #ifdef DEBUG */
/*     puts("-------------RESULT----------------"); */
/*     printf("mpz_res = "); */
/*     print_bits_r(convert_gmp_to_decimal(mpz_res)); */
/*     printf("res = "); */
/*     print_bits_r(res); */
/*     puts("-------------RESULT----------------"); */
/* #endif */

/*     /1* NOTE: sub works fine compare to online calc, mpz doesn't work (maybe
 * it */
/*      * doesn't know we have an unsigned value) *1/ */
/*     ck_assert_int_eq(s21_is_equal(res, convert_gmp_to_decimal(mpz_res)),
 * TRUE); */
/* } */
/* END_TEST */

/* START_TEST(sub_test1) { */
/*     // */
/*     s21_decimal v1, v2, sub; */

/*     init_zero(&v1); */
/*     init_zero(&v2); */
/*     // for (int i = 0; i < 96; ++i) set_bit_1(&v1, i); */
/*     // set_bit_0(&v1, 92); */
/*     // set_bit_0(&v1, 93); */
/*     // set_bit_0(&v1, 94); */
/*     // set_bit_0(&v1, 95); */
/*     // for (int i = 0; i < 33; ++i) */
/*     // if (rand() % 2) set_bit_1(&v2, i); */

/*     s21_from_int_to_decimal(12, &v1); */
/*     s21_from_int_to_decimal(1, &v2); */

/*     set_exponent(&v1, 0); */
/*     set_exponent(&v2, 0); */
/*     int code = s21_sub(v1, v2, &sub); */

/*     printf("\nNUMBERS:\n"); */
/*     printf("EXP = %d ", get_exponent(v1)); */
/*     print_bits_r(v1); */
/*     printf("EXP = %d ", get_exponent(v2)); */
/*     print_bits_r(v2); */
/*     printf("EXP = %d ", get_exponent(sub)); */
/*     print_bits_r(sub); */
/*     printf("\n"); */

/*     printf("ERR : %d\n", code); */
/*     // ck_assert_int_eq(get_bit(sub, 1), 1); */
/*     // ck_assert_int_eq(1, 0); */
/* } */
/* END_TEST */

/* START_TEST(sub_test2) { */
/*     // */
/*     s21_decimal v1, v2, sub; */

/*     init_zero(&v1); */
/*     init_zero(&v2); */
/*     for (int i = 0; i < 96; ++i) */
/*         set_bit_1(&v1, i); */
/*     set_bit_0(&v1, 92); */
/*     set_bit_0(&v1, 93); */
/*     set_bit_0(&v1, 94); */
/*     set_bit_0(&v1, 95); */
/*     // for (int i = 0; i < 33; ++i) */
/*     // if (rand() % 2) set_bit_1(&v2, i); */

/*     // s21_from_int_to_decimal(1, &v1); */
/*     s21_from_int_to_decimal(1, &v2); */

/*     set_exponent(&v1, 0); */
/*     set_exponent(&v2, 1); */
/*     int code = s21_sub(v1, v2, &sub); */

/*     printf("\nNUMBERS:\n"); */
/*     printf("EXP = %d ", get_exponent(v1)); */
/*     print_bits_r(v1); */
/*     printf("EXP = %d ", get_exponent(v2)); */
/*     print_bits_r(v2); */
/*     printf("EXP = %d ", get_exponent(sub)); */
/*     print_bits_r(sub); */
/*     printf("\n"); */

/*     printf("ERR : %d\n", code); */
/*     // ck_assert_int_eq(get_bit(sub, 1), 1); */
/*     // ck_assert_int_eq(1, 0); */
/* } */
/* END_TEST */

START_TEST(gcc_128_bits) {
    long long long_a = -1;
    long long long_b = 0;

    while (long_a < long_b) {
        long_a = get_random_ll() * rand();
        long_b = get_random_ll() * rand();
    }

    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t sub = a - b;
    s21_decimal res128 = bigint_to_decimal(sub);

    s21_decimal dec_a = ll_to_decimal(long_a);
    s21_decimal dec_b = ll_to_decimal(long_b);

    printf(RED "1:  " ENDCOLOR);
    print_bits_r(dec_a);
    printf(GRN "2:  " ENDCOLOR);
    print_bits_r(dec_b);

    s21_decimal dec_sub = {0};

    s21_sub(dec_a, dec_b, &dec_sub);

    /* This DOES NOT produce correct result, although it brings res quite close */
    /* dec_sub = bit_not(dec_sub); */

    bool comp_res = s21_is_equal(res128, dec_sub);

    printf("3:  ");
    print_bits_r(dec_sub);
    // printf(GRN "2:  " ENDCOLOR);
    // print_bits_r(res128);

    ck_assert_int_eq(comp_res, TRUE);
}

Suite *suite_s21_sub(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_sub"));
    TCase *tc = tcase_create("s21_sub_tc");

    /* tcase_add_test(tc, sub_test1); */
    /* tcase_add_test(tc, sub_test2); */
    /* tcase_add_loop_test(tc, sub_loop, 0, 1); */
    tcase_add_loop_test(tc, gcc_128_bits, 0, 10);

    suite_add_tcase(s, tc);
    return s;
}
