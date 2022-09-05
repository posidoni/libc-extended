#ifndef S21_ROUNDING_H_
#define S21_ROUNDING_H_

#include "binary_api/s21_core.h"

// Main API
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);

void s21_bank_rounding(s21_decimal *dec, int times);

// Helpers
void get_bit_string(long double res, char *bits, int exponent);
void set_bits_from_string(char *bits, s21_decimal *result);

#endif  // S21_ROUNDING_H_
