#include "s21_decimal_test.h"

START_TEST(add_test1) {
    //
    s21_decimal v1, v2, sum;
    s21_from_int_to_decimal(0, &v1);
    s21_from_int_to_decimal(0, &v2);
    for (int i = 0; i < 32; ++i) set_bit_1(&v1, i);
    for (int i = 64; i < 96; ++i) set_bit_1(&v1, i);
    set_bit_1(&v2, 0);
    int code = s21_add(v1, v2, &sum);

    for (int i = 0; i < 96; ++i) {
        printf("%-6d : ", i);
        shift_r_one(&v1);
        print_bits_r(v1);
    }
    printf("\nNUMBERS:\n");
    print_bits_r(v2);
    print_bits_r(sum);
    printf("\n");

    ck_assert_int_eq(get_bit(sum, 1), 1);
    //  ck_assert_
}
END_TEST

Suite *suite_s21_add(void) {
    Suite *s = suite_create("suite_s21_add");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_test(tc, add_test1);

    suite_add_tcase(s, tc);
    return s;
}
