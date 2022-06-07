#include "../s21_decimal_test.h"

START_TEST(gmp_random) {
    s21_decimal dec1 = {0};
    mpz_t mpz_val, mpz_copy;

    mpz_init_set_ui(mpz_val, 0);
    mpz_init_set_ui(mpz_copy, 0);

    get_random_pair(&dec1, &mpz_val, 3);

    convert_decimal_to_gmp(&mpz_copy, &dec1);
    s21_decimal dec2 = convert_gmp_to_decimal(mpz_val);

    /* d1 is sometimes < d2, else they are equal */
    if (get_rand(0, 1)) {
        int current_exp = get_exponent(dec1);
        /* Make d1 smaller or d2 larger */
        if (current_exp < 28) {
            set_exponent(&dec1, (current_exp + 1));
        } else {
            SET_BIT(dec2.bits[3], 1, 31);
        }
        gmp_sum_int(mpz_copy, 100);
    }

    // Compare op1 and op2. Return a positive value if op1 > op2, zero if op1 = op2, or a negative value if op1 < op2.
    int got = (s21_is_less_or_equal(dec1, dec2));
    int expected = mpz_cmp(mpz_val, mpz_copy);

    mpz_clear(mpz_copy);
    mpz_clear(mpz_val);

    if (got == 1 && expected <= 0) {
        ck_assert_int_eq(got, 1);
    } else {
        ck_assert_int_eq(1, 0);
    }
}
END_TEST

Suite *suite_s21_is_less_or_equal(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_is_less_or_equal"));
    TCase *tc = tcase_create("s21_is_less_or_equal_tc");

    tcase_add_loop_test(tc, gmp_random, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}
