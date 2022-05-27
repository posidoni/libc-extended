#include "s21_decimal_test.h"

Suite *suite_s21_is_less_or_equal(void) {
    Suite *s = suite_create("suite_s21_is_less_or_equal");
    TCase *tc = tcase_create("s21_is_less_or_equal_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}
