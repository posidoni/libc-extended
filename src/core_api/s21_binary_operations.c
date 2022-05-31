#include "s21_core.h"

s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2, int *err) {
    s21_decimal carry;
    while (!eq_zero(value_2)) {
        init_zero(&carry);
        carry = bit_and(value_1, value_2);
        *err = shift_l_one(&carry);
        value_1 = bit_xor(value_1, value_2);
        value_2 = carry;
    }
    return value_1;
}

s21_decimal binary_subtraction(s21_decimal value_1, s21_decimal value_2, int *err) {
    s21_decimal carry;
    value_2 = binary_addition(bit_not(value_2), get_power_of_ten(0), err);
    while (!eq_zero(value_2)) {
        init_zero(&carry);
        carry = bit_and(value_1, value_2);
        *err = shift_l_one(&carry);
        value_1 = bit_xor(value_1, value_2);
        value_2 = carry;
    }
    return value_1;
}

s21_decimal binary_multiplication(s21_decimal value_1, s21_decimal value_2, int *err) {
    s21_decimal result;
    init_zero(&result);
    while (!eq_zero(value_2)) {
        if (!eq_zero(bit_and(value_2, get_power_of_ten(0)))) {
            result = binary_addition(result, value_1, err);
        }
        *err = shift_l_one(&value_1);
        shift_r_one(&value_2);
    }
    return result;
}