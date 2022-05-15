#include "s21_math_test.h"

START_TEST(floor_loop_test) {
    double n = fRand(DBL_MIN, DBL_MAX);
    if (rand() % 2)
        n = -n;
    ck_assert_ldouble_eq(s21_floor(n), floor(n));
}
END_TEST

Suite *suite_s21_floor(void) {
    Suite *s = suite_create("s21_floor");
    TCase *tc = tcase_create("s21_floor_tc");

    tcase_add_loop_test(tc, floor_loop_test, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
