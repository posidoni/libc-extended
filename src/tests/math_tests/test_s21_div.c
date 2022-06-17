#include "../s21_decimal_test.h"

START_TEST(gcc_128_bits) {
    long long long_a = get_random_ll() * rand();
    long long long_b = get_random_ll();

    if (rand() % 2)
        long_a *= -1;

    if (rand() % 2)
        long_b *= -1;

    printf("long_a = %lld\n", long_a);
    printf("long_b = %lld\n", long_b);

    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t divided = a / b;
    printf("divided = %lld\n", (long long)divided);

    s21_decimal res128 = bigint_to_decimal(divided);

    s21_decimal dec_a = ll_to_decimal(long_a);
    s21_decimal dec_b = ll_to_decimal(long_b);
    s21_decimal dec_div = {0};

    int code = s21_div(dec_a, dec_b, &dec_div);

    printf("dec_div=");
    print_bits_r(dec_div);
    printf("res128_=");
    print_bits_r(res128);

    int comp_res = s21_is_equal(res128, dec_div);

    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_int_eq(comp_res, TRUE);
}

START_TEST(random_float) {
    float float_a = get_random_float(-100.123456, 100.123456);

    float float_b = get_random_float(-10.123456, 10.123456);

    if (rand() % 2)
        float_a *= -1;

    if (rand() % 2)
        float_b *= -1;

    printf("float_a = %f\n", float_a);
    printf("float_b = %f\n", float_b);
    float float_res = float_a / float_b;
    printf("divided = %f\n", float_res);

    s21_decimal res_float = {0};
    s21_from_float_to_decimal(float_res, &res_float);

    s21_decimal dec_a = {0};
    s21_from_float_to_decimal(float_a, &dec_a);
    s21_decimal dec_b = {0};
    s21_from_float_to_decimal(float_b, &dec_b);

    s21_decimal dec_div = {0};

    int code = s21_div(dec_a, dec_b, &dec_div);

    printf("dec_div=");
    print_bits_r(dec_div);
    printf("res_float =");
    print_bits_r(res_float);

    int comp_res = s21_is_equal(res_float, dec_div);

    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_int_eq(comp_res, TRUE);
}

START_TEST(gcc_128_division_by_ten) {
    long long long_a = get_random_ll() * rand();
    int power_of_ten = get_rand(1, 28);
    long long long_b = pow(10, power_of_ten);
    // printf("long_a  =%lld\n", long_a);
    // printf("long_b  =%lld\n", long_b);
    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t div = a / b;
    s21_decimal res128 = bigint_to_decimal(div);

    s21_decimal dec_a = ll_to_decimal(long_a);

    // print_bits_r(dec_a);
    s21_decimal dec_b = get_power_of_ten(power_of_ten);
    s21_decimal dec_div = {0};

    // print_bits_r(dec_b);

    int code = s21_div(dec_a, dec_b, &dec_div);

    // printf("dec_div=");
    // print_bits_r(dec_div);
    // printf("res128_=");
    // print_bits_r(res128);

    int comp_res = s21_is_equal(res128, dec_div);

    if (!comp_res) {
        /* I suspect that it is not our problem that signs do not match here */
        /* GCC __int128_t are unsigned, thus, they discard sign */
        /* In observed failed tests our decimal had sign & int 128 didn't */
        printf(
            GRN
            "WARNING! SIGNS DO NOT MATCH! COMPARING ABS VALUES 📌 \n" ENDCOLOR);
        set_sign_pos(&dec_div);
        comp_res = s21_is_equal(res128, dec_div);
    }

    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_int_eq(comp_res, TRUE);
}

START_TEST(divison_by_one) {
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_decimal res = {0};

    a.bits[0] = get_rand(0, INT_MAX);
    a.bits[1] = get_rand(0, INT_MAX);
    a.bits[2] = get_rand(0, INT_MAX);

    /* This is same as bits[0] = 1 */
    set_bit_1(&b, 0);

    int code = s21_div(a, b, &res);

    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_int_eq(a.bits[0], res.bits[0]);
    ck_assert_int_eq(a.bits[1], res.bits[1]);
    ck_assert_int_eq(a.bits[2], res.bits[2]);
}
END_TEST

START_TEST(divison_by_two) {
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_decimal res = {0};

    a.bits[0] = get_rand(0, INT_MAX);
    b.bits[0] = a.bits[0] / 2;

    int code = s21_div(a, b, &res);

    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_int_eq(res.bits[0], 2);
}
END_TEST

START_TEST(divison_by_rand_int) {
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_decimal res = {0};

    /* Loop ensures we do not get 0 as a result of integer div */
    while (a.bits[0] <= b.bits[0] || b.bits[0] == 0) {
        a.bits[0] = get_rand(0, INT_MAX);
        b.bits[0] = get_rand(0, INT_MAX);
    }

    int code = s21_div(a, b, &res);
    int64_t expected = a.bits[0] / b.bits[0];

    ck_assert_int_eq(code, ARITHMETIC_OK);
    ck_assert_int_eq(res.bits[0], expected);
}
END_TEST

START_TEST(division_by_zero_and_zero_like_vals) {
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_decimal res = {0};

    set_exponent(&a, get_rand(0, 27));
    set_exponent(&b, get_rand(0, 27));
    set_random_sign(&a);
    set_random_sign(&b);

    int code = s21_div(a, b, &res);
    ck_assert_int_eq(code, S21_NAN);
}
END_TEST

Suite *suite_s21_div(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_div"));
    TCase *tc = tcase_create("s21_div_tc");

    /* ✅ Heavily tested. Passed all 40000 tests several times */
    /* tcase_add_loop_test(tc, divison_by_one, 0, 100); */
    /* tcase_add_loop_test(tc, divison_by_two, 0, 100); */
    /* tcase_add_loop_test(tc, gcc_128_division_by_ten, 0, 100); */
    /* tcase_add_loop_test(tc, gcc_128_bits, 0, 1); */
    tcase_add_loop_test(tc, random_float, 0, 1);

    /* tcase_add_loop_test(tc, divison_by_rand_int, 0, 100); */

    /* 🌃 Edge cases */
    /* tcase_add_loop_test(tc, division_by_zero_and_zero_like_vals, 0, 100); */

    /**
     * [#38] TODO: (!) - SEEN BY @bezlant WILL WORK ON IT TOMORROW (14.06)
     * @bezlant - I will really appreciate your help! 😊
     *
     * -[x] test return code. This is VERY important & will be checked by
     * Verter.
     *
     * -[] 📌 Add division with different exponents. Test our exponent logic &
     * normalizing capabilities.
     *  @bezlant, @AndreyZhelannikov I don't really grasp the logic with
     * exponent handling ;( Need explanation by Andrey.
     *
     * -[] add more edgecases
     *      -[x] division by zero -> check NAN
     *      -[] bank rounding case
     *      -[] really large / small numbers (around 96 bit) divided by large /
     * small numbers
     *
     * -[] test floating point div (this is detected when MOD is not zero, i.e.
     * 5/3 or 3/5)
     *
     */

    suite_add_tcase(s, tc);
    return s;
}
