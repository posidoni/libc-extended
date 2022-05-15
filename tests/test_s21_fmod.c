#include "s21_math_test.h"

START_TEST(fmod_loop_test) {
    double x = fRand(DBL_MIN, DBL_MAX);
    if (rand() % 2)
        x = -x;
    double y = fRand(DBL_MIN, DBL_MAX);
    if (rand() % 3)
        y = -y;

    ck_assert_ldouble_eq(s21_fmod(x, y), fmod(x, y));
}
END_TEST

Suite *suite_s21_fmod(void) {
    Suite *s = suite_create("s21_fmod");
    TCase *tc = tcase_create("s21_fmod_tc");

    tcase_add_loop_test(tc, fmod_loop_test, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
