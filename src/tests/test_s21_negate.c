#include "s21_decimal_test.h"

START_TEST(negate) {
    s21_decimal n = {0};
    s21_decimal res = {0};
    s21_negate(n, &res);
    unsigned int bit = 0;
    ADD_BIT(bit, 31);
    ck_assert_int_eq(res.bits[3], bit);
}
END_TEST

Suite *suite_s21_negate(void) {
    Suite *s = suite_create("suite_s21_negate");
    TCase *tc = tcase_create("s21_negate_tc");

    tcase_add_test(tc, negate);

    suite_add_tcase(s, tc);
    return s;
}
