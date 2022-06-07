#include "../s21_decimal_test.h"

START_TEST(simple_floor) {
    s21_decimal value = get_random_decimal(1, 5);
    s21_decimal res = {0};

    float flt;
    s21_from_decimal_to_float(value, &flt);
    printf("flt=%f\n", flt);

    s21_floor(value, &res);

    printf("before=");
    print_bits_r(value);

    printf("after= ");
    print_bits_r(res);
}
END_TEST

Suite *suite_s21_floor(void) {
    Suite *s = suite_create("suite_s21_floor");
    TCase *tc = tcase_create("s21_floor_tc");

    tcase_add_test(tc, simple_floor);

    suite_add_tcase(s, tc);
    return s;
}
