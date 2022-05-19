#include "s21_math_test.h"

#pragma region math_info

/**
 * // In the case of the natural logarithm, there is an easy way to reduce the range. Real numbers are almost universally represented in terms of a mantissa and an exponent: x=m*2p, where p is an integer and m is between 1 and 2. Thus log(x) = log(m)+p*log(2). The latter term, p*log(2), is just a multiplication by a known constant. The problem thus reduces to finding the logarithm of a number between 1 and 2 (or between 1/2 and 1). A further range reduction can be made by using the fact that √2 is logarithmically in the middle of [1,2). Thus all that is needed is a way to calculate the logarithm of a number between 1 and √2. This is typically done with a rational polynomial. The ratio of a second order polynomial polynomial to a third order works quite nicely for this.
 *
 */

// https :  // onlinenumbertools.com/convert-number-to-power-of-ten

// If no errors occur, the natural (base-e) logarithm of arg (ln(arg) or log
// e(arg)) is returned.

// If a domain error occurs, an implementation-defined value is returned (NaN where supported)

// If a pole error occurs, -HUGE_VAL, -HUGE_VALF, or -HUGE_VALL is returned.

// zero , inf , - inf =>>> return the input without changes

// Pole errors occur when an operation has a result that is asymptotically infinite, such as divisions by zero, or log(0.0) . Pole error: division by zero, or some other asymptotically infinite result (from finite arguments).

// Error handling
// Errors are reported as specified in math_errhandling.

// Domain error occurs if arg is less than zero.

// Pole error may occur if arg is zero.

// If the implementation supports IEEE floating-point arithmetic (IEC 60559),

// If the argument is ±0, -∞ is returned and FE_DIVBYZERO is raised.
// If the argument is 1, +0 is returned
// If the argument is negative, NaN is returned and FE_INVALID is raised.
// If the argument is +∞, +∞ is returned
// If the argument is NaN, NaN is returned

#pragma endregion math_info

START_TEST(log_test_1_rand) {
    double x = RandomReal(1e-10, 1e+10);

    if (x == 0.0) {
        ck_assert_ldouble_nan(s21_log(x));
        ck_assert_int_eq(errno, ERANGE);
        errno = 0;
        ck_assert_int_eq(errno, ERANGE);
        ck_assert_ldouble_nan(log(x));
    } else if (x < 0.0) {
        ck_assert_ldouble_nan(s21_log(x));
        ck_assert_int_eq(errno, EINVAL);
        errno = 0;
        ck_assert_int_eq(errno, EINVAL);
        ck_assert_ldouble_nan(log(x));
    } else {
        ck_assert_ldouble_eq_tol(s21_log(x), log(x), 1e-6);
    }
}
END_TEST

START_TEST(log_test_2_inf) {
    ck_assert_ldouble_infinite(s21_log(INFINITY));
    ck_assert_ldouble_infinite(log(INFINITY));

    ck_assert_ldouble_nan(s21_log(-INFINITY));
    ck_assert_ldouble_nan(log(-INFINITY));
}
END_TEST

START_TEST(log_test_3_nan) {
    ck_assert_ldouble_nan(s21_log(NAN));
    ck_assert_ldouble_nan(log(NAN));
}
END_TEST

START_TEST(log_test_4_one) {
    ck_assert_ldouble_eq_tol(s21_log(1.0), log(1.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_log(1.1), log(1.1), 1e-6);
}
END_TEST

/* Commented out because of CPPlint */

// START_TEST(log_test_5_zero) {
//     ck_assert_ldouble_infinite(s21_log(0));
//     ck_assert_ldouble_infinite(log(0));
// }
// END_TEST

#pragma endregion log_test_cases

Suite *
suite_s21_log(void) {
    Suite *s = suite_create("s21_log");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_loop_test(tc, log_test_1_rand, 0, 1000);
    tcase_add_test(tc, log_test_2_inf);
    tcase_add_test(tc, log_test_3_nan);
    tcase_add_test(tc, log_test_4_one);
    /* Commented out because of cpplint */
    // tcase_add_test(tc, log_test_5_zero);

    suite_add_tcase(s, tc);
    return s;
}
