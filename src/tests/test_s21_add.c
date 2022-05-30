#include "s21_decimal_test.h"

START_TEST(add_test1) {
    //
    s21_decimal v1, v2, sum;
    s21_from_int_to_decimal(0, &v1);
    s21_from_int_to_decimal(0, &v2);

    // for (int i = 0; i < 96; ++i)
    // if (rand() % 2) set_bit_1(&v1, i);
    // for (int i = 0; i < 96; ++i)
    // if (rand() % 2) set_bit_1(&v2, i);

    set_exponent(&v1, 0);
    set_exponent(&v2, 1);
    s21_from_int_to_decimal(1, &v1);
    s21_from_int_to_decimal(1, &v2);

    int code = s21_add(v1, v2, &sum);

    printf("\nNUMBERS:\n");
    printf("EXP = %d ", get_exponent(v1));
    print_bits_r(v1);
    printf("EXP = %d ", get_exponent(v2));
    print_bits_r(v2);
    printf("EXP = %d ", get_exponent(sum));
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