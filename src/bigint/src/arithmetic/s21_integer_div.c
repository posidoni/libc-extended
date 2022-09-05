#include "s21_arithmetic.h"
#include "s21_decimal.h"

static s21_decimal s21_integer_div_private(s21_decimal dividend,
                                           s21_decimal divisor,
                                           s21_decimal *result);

static void handle_exponent_div(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result, int *code);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    memset(result, 0, sizeof(*result));
    if (eq_zero(value_2))
        return S21_NAN;

    int code = ARITHMETIC_OK;

    int s1 = get_sign(value_1);
    int s2 = get_sign(value_2);

    set_sign_pos(&value_1);
    set_sign_pos(&value_2);

    handle_exponent_div(value_1, value_2, result, &code);

    if (s1 != s2)
        set_sign_neg(result);

    return code;
}

int s21_int_div(s21_decimal dividend, s21_decimal divisor,
                s21_decimal *result) {
    if (eq_zero(divisor))
        return S21_NAN;
    int code = ARITHMETIC_OK;

    *result = get_power_of_ten(0);
    int s1 = get_sign(dividend), s2 = get_sign(divisor);

    set_sign_pos(&dividend);
    set_sign_pos(&divisor);

    int final_exp = get_exponent(dividend) - get_exponent(divisor);
    s21_normalize(&dividend, &divisor);
    set_exponent(&dividend, 0);
    set_exponent(&divisor, 0);

    memset(result, 0, sizeof(s21_decimal));
    result->bits[0] = 1;

    *result = s21_integer_div_private(dividend, divisor, result);

    set_exponent(result, final_exp);

    if (s1 != s2)
        set_sign_neg(result);

    return code;
}

static void handle_exponent_div(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result, int *code) {
    /* TODO add floating point division logic */

    /* 2 / 3 => 2 * 10^3 / 3 => 2000 / 3 => 666 / 10^3 => 0.66666666(6) */
    /* Last bit is rounded, i.e. 2/3 = 0.6666666666(6) => 0.66666666667 */
    s21_normalize_decimal_pair(&value_1, &value_2, code);

    /* Edge case. Division by 1 */
    if (s21_is_equal(value_2, get_power_of_ten(0))) {
        *result = value_1;
        *code = ARITHMETIC_OK;
    } else {
        /* We must set 1 bit in result, because we will move this bit in div to
         * the left */
        memset(result, 0, sizeof(s21_decimal));
        result->bits[0] = 1;

        *result = s21_integer_div_private(value_1, value_2, result);
    }
}

static s21_decimal s21_integer_div_private(s21_decimal dividend,
                                           s21_decimal divisor,
                                           s21_decimal *result) {
    s21_decimal original_divisor = divisor;
    s21_decimal modified_dividend = {0};
    s21_decimal one = {{1}};
    int unused_code = 0;

    if (s21_is_equal(dividend, divisor))
        return one;
    else if (s21_is_less_basic(dividend, divisor))
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

    while ((s21_is_less_basic(divisor, dividend) ||
            s21_is_equal(divisor, dividend)) &&
           !get_bit(divisor, 95)) {
        // printf("3\n");
        shiftl(&divisor);
        shiftl(result);
    }

    /* Shifting (@divisor) once to correctly align it with dividend */
    if (s21_is_less_basic(dividend, divisor)) {
        // printf("4\n");
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

    modified_dividend = binary_subtraction(dividend, divisor, &unused_code);

    /**
     * @arg (original_divisor) is nesessary to divide by non-modified version of
     * divisor, because our original divisor was modified by shifting to the
     * left.
     */

    one = s21_integer_div_private(modified_dividend, original_divisor, &one);

    /* @arg (result) accumulates result of division */
    *result = binary_addition(one, *result, &unused_code);

    return *result;
}
