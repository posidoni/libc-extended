#ifndef S21_CONVERSION_H_
#define S21_CONVERSION_H_

#include "../binary_api/s21_core.h"
#include "../rounding/s21_rounding.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  // S21_CONVERSION_H_
