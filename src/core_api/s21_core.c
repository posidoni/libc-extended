#include "s21_core.h"

void init_decimal(s21_decimal *decimal) { memset(decimal, 0, sizeof(*decimal)); }

// returns 0 meaning positive 1 negative
bool get_sign(s21_decimal decimal) { return IS_SET(decimal.bits[3], D_SIGN); }
void set_sign_neg(s21_decimal *decimal) { ADD_BIT(decimal->bits[3], D_SIGN); }
void set_sign_pos(s21_decimal *decimal) { ZERO_BIT(decimal->bits[3], D_SIGN); }

int get_bit(s21_decimal n, int pos) { return (n.bits[pos / 32] >> (pos % 32)) & 1; }
void set_bit_1(s21_decimal *n, int pos) { ADD_BIT(n->bits[pos / 32], pos % 32); }
void set_bit_0(s21_decimal *n, int pos) { ZERO_BIT(n->bits[pos / 32], pos % 32); }

s21_decimal get_power_of_ten(int pow) {
    s21_decimal result;
    init_zero(&result);
    set_exponent(&result, 0);
    for (int i = 0; i < 96; ++i) {
        if (binary_powers_of_ten[pow][95 - i] == '1') {
            set_bit_1(&result, i);
        } else {
            set_bit_0(&result, i);
        }
    }
    return result;
}

int get_exponent(s21_decimal decimal) {
    int exponent = 0;
    for (int i = D_START_EXP, j = 0; i <= D_END_EXP; i++, j++) {
        if (IS_SET(decimal.bits[3], i)) ADD_BIT(exponent, j);
    }
    return exponent;
}

void set_exponent(s21_decimal *decimal, int new_exponent) {
    if (new_exponent <= 28) {
        short sign = IS_SET(decimal->bits[3], D_SIGN);
        decimal->bits[3] = 0;
        if (sign) set_sign_neg(decimal);
        SET_BIT(decimal->bits[3], new_exponent, D_START_EXP);
    } else {
        // TODO: Replace with a system function call
        fprintf(stderr, "VERY BIG EXPONENT (0 - 28): exp = %d\n", new_exponent);
    }
}

void swap(s21_decimal *a, s21_decimal *b) {
    s21_decimal tmp = *a;
    *a = *b;
    *b = tmp;
}

s21_decimal get_05(void) {
    s21_decimal result;
    s21_from_int_to_decimal(5, &result);
    set_exponent(&result, 1);
    return result;
}

int eq_zero(s21_decimal value) { return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0); }

void init_zero(s21_decimal *n) {
    n->bits[0] = 0;
    n->bits[1] = 0;
    n->bits[2] = 0;
}

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }