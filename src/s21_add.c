#include "s21_decimal.h"

s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2);
void handle_exponent(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_decimal get_power_of_ten(int pow);
s21_decimal binary_substraction(s21_decimal value_1, s21_decimal value_2);
s21_decimal binary_multiplication(s21_decimal value_1, s21_decimal value_2);
#define DEBUG

#ifdef DEBUG
void print_bits(s21_decimal d);
#endif

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (get_sign(value_1) == get_sign(value_2)) {
        handle_exponent(value_1, value_2, result);
    } else {
        // s21_sub(value_1, value_2, result);
    }
}

void handle_exponent(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);
    s21_decimal power_of_ten = get_power_of_ten(abs(exp_v1 - exp_v2));
    if (exp_v1 > exp_v2) {
        value_2 = binary_multiplication(value_2, power_of_ten);
        *result = binary_addition(value_2, value_1);
    } else {
        value_1 = binary_multiplication(value_1, power_of_ten);
        *result = binary_addition(value_2, value_1);
    }
    set_exponent(result, max(exp_v1, exp_v2));
}

s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal carry;
    while (!eq_zero(value_2)) {
        init_zero(&carry);
        carry = bit_and(value_1, value_2);
        shift_l_one(&carry);
        value_1 = bit_xor(value_1, value_2);
        value_2 = carry;
    }
    return value_1;
}

s21_decimal binary_substraction(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal carry;
    value_2 = binary_addition(bit_not(value_2), get_power_of_ten(0));
    while (!eq_zero(value_2)) {
        init_zero(&carry);
        carry = bit_and(value_1, value_2);
        shift_l_one(&carry);
        value_1 = bit_xor(value_1, value_2);
        value_2 = carry;
    }
    return value_1;
}

s21_decimal binary_multiplication(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal result;
    init_zero(&result);
    while (!eq_zero(value_2)) {
        if (!eq_zero(bit_and(value_2, get_power_of_ten(0)))) {
            result = binary_addition(result, value_1);
        }
        shift_l_one(&value_1);
        shift_r_one(&value_2);
    }
    return result;
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

int eq_zero(s21_decimal value) { return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0); }
