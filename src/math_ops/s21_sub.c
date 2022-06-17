#include "../s21_decimal.h"

static void handle_exponent_sub(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result, int *code);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int code = ARITHMETIC_OK;

    int s1 = get_sign(value_1), s2 = get_sign(value_2);

    if (s1 == POS && s2 == POS) {
        if (s21_is_greater(value_1, value_2)) {
            handle_exponent_sub(value_1, value_2, result, &code);
        } else {
            handle_exponent_sub(value_2, value_1, result, &code);
            set_sign_neg(result);
        }

    } else if (s1 == POS && s2 == NEG) {
        set_sign_pos(&value_2);
        code = s21_add(value_1, value_2, result);
    } else if (s1 == NEG && s2 == POS) {
        set_sign_pos(&value_1);
        code = s21_add(value_1, value_2, result);
        set_sign_neg(result);
    } else if (s1 == NEG && s2 == NEG) {
        set_sign_pos(&value_2);
        code = s21_add(value_1, value_2, result);
    }

    code = s21_check_infinity(code, get_sign(*result));

    return code;
}

static void handle_exponent_sub(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result, int *code) {
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);

    int res_exp = min(exp_v1, exp_v2);

    s21_decimal value_2_origin = value_2;

    s21_normalize_decimal_pair(&value_1, &value_2, code);

    if (*code == S21_INFINITY) {
        /* Bank rounding happens when we fail to normalize compounds */
        if (s21_is_greater_or_equal(value_1, get_05())) {
            /* -1 */
            *result = binary_subtraction(value_2, get_power_of_ten(0), code);
        } else {
            /* -0 - leave as it was */
            *result = value_2_origin;
        }
    } else {
        *result = binary_subtraction(value_1, value_2, code);
    }

    set_exponent(result, res_exp);
}
