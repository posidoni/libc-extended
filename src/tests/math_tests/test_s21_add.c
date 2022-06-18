#include "../s21_decimal_test.h"
#include <math.h>
#include <stdio.h>

START_TEST(overflow_test) {
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_decimal res = {0};

    set_bit_1(&a, 95);
    set_bit_1(&a, 94);
    set_bit_1(&b, 95);
    set_bit_1(&b, 94);
    int code = s21_add(a, b, &res);

    ck_assert_int_eq(code, S21_INFINITY);
}
END_TEST

START_TEST(gcc_128_bits) {
    long long long_a = get_random_ll();
    long long long_b = get_random_ll();

    if (rand() % 2)
        long_a *= -1;

    if (rand() % 2)
        long_b *= -1;


    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t sum = a + b;
    s21_decimal res128 = bigint_to_decimal(sum);

    s21_decimal dec_a = ll_to_decimal(long_a);
    s21_decimal dec_b = ll_to_decimal(long_b);
    s21_decimal dec_sum = {0};

    int code = s21_add(dec_a, dec_b, &dec_sum);

#ifdef DEBUG
    printf("CODE %d \n", code);
#endif

    if (code == ARITHMETIC_OK) {
#ifdef DEBUG
        print_bits_r(res128);
        print_bits_r(dec_sum);
#endif

        int res = s21_is_equal(res128, dec_sum);

        if (res == 0) {
            printf("%lld \n", long_a);
            printf("(+) \n");
            printf("%lld \n", long_b);

            printf("=== (exp, got)\n");
            print_python(res128);
            print_python(dec_sum);
        }

        ck_assert_int_eq(code, ARITHMETIC_OK);
        ck_assert_int_eq(res, TRUE);
    }
}
END_TEST

START_TEST(random_decimal_exp) {
    long long_a = get_random_short();
    long long long_b = get_random_short();

    if (rand() % 2)
        long_a *= -1;

    if (rand() % 2)
        long_b *= -1;

    long long expected = long_a + long_b;

    s21_decimal a = ll_to_decimal(long_a);
    s21_decimal b = ll_to_decimal(long_b);

    s21_decimal short_dec = {0};

    if (expected < 0)
        set_sign_neg(&short_dec);

    short_dec.bits[0] = llabs(expected);

    s21_decimal dec_sum = {0};

    int code = s21_add(a, b, &dec_sum);

    if (!code) {
#ifdef DEBUG
        printf("ERROR\n");
        printf("1: \t");
        print_bits_r(a);
        printf("2: \t");
        print_bits_r(b);
        print_bits_r(dec_sum);
        print_bits_r(short_dec);
#endif
    }
    ck_assert_int_eq(s21_is_equal(dec_sum, short_dec), TRUE);
}
END_TEST

START_TEST(random_float) {
    float float_a = get_random_float(-85818.51851, 85818.51851);

    float float_b = get_random_float(-85818.51851, 85818.51851);

    if (rand() % 2)
        float_a *= -1;

    if (rand() % 2)
        float_b *= -1;

    // float_a = fabsf(float_a);
    // float_b = fabsf(float_b);

    float float_res = float_a + float_b;

    // float_res = fabsf(float_res);

    s21_decimal expected = {0};
    s21_from_float_to_decimal(float_res, &expected);

    s21_decimal dec_a = {0};
    s21_from_float_to_decimal(float_a, &dec_a);
    s21_decimal dec_b = {0};
    s21_from_float_to_decimal(float_b, &dec_b);

    s21_decimal result = {0};
    /* NOTE: SOMETIMES CODE IS INFINITY FOR UNKNOWN REASON */
    int code = s21_add(dec_a, dec_b, &result);

    float got_float = 0;
    s21_from_decimal_to_float(result, &got_float);

    if (got_float - float_res > 1e-6) {
        printf("float_a = %f\n", float_a);
        printf("float_b = %f\n", float_b);
        printf("float_sum (expected) = %f\n", float_res);
        printf("GOT: = %f\n", got_float);
    }

    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_float_eq_tol(got_float, float_res, 1e-6);
}


START_TEST(target_float) {
    float float_a = 85686.007812;
    float float_b = -81643.296875;

// float_a = 85686.007812
// float_b = -81643.296875
    // if (rand() % 2)
    //     float_a *= -1;

    // if (rand() % 2)
    //     float_b *= -1;

    // float_a = fabsf(float_a);
    // float_b = fabsf(float_b);

    float float_res = float_a + float_b;

    // float_res = fabsf(float_res);

#define  DEBUG
#ifdef DEBUG
    printf("float_a = %f\n", float_a);
    printf("float_b = %f\n", float_b);
    printf("float_sum (expected) = %f\n", float_res);
#endif

    s21_decimal expected = {0};
    s21_from_float_to_decimal(float_res, &expected);

    s21_decimal dec_a = {0};
    s21_from_float_to_decimal(float_a, &dec_a);
    s21_decimal dec_b = {0};
    s21_from_float_to_decimal(float_b, &dec_b);

    s21_decimal result = {0};
    /* NOTE: SOMETIMES CODE IS INFINITY FOR UNKNOWN REASON */
    int code = s21_add(dec_a, dec_b, &result);

    float got_float = 0;
    s21_from_decimal_to_float(result, &got_float);

#ifdef DEBUG
    printf("GOT_FLOAT (got dec -> got float)= %f\n", got_float);
    printf("BELOW & ABOVE SOME LOSE OF PRECISION IS OK\n");
    printf("------------------------------------------\n");
    printf("result_exp   = %d\n", get_exponent(result));
    printf("result   =");
    print_bits_r(result);
    printf("expected_exp = %d\n", get_exponent(expected));
    printf("expected =");
    s21_decimal tmp = {0};
    s21_decimal t = get_power_of_ten(get_exponent(expected));
    set_sign_pos(&expected);
    set_exponent(&expected, 0);
    s21_integer_div(expected, t, &tmp);
    print_bits_r(tmp);
    printf("------------------------------------------\n");
#endif

    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_float_eq_tol(got_float, float_res, 1e-06);
}

Suite *suite_s21_add(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_add"));
    TCase *tc = tcase_create("s21_add_tc");

    // TODO:
    // 1. compare with existing sub tests
    // 2. see if the early xoring is needed (probably NO, due to not negating 1 as in sub binary algo)
    // 3. hardcode very large numbers (decimal has 28 signs -> make up valid sums with that large numbers in binary calculator)

    tcase_add_loop_test(tc, random_float, 0, 1);
    // tcase_add_loop_test(tc, target_float, 0, 1);
    tcase_add_loop_test(tc, gcc_128_bits, 0, 5000);
    // tcase_add_loop_test(tc, random_decimal_exp, 0, 100);
    // tcase_add_test(tc, overflow_test);

    suite_add_tcase(s, tc);
    return s;
}
