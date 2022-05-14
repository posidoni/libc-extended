#include "s21_math_test.h"

START_TEST(tan_test_1) {
    double x = RandomReal(-1e10, 1e10);
    // ck_assert_double_eq_tol(s21_tan(x), tan(x), 1e-06);
    // printf("A: %6Lf\n", a);
    // printf("B: %6Lf\n", b);
    ck_assert_ldouble_eq_tol(s21_tan(x), (long double)tan(x), 1e-06);
}
END_TEST

Suite *suite_s21_tan(void) {
    Suite *s = suite_create("suite_s21_tan");
    TCase *tc = tcase_create("s21_tan_tc");

    tcase_add_loop_test(tc, tan_test_1, 0, 10);

    suite_add_tcase(s, tc);
    return s;
}
