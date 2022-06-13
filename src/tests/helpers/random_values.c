#include "../s21_decimal_test.h"

static void set_random_pair_sign(s21_decimal *dec, mpz_t *in_mpz_copy);

void debug_print_pair(s21_decimal *dec, mpz_t *big, bool exp_applied);

static void get_random_binary_string(s21_decimal *dec, char *mpz_bin_str,
                                     int size);

int get_random_pair(s21_decimal *in, mpz_t *in_mpz_copy, int size) {
    char mpz_bin_str[300] = {'\0'};

    get_random_binary_string(in, mpz_bin_str, size);

    int exp = get_rand(0, 3);
    set_exponent(in, exp);

    bool res = mpz_set_str(*in_mpz_copy, mpz_bin_str, 2);

    /* This is heavily tested! According to output of binary calculator, we
     * indeed */
    /* get equal numbers (if we reverse our decimal representation) */

#ifdef DEBUG
    debug_print_pair(in, in_mpz_copy, false);
#endif

    apply_exponent_to_mpz(in_mpz_copy, exp);

#ifdef DEBUG
    debug_print_pair(in, in_mpz_copy, false);
#endif

    set_random_pair_sign(in, in_mpz_copy);

    return res;
}

static void get_random_binary_string(s21_decimal *in, char *mpz_bin_str,
                                     int size) {
    for (int j = 0, m = 0; j < size; j++) {
        for (int i = 0; i < 32; i++, m++) {
            if (rand() % 2) {
                ADD_BIT(in->bits[j], i);
                mpz_bin_str[m] = '1';
            } else {
                ZERO_BIT(in->bits[j], i);
                mpz_bin_str[m] = '0';
            }
        }
    }

    /* TODO: This reverse is needed to match the format of normal binary with
     * subject
     */
    for (int j = 0; j < size; j++)
        in->bits[j] = reverse_bits(in->bits[j]);
}

void debug_print_pair(s21_decimal *dec, mpz_t *big, bool exp_applied) {
    printf("=================\n");

    if (exp_applied)
        printf("After exponent: \n");
    else
        printf("Before exponent: \n");

    printf("Exponent value: [%d]\n", get_exponent(*dec));
    printf("Decimal:");
    print_bits_no_exp(*dec);
    printf("Mpz_bin:");
    print_mpz_binary(*big);
    printf("MPZ_dec: ");
    print_mpz_decimal(*big);
    printf("=================\n");
}

static void set_random_pair_sign(s21_decimal *dec, mpz_t *in_mpz_copy) {
    if (get_rand(0, 1)) {
        set_sign_neg(dec);
        mpz_neg(*in_mpz_copy, *in_mpz_copy);
    } else {
        set_sign_pos(dec);
    }
}

/**
 * @brief Returns random signed decimal of specified size with exponent in range
 * [min; max].
 *
 * @param size - size array of bits (1,3)
 * @param exp - max exp (0....exp)
 *
 * @return s21_decimal
 */

s21_decimal get_random_decimal(int size, int exp) {
    s21_decimal res = {0};
    set_exponent(&res, get_rand(0, exp));

    set_random_sign(&res);

    for (int j = 0; j < size; j++) {
        for (int i = 31; i > 0; i--) {
            unsigned int x = rand() % 2;
            SET_BIT(res.bits[j], x, i);
        }
    }

    return res;
}

int get_rand(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void set_random_sign(s21_decimal *dec) {
    if (rand() % 2)
        set_sign_neg(dec);
    else
        set_sign_pos(dec);
}
