#include "../s21_decimal.h"

// returns 0 meaning positive 1 negative
bool get_sign(s21_decimal decimal) {
    return IS_SET(decimal.bits[3], D_SIGN);
}
void set_sign_neg(s21_decimal *decimal) {
    ADD_BIT(decimal->bits[3], D_SIGN);
}
void set_sign_pos(s21_decimal *decimal) {
    ZERO_BIT(decimal->bits[3], D_SIGN);
}
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

void s21_swap(s21_decimal *a, s21_decimal *b) {
    s21_decimal tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * @brief This function is used to generate 0,5 decimal value that is
 * needed by bank rounding.
 *
 * @return s21_decimal
 */

s21_decimal get_05(void) {
    s21_decimal result;
    s21_from_int_to_decimal(5, &result);
    set_exponent(&result, 1);
    set_sign_pos(&result);
    return result;
}

int eq_zero(s21_decimal value) {
    return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}

void init_zero(s21_decimal *n) {
    n->bits[0] = 0;
    n->bits[1] = 0;
    n->bits[2] = 0;
    n->bits[3] = 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}

uint32_t reverse_bits(uint32_t n) {
    uint32_t m = 0;
    for (int i = 0; i < 32; i++, n >>= 1) {
        m <<= 1;
        m |= n & 1;
    }
    return m;
}
