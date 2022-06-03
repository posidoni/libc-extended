#include "../s21_decimal_test.h"

Suite *suite_s21_round(void) {
    Suite *s = suite_create("suite_s21_round");
    TCase *tc = tcase_create("s21_round_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}
