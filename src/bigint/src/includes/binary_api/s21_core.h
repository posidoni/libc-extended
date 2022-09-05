#ifndef SRC_BINARY_API_S21_CORE_H_
#define SRC_BINARY_API_S21_CORE_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "s21_binary_arithmetic.h"
#include "s21_binary_logic.h"
#include "s21_binary_shifts.h"
#include "s21_exponent.h"
#include "s21_structures.h"

#define IS_SET(X, POS)       ((X >> POS) & 1U)
#define ADD_BIT(X, POS)      ((X) |= (1U << (POS)))
#define SET_BIT(X, BIT, POS) (X |= (BIT << POS))
#define INIT_ZERO(X)         (X &= (0U << 32))
#define ZERO_BIT(X, POS)     (X &= ~(1UL << POS));

#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MIN_DECIMAL -79228162514264337593543950335.0F

// SIGN handling
bool get_sign(s21_decimal decimal);
void set_sign_neg(s21_decimal *decimal);
void set_sign_pos(s21_decimal *decimal);
void set_sign(s21_decimal *decimal, int sign);

// Smart bit setters
void set_bit_1(s21_decimal *n, int pos);
void set_bit_0(s21_decimal *n, int pos);
int get_bit(s21_decimal n, int pos);
int eq_zero(s21_decimal value);
int eq_zerol(s21_decimal value);

// Helpers
int max(int a, int b);
int min(int a, int b);

#endif  // SRC_BINARY_API_S21_CORE_H_
