#include "../s21_decimal.h"

#ifndef S21_DECIMAL_CORE_H
#define S21_DECIMAL_CORE_H

#include <math.h>

// checks if a bit is set
#define IS_SET(X, POS) ((X >> POS) & 1U)
// sets the bit to 1 at a give position
#define ADD_BIT(X, POS) (X |= (1U << POS))
// sets multiple bits at poisition by the givev bit value
#define SET_BIT(X, BIT, POS) (X |= (BIT << POS))
// bit becomes 0 P.S. ALL INT NUMBER BECOMES 0 !
#define INIT_ZERO(X) (X &= (0U << 32))
// real zero_bit
#define ZERO_BIT(X, POS) (X &= ~(1UL << POS));

typedef enum {
    D_START_EXP = 16,  // Beginning of the Exponent Bits
    D_END_EXP = 23,    // End of the Exponent Bits
    D_MAX_EXP_VAL = 28,
    D_SIGN = 31,  // Sign Bits
} s21_decimal_const;

typedef enum {
    ARITHMETIC_OK = 0,
    S21_INFINITY = 1,
    S21_NEGATIVE_INFINITY = 2,
    S21_NAN = 3
} arithmetic_result;

typedef struct {
    unsigned int bits[4];
} s21_decimal;

typedef enum {
    FALSE = 0,
    TRUE = 1,
} comparison_result;

typedef enum {
    CONVERTATION_OK = 0,
    CONVERTATION_ERROR = 1
} convertation_result;

void init_decimal(s21_decimal *decimal);
// returns 0 meaning positive 1 negative
bool get_sign(s21_decimal decimal);
void set_sign_neg(s21_decimal *decimal);
void set_sign_pos(s21_decimal *decimal);
int get_exponent(s21_decimal decimal);
void set_exponent(s21_decimal *decimal, int new_exponent);
// helpers
void set_bit_1(s21_decimal *n, int pos);
void set_bit_0(s21_decimal *n, int pos);

int get_bit(s21_decimal n, int pos);
void init_zero(s21_decimal *n);

// BINARY OPERATIONS
s21_decimal bit_and(s21_decimal a, s21_decimal b);
s21_decimal bit_or(s21_decimal a, s21_decimal b);
s21_decimal bit_xor(s21_decimal a, s21_decimal b);
s21_decimal bit_not(s21_decimal a);
s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2, int *err);
s21_decimal binary_subtraction(s21_decimal value_1, s21_decimal value_2,
                               int *err);
s21_decimal binary_multiplication(s21_decimal value_1, s21_decimal value_2,
                                  int *err);
void shiftnr(s21_decimal *a, int n);
void shiftr(s21_decimal *a);
int shiftnl(s21_decimal *a, int n);
s21_decimal shiftnl_ret(s21_decimal a, int n);
s21_decimal shiftnr_ret(s21_decimal a, int n);
int shiftl(s21_decimal *a);

int eq_zero(s21_decimal value);
s21_decimal get_0(void);
s21_decimal get_05(void);
int max(int a, int b);
int min(int a, int b);
void swap(s21_decimal *a, s21_decimal *b);
s21_decimal get_power_of_ten(int pow);

static const char *const binary_powers_of_ten[29] = {
    [0] = "00000000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000000000000000001",
    [1] = "00000000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000000000000001010",
    [2] = "00000000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000000000001100100",
    [3] = "00000000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000000001111101000",
    [4] = "00000000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000010011100010000",
    [5] = "00000000000000000000000000000000000000000000000000000000000000000000"
          "0000000000011000011010100000",
    [6] = "00000000000000000000000000000000000000000000000000000000000000000000"
          "0000000011110100001001000000",
    [7] = "00000000000000000000000000000000000000000000000000000000000000000000"
          "0000100110001001011010000000",
    [8] = "00000000000000000000000000000000000000000000000000000000000000000000"
          "0101111101011110000100000000",
    [9] = "00000000000000000000000000000000000000000000000000000000000000000011"
          "1011100110101100101000000000",
    [10] = "0000000000000000000000000000000000000000000000000000000000000010010"
           "10100000010111110010000000000",
    [11] = "0000000000000000000000000000000000000000000000000000000000010111010"
           "01000011101101110100000000000",
    [12] = "0000000000000000000000000000000000000000000000000000000011101000110"
           "10100101001010001000000000000",
    [13] = "0000000000000000000000000000000000000000000000000000100100011000010"
           "01110011100101010000000000000",
    [14] = "0000000000000000000000000000000000000000000000000101101011110011000"
           "10000011110100100000000000000",
    [15] = "0000000000000000000000000000000000000000000000111000110101111110101"
           "00100110001101000000000000000",
    [16] = "0000000000000000000000000000000000000000001000111000011011110010011"
           "01111110000010000000000000000",
    [17] = "0000000000000000000000000000000000000001011000110100010101111000010"
           "11101100010100000000000000000",
    [18] = "0000000000000000000000000000000000001101111000001011011010110011101"
           "00111011001000000000000000000",
    [19] = "0000000000000000000000000000000010001010110001110010001100000100100"
           "01001111010000000000000000000",
    [20] = "0000000000000000000000000000010101101011110001110101111000101101011"
           "00011000100000000000000000000",
    [21] = "0000000000000000000000000011011000110101110010011010110111000101110"
           "11110101000000000000000000000",
    [22] = "0000000000000000000000100001111000011001111000001100100110111010101"
           "10010010000000000000000000000",
    [23] = "0000000000000000000101010010110100000010110001111110000101001010111"
           "10110100000000000000000000000",
    [24] = "0000000000000000110100111100001000011011110011101100110011101101101"
           "00001000000000000000000000000",
    [25] = "0000000000001000010001011001010100010110000101000000000101001000010"
           "01010000000000000000000000000",
    [26] = "0000000001010010101101111101001011011100110010000000110011010010111"
           "00100000000000000000000000000",
    [27] = "0000001100111011001011100011110010011111110100001000000000111100111"
           "01000000000000000000000000000",
    [28] = "0010000001001111110011100101111000111110001001010000001001100001000"
           "10000000000000000000000000000",
};

// void print_bits(s21_decimal d);
#endif  // S21_DECIMAL_CORE_H
