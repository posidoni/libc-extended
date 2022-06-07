#include "../../s21_decimal_test.h"
START_TEST(simple) {
    s21_decimal value = get_random_decimal(1, 5);

    float res = 0;
    s21_from_decimal_to_float(value, &res);
    printf("%f\n", res);
    print_bits_r(value);
}
END_TEST

Suite *suite_s21_from_decimal_to_float(void) {
    Suite *s = suite_create("suite_s21_from_decimal_to_float");
    TCase *tc = tcase_create("s21_from_decimal_to_float_tc");

    tcase_add_test(tc, simple);

    suite_add_tcase(s, tc);
    return s;
}
