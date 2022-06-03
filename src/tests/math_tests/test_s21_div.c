#include "../s21_decimal_test.h"

START_TEST(loop_division_mpz) {
    s21_decimal val = {0};
    s21_decimal divisor = {0};
    s21_decimal res = {0};

    mpz_t mpz_val;
    mpz_init(mpz_val);
    mpz_set_ui(mpz_val, 0);

    mpz_t mpz_divisor;
    mpz_init(mpz_divisor);
    mpz_set_ui(mpz_divisor, 0);

    mpz_t mpz_res;
    mpz_init(mpz_res);
    mpz_set_ui(mpz_res, 0);

    get_random_pair(&val, &mpz_val, 1);
    get_random_pair(&divisor, &mpz_divisor, 1);

/* #define DEBUG */
#ifdef DEBUG
    printf("val = ");
    print_bits_r(val);
    printf("divisor = ");
    print_bits_r(divisor);
    printf("mpz_val = ");
    print_bits_r(convert_gmp_to_decimal(mpz_val));
    printf("mpz_divisor = ");
    print_bits_r(convert_gmp_to_decimal(mpz_divisor));
#endif

    /* NOTE: GMP library works incorrectly or other functioned needed */
    mpz_fdiv_q(mpz_res, mpz_val, mpz_divisor);
    s21_div(val, divisor, &res);

#ifdef DEBUG
    puts("-------------RESULT----------------");
    printf("mpz_res = ");
    print_bits_r(convert_gmp_to_decimal(mpz_res));
    printf("res = ");
    print_bits_r(res);
    puts("-------------RESULT----------------");
#endif

    ck_assert_int_eq(s21_is_equal(res, convert_gmp_to_decimal(mpz_res)), TRUE);

    mpz_clear(mpz_val);
    mpz_clear(mpz_divisor);
    mpz_clear(mpz_res);
}
END_TEST

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
    for (int i = 0; i < 60; ++i) {
        if (rand() % 2)
            set_bit_1(&v1, i);
    }
    // for (int i = 0; i < 78; ++i) {
    // if (rand() % 2) set_bit_1(&v2, i);
    // }

    // set_bit_1(&v1, _i);
    // set_bit_1(&v2, _i);
    // s21_from_int_to_decimal(15, &v1);
    s21_from_int_to_decimal(1, &v2);

    set_exponent(&v1, 1);
    set_exponent(&v2, 12);
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
    // ck_assert_int_eq(get_bit(div, 1), 1);
    // ck_assert_int_eq(1, 0);
}
END_TEST

Suite *suite_s21_div(void) {
    Suite *s = suite_create("suite_s21_div");
    TCase *tc = tcase_create("s21_div_tc");

    /* tcase_add_loop_test(tc, div_test1, 0, 1); */
    tcase_add_loop_test(tc, loop_division_mpz, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
