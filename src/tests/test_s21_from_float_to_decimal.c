#include "s21_decimal_test.h"

Suite *suite_s21_from_float_to_decimal(void) {
    Suite *s = suite_create("suite_s21_from_float_to_decimal");
    TCase *tc = tcase_create("s21_from_float_to_decimal_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}
