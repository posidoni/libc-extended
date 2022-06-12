#include "../s21_decimal_test.h"

/* TODO: Implement tests using gmp(suicide) */
/* simply dividing by 10^exp to truncate & multiplying by 10^exp afterwards*/
/* i.e 764183413481 / 10000 = 76418341 */

START_TEST(simple_floor) {
    s21_decimal value = get_random_decimal(1, 5);
    s21_decimal res = {0};

    int code = s21_floor(value, &res);

#ifdef DEBUG
    printf("before=");
    print_bits_r(value);
    printf("after= ");
    print_bits_r(res);
#endif

    ck_assert_int_eq(code, CONVERTATION_OK);
}
END_TEST

Suite *suite_s21_floor(void) {
    Suite *s = suite_create("suite_s21_floor");
    TCase *tc = tcase_create("s21_floor_tc");

    tcase_add_loop_test(tc, simple_floor, 0, 1);

    suite_add_tcase(s, tc);
    return s;
}
