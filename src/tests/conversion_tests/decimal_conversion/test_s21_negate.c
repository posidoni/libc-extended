#include "../../s21_decimal_test.h"

START_TEST(negate_loop) {
    s21_decimal n = {0};
    s21_decimal res = {0};

    set_random_sign(&n);
    s21_negate(n, &res);

    unsigned char bit = !get_sign(n);

    ADD_BIT(bit, 31);
    ck_assert_int_eq(get_sign(res), bit);
}
END_TEST

Suite *suite_s21_negate(void) {
    Suite *s = suite_create(PRETTY_PRINT("suite_s21_negate"));
    TCase *tc = tcase_create("s21_negate_tc");

    tcase_add_loop_test(tc, negate_loop, 0, 6969);

    suite_add_tcase(s, tc);
    return s;
}
