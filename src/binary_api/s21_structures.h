#ifndef S21_STRUCTURES_H_
#define S21_STRUCTURES_H_

typedef struct {
    unsigned int bits[4];
} s21_decimal;

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

typedef enum {
    POS = 0,
    NEG = 1
} arithmetic_consts;

typedef enum {
    FALSE = 0,
    TRUE = 1,
} comparison_result;

typedef enum {
    CONVERTATION_OK = 0,
    CONVERTATION_ERROR = 1
} convertation_result;

#endif  // S21_STRUCTURES_H_
