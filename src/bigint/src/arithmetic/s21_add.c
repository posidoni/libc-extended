#include "s21_decimal.h"

int s21_normalize(s21_decimal *value_1, s21_decimal *value_2);

void handle_exponent_add(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result, int *code);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    memset(result, 0, sizeof(*result));
    int code = ARITHMETIC_OK;
    int s1 = get_sign(value_1);
    int s2 = get_sign(value_2);
    set_sign_pos(&value_1);
    set_sign_pos(&value_2);
    if (s1 == POS && s2 == POS) {
        handle_exponent_add(value_1, value_2, result, &code);
    } else if (s1 == POS && s2 == NEG) {
        if (s21_is_greater(value_1, value_2)) {
            code = s21_sub(value_1, value_2, result);
        } else {
            code = s21_sub(value_2, value_1, result);
            set_sign_neg(result);
        }
    } else if (s1 == NEG && s2 == POS) {
        if (s21_is_greater(value_1, value_2)) {
            code = s21_sub(value_1, value_2, result);
            set_sign_neg(result);
        } else {
            code = s21_sub(value_2, value_1, result);
            set_sign_pos(result);
        }
    } else if (s1 == NEG && s2 == NEG) {
        handle_exponent_add(value_1, value_2, result, &code);
        set_sign_neg(result);
        if (code == 1)
            code = 2;
    }
    return code;
}

void handle_exponent_add(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result, int *code) {
    int exp = s21_normalize(&value_1, &value_2);
    *result = binary_addition(value_1, value_2, code);
    set_exponent(result, exp);
}
