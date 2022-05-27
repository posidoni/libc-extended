#include "s21_decimal_test.h"

Suite *suite_s21_from_decimal_to_float(void) {
    Suite *s = suite_create("suite_s21_from_decimal_to_float");
    TCase *tc = tcase_create("s21_from_decimal_to_float_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}
