#include "../s21_decimal_test.h"

START_TEST(gcc_128_bits) {
    long long long_a = -1;
    long long long_b = 0;

    while (long_a < long_b) {
        long_a = get_random_ll() * rand();
        long_b = get_random_ll() * rand();
    }

    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t sub = a - b;
    s21_decimal res128 = bigint_to_decimal(sub);

    s21_decimal dec_a = ll_to_decimal(long_a);
    s21_decimal dec_b = ll_to_decimal(long_b);

    printf(RED "1:  " ENDCOLOR);
    print_bits_r(dec_a);
    printf(GRN "2:  " ENDCOLOR);
    print_bits_r(dec_b);

    s21_decimal dec_sub = {0};

    s21_sub(dec_a, dec_b, &dec_sub);

    bool comp_res = s21_is_equal(res128, dec_sub);

    printf("3:  ");
    print_bits_r(dec_sub);
    // printf(GRN "2:  " ENDCOLOR);
    // print_bits_r(res128);

    ck_assert_int_eq(comp_res, TRUE);
}

Suite *suite_s21_sub(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_sub"));
    TCase *tc = tcase_create("s21_sub_tc");

    tcase_add_loop_test(tc, gcc_128_bits, 0, 10);

    suite_add_tcase(s, tc);
    return s;
}
