#include "../s21_decimal_test.h"

/* START_TEST(mul_loop) { */
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
/*     get_random_pair(&val1, &mpz_val1, 1); */
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

/* NOTE: GMP library works incorrectly or other functioned needed */
/* mpz_mul(mpz_res, mpz_val1, mpz_val2); */
/* s21_mul(val1, val2, &res); */

/* #ifdef DEBUG */
/* puts("-------------RESULT----------------"); */
/* printf("mpz_res = "); */
/* print_bits_r(convert_gmp_to_decimal(mpz_res)); */
/* printf("res = "); */
/* print_bits_r(res); */
/* puts("-------------RESULT----------------"); */
/* #endif */

/* ck_assert_int_eq(s21_is_equal(res, convert_gmp_to_decimal(mpz_res)), TRUE);
 */
/* } */
/* END_TEST */

// START_TEST(gcc_128_bits) {
//     long long long_a = get_random_ll() * rand();
//     long long long_b = get_random_ll() * rand();

// #define DEBUG // #ifdef DEBUG
//     printf("long_a  =%lld\n", long_a);
//     printf("long_b  =%lld\n", long_b);
// #endif

//     __int128_t a = long_a;
//     __int128_t b = long_b;
//     __int128_t mul = a * b;

//     s21_decimal res128 = bigint_to_decimal(mul);

//     // s21_decimal dec_a = ll_to_decimal(long_a);
//     // s21_decimal dec_b = ll_to_decimal(long_b);

//     s21_decimal dec_a = {0};
//     s21_decimal dec_b = {0};
//     s21_decimal dec_mul = {0};

//     dec_a.bits[0] = 3;
//     dec_a.bits[1] = 3;
//     dec_a.bits[2] = 3;

//     s21_mul(dec_a, dec_b, &dec_mul);

// #ifdef DEBUG
//     printf("dec_a=");
//     print_bits_r(dec_a);

//     printf("dec_b=");
//     print_bits_r(dec_a);
// #endif
// #ifdef DEBUG
//     printf("dec_mul=");
//     print_bits_r(dec_mul);
//     printf("res128_=");
//     print_bits_r(res128);
// #endif

//     ck_assert_int_eq(s21_is_equal(res128, dec_mul), TRUE);
// }

/*START_TEST(simple_test) {
    s21_decimal a = {0};
    s21_decimal b = {0};

    // set_bit_1(&a, 31);
    // set_bit_1(&a, 32);

    set_bit_1(&b, 95);
    // set_bit_1(&b, 32);

    print_bits_r(a);
    print_bits_r(b);
    s21_decimal res = {0};
    s21_mul(a, b, &res);
    print_bits_r(res);
}
END_TEST*/

#define DEBUG
START_TEST(gcc_128_bits) {
    long long long_a = get_random_ll() * (rand() % 222222);
    long long long_b = get_random_ll() * (rand() % 222222);

    long_a = llabs(long_a);
    long_b = llabs(long_b);

    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t mul = a * b;
    s21_decimal res128 = bigint_to_decimal(mul);

    s21_decimal dec_a = ll_to_decimal(long_a);
    s21_decimal dec_b = ll_to_decimal(long_b);
    s21_decimal dec_mul = {0};

    // #ifdef DEBUG
    // printf("1 \t 2 \n");
    // print_bits_r(dec_a);
    // print_bits_r(dec_b);
    // #endif

    int code = s21_mul(dec_a, dec_b, &dec_mul);

    // #ifdef DEBUG
    // printf("CODE %d \n", code);
    // #endif

    if (code == ARITHMETIC_OK) {
        // #ifdef DEBUG
        // print_bits_r(res128);
        // print_bits_r(dec_mul);
        // #endif

        ck_assert_int_eq(code, ARITHMETIC_OK);
        ck_assert_int_eq(s21_is_equal(res128, dec_mul), TRUE);
    }
}
END_TEST

START_TEST(random_decimal_exp) {
    long long long_a = get_random_short();
    long long long_b = get_random_short();

    if (rand() % 2) {
        long_a *= -1;
    }

    if (rand() % 2) {
        long_b *= -1;
    }

    long long expected = long_a + long_b;

    s21_decimal a = ll_to_decimal(long_a);
    s21_decimal b = ll_to_decimal(long_b);

    s21_decimal short_dec = {.bits[0] = expected};

    s21_decimal dec_mul = {0};

    s21_add(a, b, &dec_mul);

    // #ifdef DEBUG
    //     print_bits_r(dec_mul);
    //     print_bits_r(short_dec);
    //     printf("DEC: %u \t SHORT: %u \n", dec_mul.bits[0], short_dec.bits[0]);
    //     printf("DEC: %u \t SHORT: %u \n", dec_mul.bits[1], short_dec.bits[1]);
    //     printf("DEC: %u \t SHORT: %u \n", dec_mul.bits[2], short_dec.bits[2]);
    //     printf("DEC: %u \t SHORT: %u \n", dec_mul.bits[3], short_dec.bits[3]);
    // #endif

    ck_assert_int_eq(abs((int)dec_mul.bits[0]), abs((int)short_dec.bits[0]));
}
END_TEST

Suite *suite_s21_mul(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_mult"));
    TCase *tc = tcase_create("s21_mul_tc");

    /* tcase_add_loop_test(tc, mul_loop, 0, 1); */
    tcase_add_loop_test(tc, gcc_128_bits, 0, 1000);
    tcase_add_loop_test(tc, random_decimal_exp, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}
