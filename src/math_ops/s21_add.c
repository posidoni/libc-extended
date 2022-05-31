#include "../s21_decimal.h"

int handle_exponent(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void swap(s21_decimal *a, s21_decimal *b);

#define DEBUG

#ifdef DEBUG
void print_bits(s21_decimal d);
#endif

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int code = ARITHMETIC_OK;
    if (get_sign(value_1) == get_sign(value_2)) {
        code = handle_exponent(value_1, value_2, result);
    } else {
        // s21_sub(value_1, value_2, result);
    }
    return code;
}

int handle_exponent(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int err = ARITHMETIC_OK;
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);
    if (exp_v2 > exp_v1) swap(&value_1, &value_2);
    int res_exp = min(exp_v1, exp_v2);

    s21_decimal power_of_ten = get_power_of_ten(abs(exp_v1 - exp_v2) > 0 ? 1 : 0);
    s21_decimal value_2_check_of = value_2;

    for (int i = 0; i < abs(exp_v1 - exp_v2); i++) {
        value_2_check_of = binary_multiplication(value_2, power_of_ten, &err);
        if (err == 1) break;
        value_2 = value_2_check_of;
        res_exp++;
    }
    if (err == 1) {
        *result = binary_addition(value_2, get_power_of_ten(0), &err);
    } else {
        *result = binary_addition(value_1, value_2, &err);
    }

    set_exponent(result, res_exp);
    return err;
}

void swap(s21_decimal *a, s21_decimal *b) {
    s21_decimal tmp = *a;
    *a = *b;
    *b = tmp;
}