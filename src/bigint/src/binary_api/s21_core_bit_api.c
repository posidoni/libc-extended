#include "s21_decimal.h"

// returns 0 meaning positive 1 negative
bool get_sign(s21_decimal decimal) { return IS_SET(decimal.bits[3], D_SIGN); }
void set_sign_neg(s21_decimal *decimal) { ADD_BIT(decimal->bits[3], D_SIGN); }
void set_sign_pos(s21_decimal *decimal) { ZERO_BIT(decimal->bits[3], D_SIGN); }

void set_sign(s21_decimal *decimal, int sign) {
    sign ? set_sign_neg(decimal) : set_sign_pos(decimal);
}

int get_bit(s21_decimal n, int pos) {
    return (n.bits[pos / 32] >> (pos % 32)) & 1;
}
void set_bit_1(s21_decimal *n, int pos) {
    ADD_BIT(n->bits[pos / 32], pos % 32);
}
void set_bit_0(s21_decimal *n, int pos) {
    ZERO_BIT(n->bits[pos / 32], pos % 32);
}

int eq_zero(s21_decimal value) {
    return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}
int eq_zerol(s21_decimal value) {
    return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0 &&
            value.bits[3] == 0);
}

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }
