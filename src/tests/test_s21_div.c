#include "s21_decimal_test.h"
START_TEST(div_test1) {
    //
    s21_decimal v1, v2, div;

    init_zero(&v1);
    init_zero(&v2);
    // for (int i = 0; i < 96; ++i) set_bit_1(&v1, i);
    // set_bit_0(&v1, 92);
    // set_bit_0(&v1, 93);
    // set_bit_0(&v1, 94);
    // set_bit_0(&v1, 95);
    // for (int i = 0; i < 33; ++i)
    // if (rand() % 2) set_bit_1(&v2, i);

    s21_from_int_to_decimal(124, &v1);
    s21_from_int_to_decimal(2, &v2);

    set_exponent(&v1, 0);
    set_exponent(&v2, 0);
    int code = s21_div(v1, v2, &div);

    printf("\nNUMBERS:\n");
    printf("EXP = %d ", get_exponent(v1));
    print_bits_r(v1);
    printf("EXP = %d ", get_exponent(v2));
    print_bits_r(v2);
    printf("EXP = %d ", get_exponent(div));
    print_bits_r(div);
    printf("\n");

    printf("ERR : %d\n", code);
    ck_assert_int_eq(get_bit(div, 1), 1);
    ck_assert_int_eq(1, 0);
}
END_TEST
Suite *suite_s21_div(void) {
    Suite *s = suite_create("suite_s21_div");
    TCase *tc = tcase_create("s21_div_tc");

    tcase_add_test(tc, div_test1);

    suite_add_tcase(s, tc);
    return s;
}
