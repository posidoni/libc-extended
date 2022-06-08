#include "../s21_decimal.h"

void handle_exponent_add(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result, int *code);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int code = ARITHMETIC_OK;

    if (get_sign(value_1) == 0 && get_sign(value_2) == 0) {
        handle_exponent_add(value_1, value_2, result, &code);
    } else if (get_sign(value_1) == 0 && get_sign(value_2) == 1) {
        s21_sub(value_1, value_2, result);
    } else if (get_sign(value_1) == 1 && get_sign(value_2) == 0) {
        s21_sub(value_2, value_1, result);
    } else if (get_sign(value_1) == 1 && get_sign(value_2) == 1) {
        handle_exponent_add(value_1, value_2, result, &code);
        set_sign_neg(result);
    }

    code = code == 1 ? get_sign(*result) ? S21_NEGATIVE_INFINITY : S21_INFINITY
                     : 0;

    return code;
}

void handle_exponent_add(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result, int *code) {
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);
    if (exp_v2 > exp_v1)
        s21_swap(&value_1, &value_2);
    int res_exp = min(exp_v1, exp_v2);

    s21_decimal value_2_origin = value_2;

    s21_decimal power_of_ten =
        get_power_of_ten(abs(exp_v1 - exp_v2) > 0 ? 1 : 0);

    s21_decimal value_2_check_overflow;
    for (int i = 0; i < abs(exp_v1 - exp_v2); i++) {
        value_2_check_overflow =
            binary_multiplication(value_2, power_of_ten, code);
        if (*code == 1)
            break;
        set_exponent(&value_1, get_exponent(value_1) - 1);
        res_exp++;
        value_2 = value_2_check_overflow;
    }
    if (*code == 1) {
        if (s21_is_greater_or_equal(value_1, get_05()))
            *result = binary_addition(value_2, get_power_of_ten(0), code);
        else
            *result = value_2_origin;
        *code = 1;
    } else {
        *result = binary_addition(value_1, value_2, code);
    }
    set_exponent(result, res_exp);
}
