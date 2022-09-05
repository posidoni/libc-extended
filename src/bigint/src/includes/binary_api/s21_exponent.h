#ifndef S21_EXPONENT_H_
#define S21_EXPONENT_H_

#include "s21_binary_arithmetic.h"
#include "s21_binary_logic.h"
#include "s21_binary_shifts.h"
#include "s21_structures.h"

/* exponent handling */
int get_exponent(s21_decimal decimal);
void set_exponent(s21_decimal *decimal, int new_exponent);
void s21_normalize_decimal_pair(s21_decimal *a, s21_decimal *b, int *overflow);
s21_decimal get_power_of_ten(int pow);

static const char *const binary_powers_of_ten[29] = {
  [0] =
    "00000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000001",
  [1] =
    "00000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000001010",
  [2] =
    "00000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000001100100",
  [3] =
    "00000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000001111101000",
  [4] =
    "00000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000010011100010000",
  [5] =
    "00000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000011000011010100000",
  [6] =
    "00000000000000000000000000000000000000000000000000000000000000000000000000"
    "0011110100001001000000",
  [7] =
    "00000000000000000000000000000000000000000000000000000000000000000000000010"
    "0110001001011010000000",
  [8] =
    "00000000000000000000000000000000000000000000000000000000000000000000010111"
    "1101011110000100000000",
  [9] =
    "00000000000000000000000000000000000000000000000000000000000000000011101110"
    "0110101100101000000000",
  [10] =
    "00000000000000000000000000000000000000000000000000000000000000100101010000"
    "0010111110010000000000",
  [11] =
    "00000000000000000000000000000000000000000000000000000000000101110100100001"
    "1101101110100000000000",
  [12] =
    "00000000000000000000000000000000000000000000000000000000111010001101010010"
    "1001010001000000000000",
  [13] =
    "00000000000000000000000000000000000000000000000000001001000110000100111001"
    "1100101010000000000000",
  [14] =
    "00000000000000000000000000000000000000000000000001011010111100110001000001"
    "1110100100000000000000",
  [15] =
    "00000000000000000000000000000000000000000000001110001101011111101010010011"
    "0001101000000000000000",
  [16] =
    "00000000000000000000000000000000000000000010001110000110111100100110111111"
    "0000010000000000000000",
  [17] =
    "00000000000000000000000000000000000000010110001101000101011110000101110110"
    "0010100000000000000000",
  [18] =
    "00000000000000000000000000000000000011011110000010110110101100111010011101"
    "1001000000000000000000",
  [19] =
    "00000000000000000000000000000000100010101100011100100011000001001000100111"
    "1010000000000000000000",
  [20] =
    "00000000000000000000000000000101011010111100011101011110001011010110001100"
    "0100000000000000000000",
  [21] =
    "00000000000000000000000000110110001101011100100110101101110001011101111010"
    "1000000000000000000000",
  [22] =
    "00000000000000000000001000011110000110011110000011001001101110101011001001"
    "0000000000000000000000",
  [23] =
    "00000000000000000001010100101101000000101100011111100001010010101111011010"
    "0000000000000000000000",
  [24] =
    "00000000000000001101001111000010000110111100111011001100111011011010000100"
    "0000000000000000000000",
  [25] =
    "00000000000010000100010110010101000101100001010000000001010010000100101000"
    "0000000000000000000000",
  [26] =
    "00000000010100101011011111010010110111001100100000001100110100101110010000"
    "0000000000000000000000",
  [27] =
    "00000011001110110010111000111100100111111101000010000000001111001110100000"
    "0000000000000000000000",
  [28] =
    "00100000010011111100111001011110001111100010010100000010011000010001000000"
    "0000000000000000000000",
};

#endif  // S21_EXPONENT_H_