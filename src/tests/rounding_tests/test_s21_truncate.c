#include "../s21_decimal_test.h"
START_TEST(simple_truncate) {
    s21_decimal value = get_random_decimal(1, 5);
    s21_decimal res = {0};

    float flt;
    s21_from_decimal_to_float(value, &flt);
    printf("flt=%f\n", flt);

    s21_truncate(value, &res);

    printf("before=");
    print_bits_r(value);
    /* NOTE: normalize is how div should work */
    /* tmp_normalize_exponent(&value); */
    printf("after= ");
    print_bits_r(res);
}
END_TEST

Suite *suite_s21_truncate(void) {
    Suite *s = suite_create("suite_s21_truncate");
    TCase *tc = tcase_create("s21_truncate_tc");

    tcase_add_test(tc, simple_truncate);

    suite_add_tcase(s, tc);
    return s;
}
