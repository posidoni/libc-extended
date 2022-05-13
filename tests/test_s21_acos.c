#include "s21_math_test.h"

Suite *suite_s21_acos(void) {
    Suite *s = suite_create("suite_s21_add");
    TCase *tc = tcase_create("s21_add_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}
