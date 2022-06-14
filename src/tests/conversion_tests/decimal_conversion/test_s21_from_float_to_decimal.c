#include "../../s21_decimal_test.h"

START_TEST(float_to_dec) {
    s21_decimal res = {0};
    float val = get_random_float(-100500.100500, 100500.100500);
    s21_from_float_to_decimal(val, &res);

#ifdef DEBUG
    printf("val   = %.29f\n", val);
    printf("resbit=");
    print_bits_r(res);
#endif
}

Suite *suite_s21_from_float_to_decimal(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_from_float_to_decimal"));
    TCase *tc = tcase_create("s21_from_float_to_decimal_tc");

    tcase_add_loop_test(tc, float_to_dec, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}
