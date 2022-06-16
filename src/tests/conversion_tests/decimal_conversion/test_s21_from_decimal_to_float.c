#include "../../s21_decimal_test.h"
#define DEBUG

START_TEST(simple_loop) {
    s21_decimal value = get_random_decimal(1, 8);

    int int_expected = 0;
    s21_decimal to_int = value;

    /* zero the exponent to avoid number truncation */
    set_exponent(&to_int, 0);

    int overflow = s21_from_decimal_to_int(to_int, &int_expected);
    int exp_expected = get_exponent(value);

    float expected = int_expected;

    /* recover the exponent */
    while (exp_expected--)
        expected /= 10.0;

    float got = 0;
    int code = s21_from_decimal_to_float(value, &got);

    if (overflow == CONVERTATION_OK) {
#ifdef DEBUG
        printf("expected = %.29f\n", expected);
        printf("got      = %.29f\n", got);
#endif
        ck_assert_float_eq_tol(expected, got, 1e+3);
        ck_assert_int_eq(code, CONVERTATION_OK);
    }
}
END_TEST

Suite *suite_s21_from_decimal_to_float(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_from_decimal_to_float"));
    TCase *tc = tcase_create("s21_from_decimal_to_float_tc");

    tcase_add_loop_test(tc, simple_loop, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}
