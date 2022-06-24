#include "../s21_decimal_test.h"

START_TEST(hardcoded_decimal_loop) {
    s21_decimal n1 = get_random_decimal(get_rand(0, 3), get_rand(0, 26));
    s21_decimal n2 = n1;
    s21_decimal n3 = get_random_decimal(get_rand(0, 3), get_rand(0, 26));

    int got_eq = s21_is_equal(n1, n2);
    int got_ineq = s21_is_not_equal(n1, n3);

    ck_assert_int_eq(got_eq, true);

    if (!both_all_zeroes(n1, n3)) {
        ck_assert_int_eq(got_ineq, true);
    } else {
        ck_assert_int_eq(got_ineq, false);
    }
}
END_TEST

Suite *suite_s21_is_or_not_equal(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_is_or_not_equal"));
    TCase *tc = tcase_create("s21_is_or_not_equal_tc");

    tcase_add_loop_test(tc, hardcoded_decimal_loop, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}
