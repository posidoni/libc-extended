#ifndef S21_GMP_HELPERS_
#define S21_GMP_HELPERS_

#include <gmp.h>

#include "../../s21_decimal.h"

// GMP Helpers
s21_decimal get_random_decimal(int size, int exp);
s21_decimal convert_gmp_to_decimal(mpz_t input);
void convert_decimal_to_gmp(mpz_t *gmp, s21_decimal *dec);
int get_random_pair(s21_decimal *in, mpz_t *in_mpz_copy, int size);
void apply_exponent_to_mpz(mpz_t *src, int exp);
void mpz_sint_sum(mpz_t *res, int64_t compound_val);

#endif  // S21_GMP_HELPERS_
