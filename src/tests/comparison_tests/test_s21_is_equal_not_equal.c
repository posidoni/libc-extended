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

    /* (!) Hack. Change this to our own function */
    tmp_normalize_exponent(&a1);

    int got = !(s21_is_equal(a1, res));
    int expected = mpz_cmp(mpz_val, mpz_copy);

    ck_assert_int_eq(got, expected);

    mpz_clear(mpz_copy);
    mpz_clear(mpz_val);
}
END_TEST

START_TEST(gmp_random_inequality) {
    int inequality = rand() % 2;
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

    if (inequality) {
        a1.bits[0] = rand();
        a1.bits[1] = rand();
        get_random_pair(&a1, &mpz_val, 3);
        a1.bits[2] = rand();
        res.bits[0] = -3;

        mpz_clear(mpz_copy);
        mpz_clear(mpz_val);

        ck_assert_int_eq(s21_is_not_equal(res, a1), 1);
    } else {
        /* (!) Hack. Change this to our own function */
        tmp_normalize_exponent(&a1);

        int expected = mpz_cmp(mpz_val, mpz_copy);
        int got = !(s21_is_equal(a1, res));

        mpz_clear(mpz_copy);
        mpz_clear(mpz_val);

        ck_assert_int_eq(got, abs(expected));
    }
}
END_TEST

START_TEST(equality_all_zeros) {
    s21_decimal n1 = {0};
    s21_decimal n2 = {0};
    set_sign_neg(&n1);

    s21_decimal n3 = {0};
    s21_decimal n4 = {0};
    set_exponent(&n3, 5);

    s21_decimal n5 = {0};
    set_sign_pos(&n5);
    set_exponent(&n5, 10);
    s21_decimal n6 = {0};
    set_sign_neg(&n6);

    // (1) zeros + different sign bit (+0 and -0)
    // (2) zeros + diff exponent (0e-25 && 0e-1)
    // (3) signs + exponents + zeros (+0e-3 && -0e5)

    int got1 = s21_is_equal(n1, n2);
    int got2 = s21_is_equal(n3, n4);
    int got3 = s21_is_equal(n5, n6);

    ck_assert_int_eq(got1, true);
    ck_assert_int_eq(got2, true);
    ck_assert_int_eq(got3, true);
}
END_TEST

Suite *suite_s21_is_or_not_equal(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_is_or_not_equal"));
    TCase *tc = tcase_create("s21_is_or_not_equal_tc");

    /* Tests: (1) sign, (2) exponent (0 - 28), (3) numbers */
    tcase_add_loop_test(tc, gmp_random, 0, 100);
    /* All zeroes are the only possible special case here */
    tcase_add_test(tc, equality_all_zeros);
    /* Randomly tests inequality in ~50% of cases */
    tcase_add_loop_test(tc, gmp_random_inequality, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}
