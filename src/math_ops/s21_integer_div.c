/**
 * @file s21_integer_div.c
 * @author Mikhail Kuznetsov (mikhail.n.kuznetsov@gmail.com)
 * @brief Function s21_integer_div exists only as a helper & for testing
 * purposes. The general rule is that by default our division is with floating
 * point values.
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Copyright (c) 2022
 */

#include "../s21_decimal.h"

static s21_decimal s21_integer_div(s21_decimal dividend, s21_decimal divisor,
                                   s21_decimal *result, int *code);
static void handle_exponent_div(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result, int *code);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (eq_zero(value_2))
        return S21_NAN;

    int code = ARITHMETIC_OK;

    handle_exponent_div(value_1, value_2, result, &code);

    if (get_sign(value_1) != get_sign(value_2))
        set_sign_neg(result);

    return code;
}

static s21_decimal s21_integer_div(s21_decimal dividend, s21_decimal divisor,
                                   s21_decimal *result, int *code) {
    s21_decimal original_divisor = divisor;
    s21_decimal modified_dividend = {0};
    s21_decimal one = {1};

    if (s21_is_equal(dividend, divisor))
        return one;
    else if (s21_is_less(dividend, divisor))
        return modified_dividend;

    /* Our goal is to align divisor & dividend, so we are shifting divisor to
     * the left */

    /**
     * dividend: 0101010101010101
     * divisor: 0000000000000101 <---
     *
     * As dividend result we will get something like this:
     *
     * dividend: 0101010101010101
     * divisor: 1010000000000000 <---
     *
     * We got too far by one bit. Thus, we need to shift (divisor) to the right
     * once.
     */

    while (s21_is_less_or_equal(divisor, dividend)) {
        shiftl(&divisor);
        shiftl(result);
    }

    /* Shifting (@divisor) once to correctly align it with dividend */
    if (s21_is_less(dividend, divisor)) {
        shiftr(&divisor);
        shiftr(result);
    }

    /**
     *  dividend: 0101010101010101
     *  divisor: 0101000000000000
     *
     *  An actial division is done via substraction.
     *
     * @arg (modified_dividend) stores new value of (dividend) after
     * substraction. It will later be passed to the recursive call of sivision.
     */

    *code = s21_sub(dividend, divisor, &modified_dividend);

    /**
     * @arg (original_divisor) is nesessary to divide by non-modified version of
     * divisor, because our original divisor was modified by shifting to the
     * left.
     */

    one = s21_integer_div(modified_dividend, original_divisor, &one, code);

    /* @arg (result) accumulates result of division */
    *code = s21_add(*result, one, result);

    return *result;
}

static void handle_exponent_div(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result, int *code) {
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);

    set_exponent(&value_1, 0);
    set_exponent(&value_2, 0);

    int res_exp = exp_v1 - exp_v2;

    /* TODO add floating point division logic */

    /* 2 / 3 => 2 * 10^3 / 3 => 2000 / 3 => 666 / 10^3 => 0.66666666(6) */
    /* Last bit is rounded, i.e. 2/3 = 0.6666666666(6) => 0.66666666667 */

    /* Edge case. Division by 1 */
    if (s21_is_equal(value_2, get_power_of_ten(0))) {
        *result = value_1;
        *code = ARITHMETIC_OK;
    } else {
        /* We must set 1 bit in result, because we will move this bit in div to
         * the left */
        memset(result, 0, sizeof(s21_decimal));
        result->bits[0] = 1;

        *result = s21_integer_div(value_1, value_2, result, code);

        while (res_exp < 0) {
            *result = binary_multiplication(*result, get_power_of_ten(1), code);
            res_exp++;
        }

        set_exponent(result, res_exp);
    }
}
