#include "s21_core.h"

void init_decimal(s21_decimal *decimal) { memset(decimal, 0, sizeof(*decimal)); }

// returns 0 meaning positive 1 negative
bool get_sign(s21_decimal decimal) { return IS_SET(decimal.bits[3], D_SIGN); }
void set_sign_neg(s21_decimal *decimal) { ADD_BIT(decimal->bits[3], D_SIGN); }
void set_sign_pos(s21_decimal *decimal) { ZERO_BIT(decimal->bits[3], D_SIGN); }

int get_exponent(s21_decimal decimal) {
    int exponent = 0;
    for (int i = D_START_EXP, j = 0; i <= D_END_EXP; i++, j++) {
        if (IS_SET(decimal.bits[3], i)) ADD_BIT(exponent, j);
    }
    return exponent;
}

int get_bit(s21_decimal n, int pos) { return (n.bits[pos / 32] >> (pos % 32)) & 1; }

void set_bit_1(s21_decimal *n, int pos) { ADD_BIT(n->bits[pos / 32], pos % 32); }
void set_bit_0(s21_decimal *n, int pos) { ZERO_BIT(n->bits[pos / 32], pos % 32); }

void init_zero(s21_decimal *n) {
    INIT_ZERO(n->bits[0]);
    INIT_ZERO(n->bits[1]);
    INIT_ZERO(n->bits[2]);
}

s21_decimal bit_xor(s21_decimal a, s21_decimal b) {
    s21_decimal result;
    result.bits[0] = a.bits[0] ^ b.bits[0];
    result.bits[1] = a.bits[1] ^ b.bits[1];
    result.bits[2] = a.bits[2] ^ b.bits[2];
    return result;
}

s21_decimal bit_and(s21_decimal a, s21_decimal b) {
    s21_decimal result;
    result.bits[0] = a.bits[0] & b.bits[0];
    result.bits[1] = a.bits[1] & b.bits[1];
    result.bits[2] = a.bits[2] & b.bits[2];
    return result;
}

s21_decimal bit_not(s21_decimal a) {
    s21_decimal result;
    result.bits[0] = ~a.bits[0];
    result.bits[1] = ~a.bits[1];
    result.bits[2] = ~a.bits[2];
    return result;
}

s21_decimal bit_or(s21_decimal a, s21_decimal b) {
    s21_decimal result;
    result.bits[0] = a.bits[0] | b.bits[0];
    result.bits[1] = a.bits[1] | b.bits[1];
    result.bits[2] = a.bits[2] | b.bits[2];
    return result;
}

void shift_l_one(s21_decimal *a) {
    int b1_tmp = get_bit(*a, 31);
    a->bits[0] <<= 1;

    int b2_tmp = get_bit(*a, 63);
    a->bits[1] <<= 1;
    if (b1_tmp) set_bit_1(a, 32);

    a->bits[2] <<= 1;
    if (b2_tmp) set_bit_1(a, 64);
}

void shift_l(s21_decimal *a, int n) {
    while (n--) shift_l_one(a);
}

void shift_r_one(s21_decimal *a) {
    int b1_tmp = get_bit(*a, 64);
    a->bits[2] >>= 1;

    int b2_tmp = get_bit(*a, 32);
    a->bits[1] >>= 1;
    if (b1_tmp) set_bit_1(a, 63);

    a->bits[0] >>= 1;
    if (b2_tmp) set_bit_1(a, 31);
}

void shift_r(s21_decimal *a, int n) {
    while (n--) shift_r_one(a);
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

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

// void print_bits(s21_decimal d) {
//     for (int i = 0; i < 3; i++) {
//         int x = 3;
//         for (int j = 0; j < 32; j++) {
//             printf("%u", IS_SET(d.bits[i], j));
//             if (j == x && !(i == 2 && j == 31)) {
//                 x += 4;
//                 printf(" ");
//             }
//         }
//     }
//     printf("\n");
// }