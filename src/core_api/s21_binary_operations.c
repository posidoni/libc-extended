#include "s21_core.h"

s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2, int *err) {
    s21_decimal carry;
    while (!eq_zero(value_2)) {
        init_zero(&carry);
        carry = bit_and(value_1, value_2);
        *err = shiftl(&carry);
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
        *err = shiftl(&carry);
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
        *err = shiftl(&value_1);
        shiftr(&value_2);
    }
    return result;
}
s21_decimal binary_division(s21_decimal value_1, s21_decimal value_2, int *code) {
    s21_decimal result = {0};
    if (s21_is_equal(value_2, get_power_of_ten(0))) {
        result = value_1;
    } else {
        for (int i = 95 - byte_len(value_2); i >= 0; --i) {
            if (s21_is_less_or_equal(shiftnl_ret(value_2, i), value_1)) {
                value_1 = binary_subtraction(value_1, shiftnl_ret(value_2, i), code);
                result = bit_or(result, shiftnl_ret(get_power_of_ten(0), i));
            }
        }
    }
    return result;
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

int shiftnl(s21_decimal *a, int n) {
    bool code = 0;
    while (n--) {
        code = shiftl(a);
        if (code) break;
    }
    return code;
}

s21_decimal shiftnl_ret(s21_decimal a, int n) {
    while (n--) {
        if (shiftl(&a)) break;
    }
    return a;
}

int shiftl(s21_decimal *a) {
    int b1_tmp = get_bit(*a, 31);
    a->bits[0] <<= 1;

    int b2_tmp = get_bit(*a, 63);
    a->bits[1] <<= 1;
    if (b1_tmp) set_bit_1(a, 32);

    int is_overflow = get_bit(*a, 95);
    a->bits[2] <<= 1;
    if (b2_tmp) set_bit_1(a, 64);
    return is_overflow;
}

void shiftnr(s21_decimal *a, int n) {
    while (n--) shiftr(a);
}

s21_decimal shiftnr_ret(s21_decimal a, int n) {
    while (n--) shiftr(&a);
    return a;
}

void shiftr(s21_decimal *a) {
    int b1_tmp = get_bit(*a, 64);
    a->bits[2] >>= 1;

    int b2_tmp = get_bit(*a, 32);
    a->bits[1] >>= 1;
    if (b1_tmp) set_bit_1(a, 63);

    a->bits[0] >>= 1;
    if (b2_tmp) set_bit_1(a, 31);
}
