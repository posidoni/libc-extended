#include "../s21_decimal_test.h"

START_TEST(simple_truncate) {
    s21_decimal value = get_random_decimal(3, 28);
    s21_decimal res = {0};

    float f_res;

    s21_from_decimal_to_float(value, &f_res);
    int ret = s21_truncate(value, &res);

    /* printf("before="); */
    /* print_bits_r(value); */
    /* printf("before="); */
    /* printf("%f\n", f_res); */

    f_res = truncf(f_res);

    /* printf("after= "); */
    /* print_bits_r(res); */
    /* printf("after= "); */
    /* printf("%f\n", f); */

    float f;
    s21_from_decimal_to_float(res, &f);
    f = truncf(f);

    /* printf("decimal_to_flt = %f\n", f_res); */
    ck_assert_float_eq(f, f_res);
    ck_assert_int_eq(ret, CONVERTATION_OK);
}
END_TEST

Suite *suite_s21_truncate(void) {
    Suite *s = suite_create("suite_s21_truncate");
    TCase *tc = tcase_create("s21_truncate_tc");

    tcase_add_loop_test(tc, simple_truncate, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
