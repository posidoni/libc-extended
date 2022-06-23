#include "../s21_decimal_test.h"

START_TEST(random_loop) {
    int x = rand();

    if (rand() % 2)
        x = -x;

#ifdef DEBUG
    static int test = 0;
    printf("----------------------------------------\n");
    printf("test %d\n", test++);
    printf("rand x =      %d\n", x);
#endif

    s21_decimal expected = {0};
    int expected_int = abs(x);

    if (x < 0 && expected_int % 10 != 0)
        expected_int = (expected_int / 10 + 1);
    else
        expected_int /= 10;

    expected_int = x < 0 ? -expected_int : expected_int;

    s21_from_int_to_decimal(expected_int, &expected);

    s21_decimal got = {0};
    s21_from_int_to_decimal(x, &got);
    set_exponent(&got, 1);

    s21_decimal res = {0};
    int ret = s21_floor(got, &res);

#ifdef DEBUG
    printf("expected_int = %d\n", expected_int);
    printf("expected = ");
    print_bits_r(expected);
    printf("res      = ");
    print_bits_r(res);
    printf("----------------------------------------\n");
#endif

    ck_assert_int_eq(s21_is_equal(expected, res), TRUE);
    ck_assert_int_eq(ret, CONVERTATION_OK);
}
END_TEST

Suite *suite_s21_floor(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_floor"));
    TCase *tc = tcase_create("s21_floor_tc");

    tcase_add_loop_test(tc, random_loop, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}
