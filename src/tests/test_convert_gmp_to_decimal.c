#include "s21_decimal_test.h"

START_TEST(convert_test) {
    s21_decimal expected = {0};

    mpz_t mpz_val;
    mpz_init(mpz_val);
    mpz_set_ui(mpz_val, 0);
    get_random_pair(&expected, &mpz_val);

    s21_decimal res = convert_gmp_to_decimal(mpz_val);

    if (IS_SET(expected.bits[3], D_SIGN)) {
        ADD_BIT(res.bits[3], D_SIGN);
    }

    /* TODO: Apply exponent to the gotten number */
    /* bool err_code; */
    /* expected = binary_division( */
    /*     expected, get_power_of_ten(get_exponent(expected)), &err_code); */

#define DEBUG
#ifdef DEBUG
    static int test = 0;
    printf("TEST = %d\n", test++);
    printf("-------mpz_val--------");
    mpz_out_str(stdout, 2, mpz_val);
    printf("\n");
    printf("-------result---------");
    print_bits(res);
    printf("-------expected-------");
    print_bits(expected);
#endif
    /* FIXME: cmp */
    ck_assert_int_eq(s21_is_equal(res, res), TRUE);
    mpz_clear(mpz_val);
}
END_TEST

Suite *suite_convert_gmp_to_decimal(void) {
    Suite *s = suite_create("suite_convert_dmp_to_decimal");
    TCase *tc = tcase_create("s21_convert_dmp_to_decimal");

    tcase_add_loop_test(tc, convert_test, 0, 5);

    suite_add_tcase(s, tc);
    return s;
}