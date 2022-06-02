#include "../s21_decimal.h"

int byte_len(s21_decimal n);
void handle_exponent_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int *code);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int code = ARITHMETIC_OK;

    handle_exponent_div(value_1, value_2, result, &code);

    if (get_sign(value_1) != get_sign(value_2)) set_sign_neg(result);

    return code;
}

void handle_exponent_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int *code) {
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);
    set_exponent(&value_1, 0);
    set_exponent(&value_2, 0);

    int res_exp = exp_v1 - exp_v2;

    *result = binary_division(value_1, value_2, code);

    while (res_exp < 0) {
        *result = binary_multiplication(*result, get_power_of_ten(1), code);
        res_exp++;
    }

    set_exponent(result, res_exp);
}

s21_decimal binary_division(s21_decimal value_1, s21_decimal value_2, int *code) {
    if (s21_is_equal(value_2, get_power_of_ten(0))) return value_1;

    s21_decimal result = {0};
    for (int i = 95 - byte_len(value_2); i >= 0; --i) {
        if (s21_is_less_or_equal(shiftnl_ret(value_2, i), value_1)) {
            value_1 = binary_subtraction(value_1, shiftnl_ret(value_2, i), code);
            result = bit_or(result, shiftnl_ret(get_power_of_ten(0), i));
        }
    }
    return result;
}

int byte_len(s21_decimal n) {
    int pos;
    for (pos = 95; pos >= 0; --pos) {
        if (get_bit(n, pos)) break;
    }
    return pos;
}
