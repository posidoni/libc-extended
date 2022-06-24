#include "../s21_decimal.h"

void handle_exponent_mul(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result, int *code);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    memset(result, 0, sizeof(*result));
    int code = ARITHMETIC_OK;

    handle_exponent_mul(value_1, value_2, result, &code);

    if (get_sign(value_1) != get_sign(value_2)) {
        set_sign_neg(result);
        if (code == 1)
            code = 2;
    }

    return code;
}

void handle_exponent_mul(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result, int *code) {
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);
    set_exponent(&value_1, 0);
    set_exponent(&value_2, 0);

    *result = binary_multiplication(value_1, value_2, code);
    int i = 0;

    for (; i < exp_v1 + exp_v2 && *code != 0; ++i) {
        s21_int_div(i % 2 ? value_1 : value_2, get_power_of_ten(1),
                    i % 2 ? &value_1 : &value_2);
        *result = binary_multiplication(value_1, value_2, code);
    }
    if (*code == 0) {
        int flag = 0;
        while (i > 0 && *code == 0) {
            s21_decimal tmp =
                binary_multiplication(*result, get_power_of_ten(1), code);
            if (*code == 0) {
                i--;
                *result = tmp;
            } else {
                s21_int_div(flag % 2 ? value_1 : value_2, get_power_of_ten(1),
                            flag % 2 ? &value_1 : &value_2);
                flag++;
                i++;
            }
        }
        *code = 0;
        int ex = exp_v1 + exp_v2 - i;
        set_exponent(result, ex == 0 ? 0 : ex + 1);
    }
}
