#include "../../s21_decimal_test.h"

START_TEST(float_to_dec) {
    s21_decimal res = {0};

    float expected = get_random_float(-12345.6789, 12345.6789);
    int err = s21_from_float_to_decimal(expected, &res);
    float got = 0;
    s21_from_decimal_to_float(res, &got);

#ifdef DEBUG
    static int test = 0;
    printf("TEST: %d\n", test++);
    printf("------------------------------------\n");
    printf("expected = %.29f\n", expected);
    printf("got      = %.29f\n", got);
    printf("------------------------------------\n");
#endif

    if (err == CONVERTATION_OK)
        ck_assert_float_eq_tol(got, expected, 1e-06);
}

Suite *suite_s21_from_float_to_decimal(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_from_float_to_decimal"));
    TCase *tc = tcase_create("s21_from_float_to_decimal_tc");

    tcase_add_loop_test(tc, float_to_dec, 0, 10);

    suite_add_tcase(s, tc);
    return s;
}
