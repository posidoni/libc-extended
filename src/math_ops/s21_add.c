#include "../s21_decimal.h"

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

    /*

        Что тут происходит на русском языке:
            Если у нас произошло переполнение, но у слагаемых все еще есть некоторая экспонента
            (то есть их можно округлить путем банковского округления), то мы их округляем и запускаем
            сложение еще раз

        Вопросы к Степе:
            1. Что именно делает банк раунд?
            2. Что банк раунд сделает со следующими числами:

                - 0.1323
                AB
                B > 5 - A++
                B < 5 - A
                B == 5 - A++ if !A%2 else A

                - 51.5928282823

            Банк раунд полностью убирает часть после запятой?

    */

    // if (exp_1 > 0 && exp_2 > 0 && additional_bit) {
        // bank_round(&value_1, 1);
        // bank_round(&value_2, 1);
    // res = very_stupid_add(value_1, value_2, result, get_exponent(value_1),
    //                       get_exponent(value_2));

    // ((additional_bit 2^97 % 10) + number % 10) % 10 -> получаем последний знак

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
