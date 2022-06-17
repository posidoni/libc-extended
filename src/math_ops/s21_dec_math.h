#ifndef S21_DEC_MATH_H
#define S21_DEC_MATH_H

#include "../binary_api/s21_core.h"

/* Smart artithmetic API */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/* Basic arithmetic API */
s21_decimal s21_integer_mod(s21_decimal dividend, s21_decimal divisor);
s21_decimal s21_integer_div(s21_decimal dividend, s21_decimal divisor,
                            s21_decimal *result);

#endif  // S21_DEC_MATH_H
