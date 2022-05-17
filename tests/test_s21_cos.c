#include "s21_math_test.h"

START_TEST(cos_test_1) {
    double x = RandomReal(-1e10, 1e10);
    ck_assert_double_eq_tol(s21_cos(x), cosl(x), 1e-06);
}
END_TEST

START_TEST(cos_0) {
    double x = 0;
    ck_assert_double_eq_tol(s21_cos(x), cosl(x), 1e-06);
}
END_TEST

START_TEST(cos_minf) {
    ck_assert_ldouble_nan(s21_cos(-INFINITY));
    ck_assert_ldouble_nan(cosl(-INFINITY));
}
END_TEST

START_TEST(cos_inf) {
    ck_assert_ldouble_nan(s21_cos(INFINITY));
    ck_assert_ldouble_nan(cosl(INFINITY));
}
END_TEST

START_TEST(cos_nan) {
    ck_assert_ldouble_nan(s21_cos(NAN));
    ck_assert_ldouble_nan(cosl(NAN));
}
END_TEST

Suite *suite_s21_cos(void) {
    Suite *s = suite_create("s21_cos");
    TCase *tc = tcase_create("s21_cos_tc");

    // tcase_add_test(tc, );
    tcase_add_loop_test(tc, cos_test_1, 0, 10000);
    tcase_add_test(tc, cos_0);
    tcase_add_test(tc, cos_minf);
    tcase_add_test(tc, cos_inf);
    tcase_add_test(tc, cos_nan);

    suite_add_tcase(s, tc);
    return s;
}
