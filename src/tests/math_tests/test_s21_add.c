#include "../s21_decimal_test.h"

START_TEST(overflow_test) {
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_decimal res = {0};

    set_bit_1(&a, 95);
    set_bit_1(&a, 94);
    set_bit_1(&b, 95);
    set_bit_1(&b, 94);
    int code = s21_add(a, b, &res);

    print_bits_r(a);
    print_bits_r(b);
    print_bits_r(res);
    printf("CODE : %d\n", code);
}
END_TEST

START_TEST(gcc_128_bits) {
    long long long_a = get_random_ll() * rand();
    long long long_b = get_random_ll() * rand();

    long_a = llabs(long_a);
    long_b = llabs(long_b);

    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t sum = a + b;
    s21_decimal res128 = bigint_to_decimal(sum);

    s21_decimal dec_a = ll_to_decimal(long_a);
    s21_decimal dec_b = ll_to_decimal(long_b);
    s21_decimal dec_sum = {0};

#ifdef DEBUG
    printf("1 \t 2 \n");
    print_bits_r(dec_a);
    print_bits_r(dec_b);
#endif

    int code = s21_add(dec_a, dec_b, &dec_sum);

#ifdef DEBUG
    printf("CODE %d \n", code);
#endif

    if (code == ARITHMETIC_OK) {
#ifdef DEBUG
        print_bits_r(res128);
        print_bits_r(dec_sum);
#endif

        ck_assert_int_eq(code, ARITHMETIC_OK);
        ck_assert_int_eq(s21_is_equal(res128, dec_sum), TRUE);
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

    s21_decimal dec_sum = {0};

    s21_add(a, b, &dec_sum);

#ifdef DEBUG
    print_bits_r(dec_sum);
    print_bits_r(short_dec);
    printf("DEC: %u \t SHORT: %u \n", dec_sum.bits[0], short_dec.bits[0]);
    printf("DEC: %u \t SHORT: %u \n", dec_sum.bits[1], short_dec.bits[1]);
    printf("DEC: %u \t SHORT: %u \n", dec_sum.bits[2], short_dec.bits[2]);
    printf("DEC: %u \t SHORT: %u \n", dec_sum.bits[3], short_dec.bits[3]);
#endif

    ck_assert_int_eq(dec_sum.bits[0], short_dec.bits[0]);
}
END_TEST

/* START_TEST(sum_with_arbitrary_exp) { */
/*     s21_decimal a = {{1, 0, 0, 0}}; */
/*     s21_decimal b = get_random_decimal(2, get_rand(1, 20)); */

/*     s21_decimal got = {0}; */

/*     // printf("%d \n", get_exponent(b)); */
/*     // printf("%d \n", get_exponent(b)); */

/*     int code = s21_add(a, b, &got); */

/*     if (code == ARITHMETIC_OK) { */
/*         // */
/*     } */
/* } */
/* END_TEST */

START_TEST(edge_cases) {
    s21_decimal a = {{1, 0, 0, get_rand(0, INT_MAX)}};
    s21_decimal b = get_random_decimal(3, get_rand(1, 20));
    s21_decimal got = {0};
    set_random_sign(&a);
    set_random_sign(&b);
    int code = s21_add(a, b, &got);
    ck_assert_int_eq(code, ARITHMETIC_OK);
}
END_TEST

Suite *suite_s21_add(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_add"));
    TCase *tc = tcase_create("s21_add_tc");

    /* Add works great. Tested with binary calculator */

    tcase_add_loop_test(tc, gcc_128_bits, 0, 100);
    tcase_add_loop_test(tc, random_decimal_exp, 0, 100);
    /* tcase_add_loop_test(tc, sum_with_arbitrary_exp, 0, 10000); */
    tcase_add_loop_test(tc, edge_cases, 0, 10000);
    tcase_add_test(tc, overflow_test);

    suite_add_tcase(s, tc);
    return s;
}
