#include "../s21_decimal_test.h"

START_TEST(gcc_128_bits) {
    long long long_a = get_random_ll();
    long long long_b = get_random_ll();

    if (rand() % 2)
        long_a *= -1;

    if (rand() % 2)
        long_b *= -1;

#ifdef DEBUG
    printf("long_a  =%lld\n", long_a);
    printf("long_b  =%lld\n", long_b);
#endif

    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t mul = a * b;

    s21_decimal res128 = bigint_to_decimal(mul);

    s21_decimal dec_a = ll_to_decimal(long_a);
    s21_decimal dec_b = ll_to_decimal(long_b);

    s21_decimal dec_mul = {0};

    s21_mul(dec_a, dec_b, &dec_mul);

#ifdef DEBUG
    printf("dec_a=");
    print_bits_r(dec_a);

    printf("dec_b=");
    print_bits_r(dec_a);

    printf("dec_mul=");
    print_bits_r(dec_mul);
    printf("res128_=");
    print_bits_r(res128);
#endif
    // print_python(res128);
    // print_python(dec_mul);
    ck_assert_int_eq(s21_is_equal(res128, dec_mul), TRUE);
}

// START_TEST(simple_test) {
//     s21_decimal a = {0};
//     s21_decimal b = {0};

//     set_bit_1(&b, 95);
//     set_bit_1(&a, 32);

//     print_bits_r(a);
//     print_bits_r(b);
//     s21_decimal res = {0};
//     s21_mul(a, b, &res);
//     print_bits_r(res);
// }
// END_TEST

START_TEST(random_float) {
    float float_a = get_random_float(-85818.51851, 85818.51851);

    float float_b = get_random_float(-85818.51851, 85818.51851);

    if (rand() % 2)
        float_a *= -1;

    if (rand() % 2)
        float_b *= -1;

    float float_res = float_a * float_b;
#ifdef DEBUG
    printf("float_a = %f\n", float_a);
    printf("float_b = %f\n", float_b);
    printf("float_mul = %f\n", float_res);
#endif

    s21_decimal expected = {0};
    s21_from_float_to_decimal(float_res, &expected);

    s21_decimal dec_a = {0};
    s21_from_float_to_decimal(float_a, &dec_a);
    s21_decimal dec_b = {0};
    s21_from_float_to_decimal(float_b, &dec_b);

    s21_decimal result = {0};

    /* Always INF */
    int code = s21_mul(dec_a, dec_b, &result);

    float expected_float = 0;
    s21_from_decimal_to_float(result, &expected_float);

#ifdef DEBUG
    printf("expctd_flt= %f\n", expected_float);
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
    ck_assert_float_eq_tol(expected_float, float_res, 1e-06);
}

Suite *suite_s21_mul(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_mult"));
    TCase *tc = tcase_create("s21_mul_tc");

    /* tcase_add_test(tc, simple_test); */
    tcase_add_loop_test(tc, gcc_128_bits, 0, 1000);
    tcase_add_loop_test(tc, random_float, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}
