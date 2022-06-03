#include "../s21_decimal_test.h"

START_TEST(mul_loop) {
    mpz_t mpz_val1;
    mpz_init(mpz_val1);
    mpz_set_ui(mpz_val1, 0);

    mpz_t mpz_val2;
    mpz_init(mpz_val2);
    mpz_set_ui(mpz_val2, 0);

    mpz_t mpz_res;
    mpz_init(mpz_res);
    mpz_set_ui(mpz_res, 0);

    s21_decimal val1 = {0};
    get_random_pair(&val1, &mpz_val1, 1);
    s21_decimal val2 = {0};
    get_random_pair(&val2, &mpz_val2, 1);
    s21_decimal res = {0};

#define DEBUG
#ifdef DEBUG
    printf("val1 = ");
    print_bits_r(val1);
    printf("val2 = ");
    print_bits_r(val2);
    printf("mpz_val1 = ");
    print_bits_r(convert_gmp_to_decimal(mpz_val1));
    printf("mpz_val2 = ");
    print_bits_r(convert_gmp_to_decimal(mpz_val2));
#endif

    /* NOTE: GMP library works incorrectly or other functioned needed */
    mpz_mul(mpz_res, mpz_val1, mpz_val2);
    s21_mul(val1, val2, &res);

#ifdef DEBUG
    puts("-------------RESULT----------------");
    printf("mpz_res = ");
    print_bits_r(convert_gmp_to_decimal(mpz_res));
    printf("res = ");
    print_bits_r(res);
    puts("-------------RESULT----------------");
#endif

    ck_assert_int_eq(s21_is_equal(res, convert_gmp_to_decimal(mpz_res)), TRUE);
}
END_TEST

Suite *suite_s21_mul(void) {
    Suite *s = suite_create("suite_s21_mul");
    TCase *tc = tcase_create("s21_mul_tc");

    tcase_add_loop_test(tc, mul_loop, 0, 1);

    suite_add_tcase(s, tc);
    return s;
}
