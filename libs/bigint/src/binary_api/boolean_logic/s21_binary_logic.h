#ifndef S21_BINARY_LOGIC_H_
#define S21_BINARY_LOGIC_H_

#include "../s21_structures.h"

s21_decimal bit_and(s21_decimal a, s21_decimal b);
s21_decimal bit_land(s21_decimal a, s21_decimal b);
s21_decimal bit_or(s21_decimal a, s21_decimal b);
s21_decimal bit_xor(s21_decimal a, s21_decimal b);
s21_decimal bit_lxor(s21_decimal a, s21_decimal b);
s21_decimal bit_not(s21_decimal a);

#endif  // S21_BINARY_LOGIC_H_
