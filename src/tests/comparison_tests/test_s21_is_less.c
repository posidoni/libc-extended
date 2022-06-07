#include "../s21_decimal_test.h"

START_TEST(gmp_random) {
    s21_decimal dec1 = {0};
    mpz_t mpz_val, mpz_copy;

    mpz_init_set_ui(mpz_val, 0);
    mpz_init_set_ui(mpz_copy, 0);

    get_random_pair(&dec1, &mpz_val, 3);

    convert_decimal_to_gmp(&mpz_copy, &dec1);
    s21_decimal dec2 = convert_gmp_to_decimal(mpz_val);

    /* d1 is always < d2 */
    gmp_sum_int(&mpz_copy, 100);

    // Compare op1 and op2. Return a positive value if op1 > op2, zero if op1 = op2, or a negative value if op1 < op2.
    int got = s21_is_less(dec1, dec2);

    /* BUG (!) MPZ IS UNABLE TO CORRECTLY COMPARE UNSIGNED INTS */
    int expected = mpz_cmp(mpz_val, mpz_copy);
    /* BUG (!) I NEED TO WRITE MY OWN LOGIC!!!! */

    if (got == 1 && expected < 0) {
        ck_assert_int_eq(got, 1);
    } else {
        printf("GOT: %d EXPECTED: %d\n", got, expected);
        print_bits_r(dec1);
        print_bits_r(dec2);
        printf("MPZ: \n");
        
        print_mpz_decimal(mpz_val);
        print_mpz_decimal(mpz_copy);

        printf("END: \n");
        ck_assert_int_eq(1, 0);
    }
    
    mpz_clear(mpz_copy);
    mpz_clear(mpz_val);
}
END_TEST

// A : 1959779897 
// B : 580803652

Suite *
suite_s21_is_less(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_is_less"));
    TCase *tc = tcase_create("s21_is_less_tc");

    tcase_add_loop_test(tc, gmp_random, 0, 5);

    suite_add_tcase(s, tc);
    return s;
}
