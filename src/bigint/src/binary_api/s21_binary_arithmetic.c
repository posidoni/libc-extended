#include "s21_decimal.h"

/**
    1. Init
    1:  0110 1011
    2:  0001 1010
    C:  0000 0000

    2. BIT AND
    1:     0110 1011
    2:     0001 1010
    C:     0000 1010

    3. SHIFT L CARRY
   C:     0001 0100

    4. BIT XOR.
   1:     0110 1011 2:     0001 1010 New 1: 0111 0001

    5. If Carry is not 0 yet, loop again
 */

s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2,
                            int *err) {
    *err = ARITHMETIC_OK;
    s21_decimal carry = {0};

    while (!eq_zero(value_2)) {
        memset(&carry, 0, sizeof(s21_decimal));
        carry = bit_and(value_1, value_2);
        *err = shiftl(&carry);
        value_1 = bit_xor(value_1, value_2);

        value_2 = carry;

        if (*err)
            break;
    }

    return value_1;
}

s21_decimal binary_subtraction(s21_decimal value_1, s21_decimal value_2,
                               int *err) {
    *err = ARITHMETIC_OK;
    value_1.bits[3] = 0;
    value_2.bits[3] = 0;
    s21_decimal carry = {0};

    value_2 = binary_addition(bit_not(value_2), get_power_of_ten(0), err);

    while (!eq_zerol(value_2)) {
        memset(&carry, 0, sizeof(s21_decimal));
        carry = bit_land(value_1, value_2);
        lshiftl(&carry);
        value_1 = bit_lxor(value_1, value_2);
        value_2 = carry;
    }

    value_1.bits[3] = 0;
    return value_1;
}

s21_decimal binary_multiplication(s21_decimal value_1, s21_decimal value_2,
                                  int *err) {
    *err = ARITHMETIC_OK;
    s21_decimal result = {0};
    while (!eq_zero(value_2) && !(*err)) {
        if (!eq_zero(bit_and(value_2, get_power_of_ten(0)))) {
            result = binary_addition(result, value_1, err);
            if (*err)
                break;
        }

        *err = shiftl(&value_1);
        shiftr(&value_2);
    }
    return result;
}
