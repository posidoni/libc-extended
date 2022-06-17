#ifndef S21_BINARY_ARITHMETIC_H
#define S21_BINARY_ARITHMETIC_H

#include "../boolean_logic/s21_binary_logic.h"
#include "../s21_structures.h"
#include "../shifts/s21_binary_shifts.h"

s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2, int *err);
s21_decimal binary_subtraction(s21_decimal value_1, s21_decimal value_2,
                               int *err);
s21_decimal binary_multiplication(s21_decimal value_1, s21_decimal value_2,
                                  int *err);

#endif  // S21_BINARY_ARITHMETIC_H
