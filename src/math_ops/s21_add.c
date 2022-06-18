#include "../s21_decimal.h"
#include "../tests/s21_decimal_test.h"
#include <stdio.h>

static void handle_exponent_add(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result, int *code);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int code = ARITHMETIC_OK;

    int s1 = get_sign(value_1), s2 = get_sign(value_2);

    if (s1 == POS && s2 == POS) {
        handle_exponent_add(value_1, value_2, result, &code);
    } else if (s1 == POS && s2 == NEG) {
        set_sign_pos(&value_2);
        code = s21_sub(value_1, value_2, result);
    } else if (s1 == NEG && s2 == POS) {
        set_sign_pos(&value_1);
        code = s21_sub(value_2, value_1, result);
    } else if (s1 == NEG && s2 == NEG) {
        set_sign_pos(&value_1);
        set_sign_pos(&value_2);
        handle_exponent_add(value_1, value_2, result, &code);
        set_sign_neg(result);
    }

    code = s21_check_infinity(code, get_sign(*result));


//     // At this point decimals have equal exponent,
//     // because it was normalized by s21_normalize_exponent
    if (code && get_exponent(value_1) && get_exponent(value_2)) {


#define DEBUG
#ifdef DEBUG
        printf(RED "\tBank rounding\n" ENDCOLOR);
        float a1, a2, b1, b2;

        s21_from_decimal_to_float(value_1, &a1);
        s21_from_decimal_to_float(value_2, &b1);

        printf(RED "Before round: %f \n" ENDCOLOR, a1);
        printf(RED "Before round: %f \n" ENDCOLOR, b1);
#endif

        s21_bank_rounding(&value_1, 1);
        s21_bank_rounding(&value_2, 1);

#ifdef DEBUG
        s21_from_decimal_to_float(value_1, &a2);
        s21_from_decimal_to_float(value_2, &b2);
        printf(GRN "After round:  %f \n" ENDCOLOR, a2);
        printf(GRN "After round:  %f \n" ENDCOLOR, b2);
#endif

        code = s21_add(value_1, value_2, result);
    }

    return code;
}

static void handle_exponent_add(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result, int *code) {
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);

    if (exp_v2 > exp_v1)
        s21_swap(&value_1, &value_2);
    int res_exp = min(exp_v1, exp_v2);

    s21_decimal value_2_origin = value_2;

    s21_normalize_decimal_pair(&value_1, &value_2, code);

    /* ADDITION OPERATION */
    if (*code == S21_INFINITY) {
        /* Bank rounding happens when we fail to normalize compounds */
        if (s21_is_greater_or_equal(value_1, get_05())) {
            /* +1 */
            *result = binary_addition(value_2, get_power_of_ten(0), code);
        } else {
            /* +0 (leave as it was) */
            *result = value_2_origin;
            *code = 0;
        }
    } else {
        /* Normal addition with normalized exponents */
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
