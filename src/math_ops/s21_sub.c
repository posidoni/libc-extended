#include <stdio.h>

#include "../s21_decimal.h"
#include "../tests/s21_decimal_test.h"

static void s21_sub_handle_signs(int s1, int s2, s21_decimal value_1, s21_decimal value_2,
                                 s21_decimal *result, int *code);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    memset(result, 0, sizeof(*result));
    int code = ARITHMETIC_OK;

    s21_normalize_decimal_pair(&value_1, &value_2, &code);

    int s1 = get_sign(value_1), s2 = get_sign(value_2);

    s21_sub_handle_signs(s1, s2, value_1, value_2, result, &code);

    // if (code && get_exponent(value_1) && get_exponent(value_2)) {
    //     s21_bank_rounding(&value_1, 1);
    //     s21_bank_rounding(&value_2, 1);

    //     code = s21_sub(value_1, value_2, result);

    //     code = 0;
    //     // set_sign(&value_1, s1);
    //     // set_sign(&value_2, s2);

    set_exponent(result, get_exponent(value_1));

    return s21_check_infinity(code, get_sign(*result));
}

static void s21_sub_handle_signs(int s1, int s2, s21_decimal value_1, s21_decimal value_2,
                                 s21_decimal *result, int *code) {
    if (s1 == POS && s2 == POS) {
        if (s21_is_greater(value_1, value_2)) {
            *result = binary_subtraction(value_1, value_2, code);
        } else {
            *result = binary_subtraction(value_2, value_1, code);
            set_sign_neg(result);
        }
    } else if (s1 == POS && s2 == NEG) {
        *result = binary_addition(value_1, value_2, code);
    } else if (s1 == NEG && s2 == POS) {
        set_sign_pos(&value_1);
        *result = binary_addition(value_1, value_2, code);
        set_sign_neg(result);
    } else if (s1 == NEG && s2 == NEG) {
        set_sign_pos(&value_1);
        set_sign_pos(&value_2);

        if (s21_is_greater(value_1, value_2)) {
            *result = binary_subtraction(value_1, value_2, code);
            set_sign_neg(result);
        } else {
            *result = binary_subtraction(value_2, value_1, code);
        }
    }
}
