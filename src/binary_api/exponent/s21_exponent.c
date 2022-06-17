#include "../../s21_decimal.h"

/**
 * @brief Normalizes pair of two decimals. To normalize => match their
 * exponent. This is done via multiplication by 10 of decimal with the
 * smallest exponent.
 *
 * In case of overflow the flag is raised.
 *
 * @param [a, b] - pair of decimals that need to be normalized to the same
 * exponent
 */

void s21_normalize_decimal_pair(s21_decimal *a, s21_decimal *b, int *overflow) {
    int e1 = get_exponent(*a), e2 = get_exponent(*b);
    int cur_exp = min(e1, e2);
    int target_exp = max(e1, e2);

    s21_decimal cur = (e1 < e2) ? *a : *b;

    while (cur_exp != target_exp && !(*overflow)) {
        cur = binary_multiplication(cur, get_power_of_ten(1), overflow);
        cur_exp++;
        set_exponent(&cur, cur_exp);
    }

    if (e1 < e2)
        *a = cur;
    else
        *b = cur;
}

s21_decimal get_power_of_ten(int pow) {
    s21_decimal result = {0};
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
            set_sign_neg(decimal);
        SET_BIT(decimal->bits[3], new_exponent, D_START_EXP);
    }
}
