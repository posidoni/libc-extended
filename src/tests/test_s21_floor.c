#include "s21_decimal_test.h"

Suite *suite_s21_floor(void) {
    Suite *s = suite_create("suite_s21_floor");
    TCase *tc = tcase_create("s21_floor_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}
