#include "s21_core.h"

// s21_decimal binary_division(s21_decimal value_1, s21_decimal value_2, int *code) {
//     s21_decimal result = {0};
//     if (s21_is_equal(value_2, get_power_of_ten(0))) {
//         result = value_1;
//     } else {
//         for (int i = 95 - byte_len(value_2); i >= 0; --i) {
//             if (s21_is_less_or_equal(shiftnl_ret(value_2, i), value_1)) {
//                 value_1 = binary_subtraction(value_1, shiftnl_ret(value_2, i), code);
//                 result = bit_or(result, shiftnl_ret(get_power_of_ten(0), i));
//             }
//         }
//     }
//     return result;
// }

void s21_decimal_apply_exponent(s21_decimal *dec) {
    /* TODO: add code checking & respective logic */
    int code = 0;
    int expon = get_exponent(*dec);
    *dec = binary_division(*dec, get_power_of_ten(expon), &code);
}

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
        if (IS_SET(decimal.bits[3], i))
            ADD_BIT(exponent, j);
    }

    if (exponent > 28) {
        fprintf(stderr, "VERY BIG EXPONENT (0 - 28): exp = %d\n", exponent);
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
    } else {
        // TODO: Replace with a system function call
        fprintf(stderr, "VERY BIG EXPONENT (0 - 28): exp = %d\n", new_exponent);
    }
}