#include "../s21_decimal_test.h"

START_TEST(gmp_random) {
    s21_decimal a1 = {0};
    init_zero(&a1);

    mpz_t mpz_val, mpz_copy;
    mpz_init(mpz_val);
    mpz_init(mpz_copy);
    mpz_set_ui(mpz_val, 0);
    mpz_set_ui(mpz_copy, 0);

    get_random_pair(&a1, &mpz_val, 3);

    convert_decimal_to_gmp(&mpz_copy, &a1);
    s21_decimal res = convert_gmp_to_decimal(mpz_val);

    /* Produces randomly smaller / greater numbers */
    if (rand() % 2)
        set_exponent(&a1, (get_exponent(a1) + 1) % 28);

    /* (!) Hack. Change this to our own function */
    tmp_normalize_exponent(&a1);

    // Compare op1 and op2. Return a positive value if op1 > op2, zero if op1 = op2, or a negative value if op1 < op2.
    int got = (s21_is_greater(a1, res));
    int expected = mpz_cmp(mpz_val, mpz_copy);

    mpz_clear(mpz_copy);
    mpz_clear(mpz_val);

    if (expected > 0) {
        ck_assert_int_eq(got, expected);
    } else {
        ck_assert_int_eq(got, 0);
    }
}
END_TEST

Suite *suite_s21_is_greater(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_is_greater"));
    TCase *tc = tcase_create("s21_is_greater_tc");

    tcase_add_loop_test(tc, gmp_random, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}
