#include "../s21_decimal_test.h"

START_TEST(random_loop) {
    int x = rand();

#ifdef DEBUG
    static int test = 0;
    printf("----------------------------------------\n");
    printf("test %d\n", test++);
    printf("rand x = %d\n", x);
#endif

    s21_decimal expected = {0};
    int expected_int = x;

    if (x % 10 > 5) {
        expected_int = (expected_int / 10 + 1) * 10;
    } else if (x % 10 < 5) {
        expected_int = expected_int / 10 * 10;
    } else {
        if ((x / 10 % 10 + 1) % 2 == 0)
            expected_int = (expected_int / 10 + 1) * 10;
        else
            expected_int = expected_int / 10 * 10;
    }

    s21_from_int_to_decimal(expected_int, &expected);
    set_exponent(&expected, 1);

    s21_decimal got = {0};
    s21_from_int_to_decimal(x, &got);
    set_exponent(&got, 1);

#ifdef DEBUG
    printf("before rounding = ");
    print_bits_r(got);
    printf("exponent = %d\n", get_exponent(got));
#endif

    s21_decimal res = {0};
    int ret = s21_round(got, &res);

#ifdef DEBUG
    printf("expected_int=%d\n", expected_int);
    printf("expected = ");
    print_bits_r(expected);
    printf("got      = ");
    print_bits_r(res);
    printf("----------------------------------------\n");
#endif

    ck_assert_int_eq(s21_is_equal(expected, res), TRUE);
    ck_assert_int_eq(ret, CONVERTATION_OK);
}
END_TEST

START_TEST(bank_round_up) {
    float x = 19.55;
    s21_decimal value = {0};
    s21_from_float_to_decimal(x, &value);

    s21_decimal result = {0};
    s21_round(value, &result);

    float got = 0;
    float expected = 20.0;
    s21_from_decimal_to_float(result, &got);

    ck_assert_float_eq_tol(got, expected, 1e-06);
}
END_TEST

START_TEST(bank_round_down) {
    float x = 18.55;
    s21_decimal value = {0};
    s21_from_float_to_decimal(x, &value);

    s21_decimal result = {0};
    s21_round(value, &result);

    float got = 0;
    float expected = 18.0;
    s21_from_decimal_to_float(result, &got);

    ck_assert_float_eq_tol(got, expected, 1e-06);
}
END_TEST

Suite *suite_s21_round(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_round"));
    TCase *tc = tcase_create("s21_round_tc");

    tcase_add_loop_test(tc, random_loop, 0, 100);
    tcase_add_test(tc, bank_round_up);
    tcase_add_test(tc, bank_round_down);

    suite_add_tcase(s, tc);
    return s;
}
