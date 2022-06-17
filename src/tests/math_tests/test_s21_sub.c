#include "../s21_decimal_test.h"
#define DEBUG

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

    s21_decimal dec_sub = {0};

    s21_sub(a, b, &dec_sub);

    bool comp_res = s21_is_equal(dec_sub, short_dec);

    if (!comp_res) {
#ifdef DEBUG
        printf("ERROR\n");
        printf("1: \t");
        print_bits_r(a);
        printf("2: \t");
        print_bits_r(b);
        print_bits_r(dec_sub);
        print_bits_r(short_dec);
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

    s21_decimal dec_sub = {0};

    s21_sub(dec_a, dec_b, &dec_sub);

    bool comp_res = s21_is_equal(res128, dec_sub);

    ck_assert_int_eq(comp_res, TRUE);
}

START_TEST(random_float) {
    float float_a = get_random_float(-934185818.51851, 4914185818.51851);

    float float_b = get_random_float(-85818.51851, 85818.51851);

    if (rand() % 2)
        float_a *= -1;

    if (rand() % 2)
        float_b *= -1;

    float float_res = float_a - float_b;
#ifdef DEBUG
    printf("float_a = %f\n", float_a);
    printf("float_b = %f\n", float_b);
    printf("float_sub = %f\n", float_res);
#endif

    s21_decimal expected = {0};
    s21_from_float_to_decimal(float_res, &expected);

    s21_decimal dec_a = {0};
    s21_from_float_to_decimal(float_a, &dec_a);

    s21_decimal dec_b = {0};
    s21_from_float_to_decimal(float_b, &dec_b);

#ifdef DEBUG
    printf("dec_a =");
    print_bits_r(dec_a);

    printf("dec_b =");
    print_bits_r(dec_b);
#endif

    s21_decimal result = {0};

    /* NOTE: SOMETIMES CODE IS INFINITY FOR UNKNOWN REASON */
    int code = s21_sub(dec_a, dec_b, &result);

    float got = 0;
    s21_from_decimal_to_float(result, &got);

#ifdef DEBUG
    printf("got= %f\n", got);
    printf("BELOW & ABOVE SOME LOSE OF PRECISION IS OK\n");
    printf("------------------------------------------\n");
    printf("result_exp   = %d\n", get_exponent(result));
    printf("result   =");
    print_bits_r(result);
    printf("expected_exp = %d\n", get_exponent(expected));
    printf("expected =");
    print_bits_r(expected);
    printf("------------------------------------------\n");
#endif

    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_float_eq_tol(got, float_res, 1e-06);
}

Suite *suite_s21_sub(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_sub"));
    TCase *tc = tcase_create("s21_sub_tc");

    /* tcase_add_loop_test(tc, random_decimal_exp, 0, 100); */
    /* tcase_add_loop_test(tc, gcc_128_bits, 0, 100); */
    tcase_add_loop_test(tc, random_float, 0, 1);

    suite_add_tcase(s, tc);
    return s;
}
