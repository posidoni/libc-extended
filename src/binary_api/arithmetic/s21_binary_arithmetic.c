#include "../../s21_decimal.h"

/**
    1. Init
    1:  0110 1011
    2:  0001 1010
    C:  0000 0000

    2. BIT AND (посмотреть где случается переполнение)
    1:     0110 1011
    2:     0001 1010
    C:     0000 1010

    3. SHIFT L CARRY (сдвигаем, чтобы смочь прибавить переполненные единицы.
   Запомнили переполнение. Здесь может произойти оверфлоу, тк нам не хватит
   места) C:     0001 0100

    4. BIT XOR. (V1, V2) (кор реально прибавляет два числа, обнуляя
   переполнение) 1:     0110 1011 2:     0001 1010 New 1: 0111 0001

    5. Если Керри не ноль (если еще есть что прибавлять), то продолжаем цикл
 */

s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2,
                            int *err) {
    s21_decimal carry = {0};

    s21_decimal origin_1 = value_1;
    s21_decimal origin_2 = value_2;

    while (!eq_zero(value_2)) {
        memset(&carry, 0, sizeof(s21_decimal));
        carry = bit_and(value_1, value_2);
        *err = shiftl(&carry);
        value_1 = bit_xor(value_1, value_2);

        value_2 = carry;

        if (*err)
            break;
    }

    if (*err && get_exponent(origin_1) > 0 && get_exponent(origin_2) > 0) {
        s21_bank_rounding(&origin_1, 1);
        s21_bank_rounding(&origin_2, 1);

        return binary_addition(origin_1, origin_2, err);
    }

    return value_1;
}

s21_decimal binary_subtraction(s21_decimal value_1, s21_decimal value_2,
                               int *err) {
    s21_decimal carry = {0};

    s21_decimal origin_1 = value_1;
    s21_decimal origin_2 = value_2;

    value_2 = binary_addition(bit_not(value_2), get_power_of_ten(0), err);

    while (!eq_zero(value_2)) {
        memset(&carry, 0, sizeof(s21_decimal));
        carry = bit_and(value_1, value_2);
        *err = shiftl(&carry);
        value_1 = bit_xor(value_1, value_2);

        value_2 = carry;

        if (*err)
            break;
    }

    // if (*err && get_exponent(origin_1) > 0 && get_exponent(origin_2) > 0) {
    //     s21_bank_rounding(&origin_1, 1);
    //     s21_bank_rounding(&origin_2, 1);
    //     *err = 0;

    //     return binary_subtraction(origin_1, origin_2, err);
    // }

    return value_1;
}

s21_decimal binary_multiplication(s21_decimal value_1, s21_decimal value_2,
                                  int *err) {
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
