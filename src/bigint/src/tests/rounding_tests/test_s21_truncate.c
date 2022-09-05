#include "s21_decimal_test.h"

START_TEST(gcc_128_bits) {
    /* get random value */
    __int128_t a = llabs(get_random_ll() * rand());

    /* apply exponent */
    int exp = get_rand(0, 10);
    __int128_t b = int128_pow(10, exp);
    __int128_t sum = a / b;

    /* get expected */
    s21_decimal expected = bigint_to_decimal(sum);

    s21_decimal val = bigint_to_decimal(a);
    set_exponent(&val, exp);

    s21_decimal got = {0};

    int ret = s21_truncate(val, &got);

#ifdef DEBUG
    printf("before  =");
    print_bits_r(val);
    printf("expected=");
    print_bits_r(expected);
    printf("got     =");
    print_bits_r(got);
#endif

    ck_assert_int_eq(s21_is_equal(expected, got), TRUE);
    ck_assert_int_eq(ret, CONVERTATION_OK);
}
END_TEST

Suite *suite_s21_truncate(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_truncate"));
    TCase *tc = tcase_create("s21_truncate_tc");

    tcase_add_loop_test(tc, gcc_128_bits, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}
