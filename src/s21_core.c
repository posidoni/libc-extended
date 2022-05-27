#include "s21_core.h"

void init_decimal(s21_decimal *decimal) {
    memset(decimal, 0, sizeof(*decimal));
}

// returns 0 meaning positive 1 negative
bool get_sign(s21_decimal decimal) { return IS_SET(decimal.bits[3], D_SIGN); }
void set_sign(s21_decimal *decimal) { ADD_BIT(decimal->bits[3], D_SIGN); }

int get_exponent(s21_decimal decimal) {
    int exponent = 0;
    for (int i = D_START_EXP, j = 0; i <= D_END_EXP; i++, j++) {
        if (IS_SET(decimal.bits[3], i))
            ADD_BIT(exponent, j);
    }
    return exponent;
}

void set_exponent(s21_decimal *decimal, int new_exponent) {
    if (new_exponent <= 28) {
        short sign = IS_SET(decimal->bits[3], D_SIGN);
        decimal->bits[3] = 0;
        if (sign)
            set_sign(decimal);
        SET_BIT(decimal->bits[3], new_exponent, D_START_EXP);
    } else {
        // TODO: Replace with a system function call
        fprintf(stderr, "VERY BIG EXPONENT (0 - 28): exp = %d\n", new_exponent);
    }
}
