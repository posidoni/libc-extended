#include "s21_decimal_test.h"

START_TEST(convert_test) {
    s21_decimal expected = {0};
    /* static int test = 0; */
    mpz_t mpz_val;
    s21_get_random_decimal_and_npz_copy(&expected, &mpz_val);

    s21_decimal res = convert_gmp_to_decimal(mpz_val);
    /* TODO: set sign logic needs to be implemented */

#ifdef DEBUG
    printf("TEST = %d\n", test++);
    printf("-------mpz_val--------");
    mpz_out_str(stdout, 2, mpz_val);
    printf("\n");
    printf("-------result---------");
    print_bits(res);
    printf("-------expected-------");
    print_bits(expected);
#endif
    ck_assert_int_eq(s21_is_equal(res, expected), TRUE);
    mpz_clear(mpz_val);
}
END_TEST

Suite *suite_convert_gmp_to_decimal(void) {
    Suite *s = suite_create("suite_convert_dmp_to_decimal");
    TCase *tc = tcase_create("s21_convert_dmp_to_decimal");

    tcase_add_loop_test(tc, convert_test, 0, 10000);

    suite_add_tcase(s, tc);
    return s;
}
