#include "../../s21_decimal_test.h"

s21_decimal convert_gmp_to_decimal(mpz_t input) {
    s21_decimal res = {0};

    //  https://gmplib.org/manual/Integer-Import-and-Export
    mpz_export(res.bits, 0, -1, sizeof(res.bits[0]), 1, 0, input);

    if (mpz_sgn(input) == -1) set_sign_neg(&res);

    return res;
}

void convert_decimal_to_gmp(mpz_t *gmp, s21_decimal *dec) {
    mpz_import(*gmp, 3, 0, sizeof(dec->bits[0]), 0, 0, dec->bits);

    apply_exponent_to_mpz(gmp, get_exponent(*dec));

    if (get_sign(*dec)) mpz_neg(*gmp, *gmp);
}

void apply_exponent_to_decimal(s21_decimal *dec) {
    mpz_t tmp;
    mpz_init(tmp);
    mpz_set_ui(tmp, 0);

    convert_decimal_to_gmp(&tmp, dec);
    init_zero(dec);
    *dec = convert_gmp_to_decimal(tmp);

    mpz_clear(tmp);
}

void apply_exponent_to_mpz(mpz_t *src, int exp) {
    mpz_t mpz_ten_const;
    mpz_init(mpz_ten_const);
    mpz_set_ui(mpz_ten_const, exp);

    while (exp) {
        mpz_fdiv_q(*src, *src, mpz_ten_const);
        exp--;
    }

    mpz_clear(mpz_ten_const);
}
