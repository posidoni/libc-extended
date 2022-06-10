#include "../s21_decimal_test.h"

START_TEST(decimal_random_noexp_unsigned) {
    s21_decimal dec1 = get_random_decimal(3, 0);
    s21_decimal dec2 = dec1;

    set_sign_pos(&dec1);
    set_sign_pos(&dec2);

    // This test is expected to fail only if uint32 overflow happens, which is
    // very unlikely. Thus, there is no special logic for this case.
    dec2.bits[2] += 1;

    ck_assert_int_eq(s21_is_less(dec1, dec2), true);
}
END_TEST

START_TEST(decimal_random_noexp_signed) {
    s21_decimal dec1 = get_random_decimal(3, 0);
    s21_decimal dec2 = get_random_decimal(3, 0);

    int s1 = get_sign(dec1), s2 = get_sign(dec2);

    if (both_all_zeroes(dec1, dec2)) {
        ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2), true);
    } else {
        // NEG < NEG
        if (s1 && s2) {
            dec1.bits[2] = dec2.bits[2];
            dec1.bits[2] += 100;
            ck_assert_int_eq(s21_is_less(dec1, dec2), true);
        }

        // NEG < POS
        if (s1 && !s2) {
            ck_assert_int_eq(s21_is_less(dec1, dec2), true);
        }

        // POS < NEG
        if (!s1 && s2) {
            ck_assert_int_eq(s21_is_less(dec1, dec2), false);
        }

        // POS < POS
        if (!s1 && !s2) {
            dec2.bits[2] = dec1.bits[2];
            dec2.bits[2] += 10000;
            ck_assert_int_eq(s21_is_less(dec1, dec2), true);
        }
    }
}
END_TEST

START_TEST(decimal_random_exp_unsigned) {
    s21_decimal dec1 = {0};
    s21_decimal dec2 = {0};

    dec1.bits[1] = 500, dec2.bits[1] = 500;
    dec1.bits[2] = 500, dec2.bits[2] = 500;
    dec1.bits[3] = 500, dec2.bits[3] = 500;

    set_sign_pos(&dec1);
    set_sign_pos(&dec2);

    int e1 = get_rand(0, 28), e2 = get_rand(0, 28);

    set_exponent(&dec1, e1);
    set_exponent(&dec2, e2);

    int zeroes = both_all_zeroes(dec1, dec2);

    int res = s21_is_less(dec1, dec2);

    int overflow = 0;
    s21_normalize_decimal_pair(&dec1, &dec2, &overflow);

    if (!zeroes && !overflow && e1 != e2) {
        if (e1 > e2) {
            ck_assert_int_eq(res, true);
        } else {
            ck_assert_int_eq(res, false);
        }
    }
}
END_TEST

START_TEST(all_zeroes) {
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

    int got1 = s21_is_less(n1, n2);
    int got2 = s21_is_less(n3, n4);
    int got3 = s21_is_less(n5, n6);

    ck_assert_int_eq(got1, false);
    ck_assert_int_eq(got2, false);
    ck_assert_int_eq(got3, false);
}
END_TEST

Suite *suite_s21_is_less(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_is_less"));
    TCase *tc = tcase_create("s21_is_less_tc");

    tcase_add_loop_test(tc, decimal_random_noexp_unsigned, 0, 5000);
    tcase_add_loop_test(tc, decimal_random_noexp_signed, 0, 5000);
    tcase_add_loop_test(tc, decimal_random_exp_unsigned, 0, 5000);
    tcase_add_test(tc, all_zeroes);

    suite_add_tcase(s, tc);
    return s;
}
