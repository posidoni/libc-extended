#include "s21_math_test.h"

START_TEST(atan_test_1) {
    double x = RandomReal(-1e10, 1e10);
}
END_TEST

Suite *suite_s21_atan(void) {
    Suite *s = suite_create("suite_s21_atan");
    TCase *tc = tcase_create("s21_add_tc");

    // tcase_add_test(tc, );
    tcase_add_loop_test(tc, atan_test_1, 0, 15);

    suite_add_tcase(s, tc);
    return s;
}
