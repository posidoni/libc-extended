#include "../s21_decimal_test.h"

s21_decimal convert_gmp_to_decimal(mpz_t input) {
    s21_decimal res = {0};
    /* https://gmplib.org/manual/Integer-Import-and-Export */
    mpz_export(res.bits, 0, -1, sizeof(res.bits[0]), -1, 0, input);

    // Macro: int mpz_sgn (const mpz_t op)
    // Return +1 if op > 0, 0 if op = 0, and -1 if op < 0.

    if (mpz_sgn(input) == -1)
        set_sign_neg(&res);

    return res;
}

void convert_decimal_to_gmp(mpz_t *gmp, s21_decimal *dec) {
    // changed to -1 because we work in litte endian & reversed bytes
    mpz_import(*gmp, 3, -1, sizeof(dec->bits[0]), -1, 0, dec->bits);

    apply_exponent_to_mpz(gmp, get_exponent(*dec));

    if (get_sign(*dec))
        mpz_neg(*gmp, *gmp);
}

/**
 * @brief [TEMPORARY HACK (!)] Applies exponent to decimal by converting it
 * to GMP, dividing GMP and converting back to decimal.
 *
 * @param dec pointer to decimal that needs to be normalized
 */

void tmp_normalize_exponent(s21_decimal *dec) {
    /* int exponent = get_exponent(*dec); */

    mpz_t tmp;
    mpz_init(tmp);
    mpz_set_ui(tmp, 0);

    convert_decimal_to_gmp(&tmp, dec);
    init_zero(dec);
    *dec = convert_gmp_to_decimal(tmp);

    mpz_clear(tmp);
}
