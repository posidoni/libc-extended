#ifndef S21_COMPARISON_H_
#define S21_COMPARISON_H_

#include "../binary_api/s21_core.h"

/* S21_Decimal API */
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

bool s21_is_less_basic(s21_decimal a, s21_decimal b);

int s21_check_infinity(int code, int sign);

/* Helpers */
bool both_all_zeroes(s21_decimal a, s21_decimal b);

#endif  // S21_COMPARISON_H_
