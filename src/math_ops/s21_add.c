#include "../s21_decimal.h"

static void handle_exponent_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int *code);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int code = ARITHMETIC_OK;

    int s1 = get_sign(value_1), s2 = get_sign(value_2);

    if (s1 == POS && s2 == POS) {
        handle_exponent_add(value_1, value_2, result, &code);
    } else if (s1 == POS && s2 == NEG) {
        /* There was a BUG that caused stack overflow */
        set_sign_pos(&value_2);
        code = s21_sub(value_1, value_2, result);
    } else if (s1 == NEG && s2 == POS) {
        set_sign_pos(&value_1);
        code = s21_sub(value_2, value_1, result);
    } else if (s1 == NEG && s2 == NEG) {
        handle_exponent_add(value_1, value_2, result, &code);
        set_sign_neg(result);
    }

    code = s21_check_infinity(code, get_sign(*result));

    return code;
}

static void handle_exponent_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int *code) {
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);

    if (exp_v2 > exp_v1) s21_swap(&value_1, &value_2);
    int res_exp = min(exp_v1, exp_v2);

    s21_decimal value_2_origin = value_2;

    if (abs(exp_v1 - exp_v2) != 0) {
        s21_decimal value_2_check_overflow = {0};

        /* NORMALIZATION OF EXPONENT */
        for (int i = 0; i < abs(exp_v1 - exp_v2) && *code != S21_INFINITY; i++) {
            value_2_check_overflow = binary_multiplication(value_2, get_power_of_ten(1), code);
            if (*code == S21_INFINITY) break;
            set_exponent(&value_1, get_exponent(value_1) - 1);
            res_exp++;
            value_2 = value_2_check_overflow;
        }
    }

    /* ADDITION OPERATION */
    if (*code == S21_INFINITY) {
        // BANK_ROUNDING_REQUIRED
        /* Bank rounding happens when we fail to normalize compounds */
        if (s21_is_greater_or_equal(value_1, get_05())) {
            /* +1 */
            *result = binary_addition(value_2, get_power_of_ten(0), code);
        } else {
            /* +0 (leave as it was) */
            *result = value_2_origin;
        }

        // Commented out, because BANK_ROUNDING situation is conventionally valid & not an overflow
        // but even here we may have an integer overflow in we sum(MAX_DEC, 1)
        // *code = S21_INFINITY;
    } else {
        /* (!) Normal addition with normalized exponents */
        *result = binary_addition(value_1, value_2, code);
    }

    set_exponent(result, res_exp);
}

int s21_check_infinity(int code, int sign) {
    int res = ARITHMETIC_OK;

    if (code == S21_INFINITY) {
        if (sign == POS)
            res = S21_INFINITY;
        else
            res = S21_NEGATIVE_INFINITY;
    }

    return res;
}
