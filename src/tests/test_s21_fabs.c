#include "s21_math_test.h"

START_TEST(normal) {
    double a = -5.53151413431;
    ck_assert_ldouble_eq(s21_fabs(a), fabs(a));
}
END_TEST

START_TEST(nan_num) {
    double a = NAN;
    ck_assert_ldouble_nan(s21_fabs(a));
    ck_assert_ldouble_nan(fabs(a));
}
END_TEST

START_TEST(inf) {
    double a = S21_INF;
    ck_assert_ldouble_infinite(s21_fabs(a));
    ck_assert_ldouble_infinite(fabs(a));
}
END_TEST

START_TEST(large) {
    double a = -9519359135915.53151413431;
    ck_assert_ldouble_eq_tol(s21_fabs(a), fabs(a), EPS);
}
END_TEST

START_TEST(fabs_loop_test_1) {
    double n = fRand(-513.43141, 9159.531151351351);
    if (rand() % 2)
        n = -n;
    ck_assert_ldouble_eq_tol(s21_fabs(n), fabs(n), EPS);
}
END_TEST

START_TEST(not_a_num) {
    ck_assert_ldouble_nan(s21_fabs(NAN));
    ck_assert_ldouble_nan(fabs(NAN));
}
END_TEST

Suite *suite_s21_fabs(void) {
    Suite *s = suite_create("s21_fabs");
    TCase *tc = tcase_create("s21_fabs_tc");

    tcase_add_test(tc, normal);
    tcase_add_test(tc, not_a_num);
    tcase_add_test(tc, inf);
    tcase_add_test(tc, large);
    tcase_add_test(tc, nan_num);
    tcase_add_loop_test(tc, fabs_loop_test_1, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
