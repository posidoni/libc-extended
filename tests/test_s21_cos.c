#include "s21_math_test.h"

START_TEST(cos_test_1) {
    double x = RandomReal(-1e10, 1e10);
    ck_assert_double_eq_tol(s21_cos(x), cos(x), 1e-06);
}
END_TEST

Suite *suite_s21_cos(void) {
    Suite *s = suite_create("suite_s21_cos");
    TCase *tc = tcase_create("s21_cos_tc");

    // tcase_add_test(tc, );
    tcase_add_loop_test(tc, cos_test_1, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}
