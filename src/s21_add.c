#include "s21_decimal.h"

s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2);
handle_exponent(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
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
        //
        // s21_sub(value_1, value_2, result);
    }
}

handle_exponent(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);
    s21_decimal power_of_ten = get_power_of_ten(abs(exp_v1 - exp_v2));
    *result = value_2;
    // while (!eq_zero(value_1)) {
    value_2 = binary_multiplication(value_2, power_of_ten);
    *result = binary_addition(value_2, value_1);
    // value_1 = binary_substraction(value_1, get_power_of_ten(0));
    // }
    set_exponent(result, max(exp_v1, exp_v2));
}

s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal carry;
    while (!eq_zero(value_2)) {
        init_zero(&carry);
        bit_and(value_1, value_2, &carry);
        shift_l_one(&carry);
        bit_xor(value_1, value_2, &value_1);
        value_2 = carry;
    }
    return value_1;
}

s21_decimal binary_substraction(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal carry;
    s21_decimal not_value_2;
    init_zero(&not_value_2);
    bit_not(value_2, &not_value_2);
    value_2 = binary_addition(not_value_2, get_power_of_ten(0));
    while (!eq_zero(value_2)) {
        init_zero(&carry);
        bit_and(value_1, value_2, &carry);
        shift_l_one(&carry);
        bit_xor(value_1, value_2, &value_1);
        value_2 = carry;
    }
    return value_1;
}

s21_decimal binary_multiplication(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal result;
    init_zero(&result);
    s21_decimal bit_and_result;
    while (!eq_zero(value_2)) {
        init_zero(&bit_and_result);
        bit_and(value_2, get_power_of_ten(0), &bit_and_result);
        if (!eq_zero(bit_and_result)) {
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

// int s21_add(s21_decimal a, s21_decimal b) {
//     s21_decimal res = {0};
//     // a negative b positive
//     if (get_sign(a) && !get_sign(b)) {
//         res = s21_sub(b, a);
//         // a positive b negative
//     } else if (!get_sign(a) && get_sign(b)) {
//         res = s21_sub(a, b);
//         // both positive
//     } else {
//         res = add(a, b);
//     }
//     return res;
// }
//
// int add(s21_decimal a, s21_decimal b) {
//     // FIXES NEEDED! TURNS OUT '.' CAN BE AT ANY POSITION UP TO 28
//     s21_decimal res = {0};
//     if (!get_exponent(a) && !get_exponent(b))
//         res = add_integers(a, b);
//     else
//         res = add_floats(a, b);
//     return res;
// }
//
//// msb = most significant bit
// int check_overflow(s21_decimal val, int msb) {
//     int res = IS_SET(val.bits[0], msb);
//     return res;
// }
//
// s21_decimal add_integers(s21_decimal a, s21_decimal b) {
//     s21_decimal res = {0};
//     unsigned int *b1 = a.bits;
//     unsigned int *b2 = b.bits;
//     bool cf = false;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 32; j++) {
//             int current = cf + IS_SET(b1[i], j) + IS_SET(b2[i], j);
//             if (current == 3) {
//                 ADD_BIT(res.bits[i], j);
//                 cf = true;
//             }
//             if (current == 2) {
//                 cf = true;
//             }
//             if (current == 1) {
//                 ADD_BIT(res.bits[i], j);
//                 cf = false;
//             }
//         }
//         if (cf)
//             return S21_INFINITY;
//     }
//     return res;
// }
//
