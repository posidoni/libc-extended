#include "s21_math_test.h"

START_TEST(ceil_loop_test) {
    double n = fRand(DBL_MIN, DBL_MAX);
    if (rand() % 2)
        n = -n;
    ck_assert_ldouble_eq(s21_ceil(n), ceil(n));
}
END_TEST

Suite *suite_s21_ceil(void) {
    Suite *s = suite_create("s21_ceil");
    TCase *tc = tcase_create("s21_ceil_tc");

    tcase_add_loop_test(tc, ceil_loop_test, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
