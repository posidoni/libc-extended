#include "../s21_decimal_test.h"

START_TEST(random_decimal_exp) {
    long long long_a = get_random_short();
    long long long_b = get_random_short();

    if (rand() % 2) {
        long_a *= -1;
    }

    if (rand() % 2) {
        long_b *= -1;
    }

    long long expected = long_a - long_b;

    s21_decimal a = ll_to_decimal(long_a);
    s21_decimal b = ll_to_decimal(long_b);

    s21_decimal short_dec = {0};

    if (expected < 0) {
        set_sign_neg(&short_dec);
    }

    short_dec.bits[0] = llabs(expected);

    s21_decimal dec_sum = {0};

    s21_sub(a, b, &dec_sum);

    bool comp_res = s21_is_equal(dec_sum, short_dec);

    if (!comp_res) {
#ifdef DEBUG
        printf("ERROR\n");
        printf("1: \t");
        print_bits_r(a);
        printf("2: \t");
        print_bits_r(b);
        // printf("EXPECTED: \t[%d]\n", expected);
        print_bits_r(dec_sum);
        print_bits_r(short_dec);
        // printf("DEC: %d \t SHORT: %d \n", dec_sum.bits[0],
        // short_dec.bits[0]); printf("DEC: %d \t SHORT: %d \n",
        // dec_sum.bits[1], short_dec.bits[1]); printf("DEC: %d \t SHORT: %d
        // \n", dec_sum.bits[2], short_dec.bits[2]);
#endif
    }

    ck_assert_int_eq(comp_res, true);
}
END_TEST

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

    // printf(RED "1:  " ENDCOLOR);
    // print_bits_r(dec_a);
    // printf(GRN "2:  " ENDCOLOR);
    // print_bits_r(dec_b);

    s21_decimal dec_sub = {0};

    s21_sub(dec_a, dec_b, &dec_sub);

    bool comp_res = s21_is_equal(res128, dec_sub);

    // printf("3:  ");
    // print_bits_r(dec_sub);
    // printf(GRN "2:  " ENDCOLOR);
    // print_bits_r(res128);

    ck_assert_int_eq(comp_res, TRUE);
}

Suite *suite_s21_sub(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_sub"));
    TCase *tc = tcase_create("s21_sub_tc");

    tcase_add_loop_test(tc, random_decimal_exp, 0, 1000);
    tcase_add_loop_test(tc, gcc_128_bits, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}
