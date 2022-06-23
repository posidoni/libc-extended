#include "../s21_decimal.h"
#include "../tests/s21_decimal_test.h"
void handle_exponent_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int *code);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    memset(result, 0, sizeof(*result));
    int code = ARITHMETIC_OK;
    int s1 = get_sign(value_1);
    int s2 = get_sign(value_2);
    set_sign_pos(&value_1);
    set_sign_pos(&value_2);
    if (s1 == POS && s2 == POS) {
        if (s21_is_greater(value_1, value_2)) {
            handle_exponent_sub(value_1, value_2, result, &code);
        } else {
            handle_exponent_sub(value_2, value_1, result, &code);
            set_sign_neg(result);
        }
    } else if (s1 == POS && s2 == NEG) {
        code = s21_add(value_1, value_2, result);
    } else if (s1 == NEG && s2 == POS) {
        code = s21_add(value_1, value_2, result);
        set_sign_neg(result);
        if (code == 1)
            code = 2;
    } else if (s1 == NEG && s2 == NEG) {
        if (s21_is_greater(value_1, value_2)) {
            handle_exponent_sub(value_1, value_2, result, &code);
            set_sign_neg(result);
        } else {
            handle_exponent_sub(value_2, value_1, result, &code);
        }
    }
    return code;
}

void handle_exponent_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int *code) {
    int exp = s21_normalize(&value_1, &value_2);
    *result = binary_subtraction(value_1, value_2, code);
    set_exponent(result, exp);
}