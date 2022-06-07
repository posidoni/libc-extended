#include "../s21_decimal_test.h"
START_TEST(simple_truncate) {
    s21_decimal value = get_random_int_decimal();
    s21_decimal res = {0};

    set_exponent(&value, 3);
    // s21_truncate(value, &res);

    printf("before=");
    print_bits_r(value);
    /* NOTE: normalize is how div should work */
    /* tmp_normalize_exponent(&value); */
    printf("after= ");
    print_bits_r(value);
}
END_TEST

Suite *suite_s21_truncate(void) {
    Suite *s = suite_create("suite_s21_truncate");
    TCase *tc = tcase_create("s21_truncate_tc");

    tcase_add_test(tc, simple_truncate);

    suite_add_tcase(s, tc);
    return s;
}
