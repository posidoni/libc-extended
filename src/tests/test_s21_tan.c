
#include "s21_math_test.h"

START_TEST(tan_test_1) {
<<<<<<< HEAD
<<<<<<< HEAD
    double x = RandomReal(-2 * M_PI, 2 * M_PI);
=======
    // double x = RandomReal(-2 * M_PI, 2 * M_PI);
    double x = S21_M_PI_2;
    // double x = RandomReal(-1e5, 1e5);
>>>>>>> 85ddb17 (Add TODO)
=======
    double x = RandomReal(-2 * S21_M_PI, 2 * S21_M_PI);
>>>>>>> 144f1f3 (Fix pow edge cases)
    ck_assert_ldouble_eq_tol(s21_tan(x), tanl(x), 1e-06);
}
END_TEST

START_TEST(tan_0) {
    double x = 0;
    ck_assert_double_eq_tol(s21_tan(x), tanl(x), 1e-06);
}
END_TEST

START_TEST(tan_minf) {
    ck_assert_ldouble_nan(s21_tan(-INFINITY));
    ck_assert_ldouble_nan(tanl(-INFINITY));
}
END_TEST

START_TEST(tan_inf) {
    ck_assert_ldouble_nan(s21_tan(INFINITY));
    ck_assert_ldouble_nan(tanl(INFINITY));
}
END_TEST

START_TEST(tan_nan) {
    ck_assert_ldouble_nan(s21_tan(NAN));
    ck_assert_ldouble_nan(tanl(NAN));
}
END_TEST

Suite *suite_s21_tan(void) {
    Suite *s = suite_create("s21_tan");
    TCase *tc = tcase_create("s21_tan_tc");

    tcase_add_loop_test(tc, tan_test_1, 0, 10000);
    tcase_add_test(tc, tan_0);
    tcase_add_test(tc, tan_minf);
    tcase_add_test(tc, tan_inf);
    tcase_add_test(tc, tan_nan);

    suite_add_tcase(s, tc);
    return s;
}