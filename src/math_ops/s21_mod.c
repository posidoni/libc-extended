#include <stdio.h>

#include "../s21_decimal.h"
#include "s21_dec_math.h"

static s21_decimal s21_integer_mod_private(s21_decimal dividend, s21_decimal divisor);

void handle_exponent_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int *code);

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    memset(result, 0, sizeof(*result));

    if (eq_zero(value_2))
        return S21_NAN;

    int code = 0;

    int exp = max(get_exponent(value_1), get_exponent(value_2));
    (void) s21_normalize(&value_1, &value_2);

    code = s21_int_mod(value_1, value_2, result);
    set_exponent(result, exp);

    return code;
}

int s21_int_mod(s21_decimal dividend, s21_decimal divisor, s21_decimal *result) {
    if (eq_zero(divisor))
        return S21_NAN;

    result->bits[0] = 1;
    result->bits[1] = 0;
    result->bits[2] = 0;
    result->bits[3] = 0;

    set_sign(result, get_sign(dividend));
    set_sign_pos(&dividend);
    set_sign_pos(&divisor);

    *result = s21_integer_mod_private(dividend, divisor);

    return ARITHMETIC_OK;
}

static s21_decimal s21_integer_mod_private(s21_decimal dividend, s21_decimal divisor) {
    s21_decimal original_divisor = divisor;
    s21_decimal res = {0};
    s21_decimal modified_dividend = {0};
    s21_decimal zero = {0};
    int code = 0;

    if (s21_is_equal(dividend, divisor)) {
        return zero;
    } else if (s21_is_less_basic(dividend, divisor)) {
        return dividend;
    }

    // Our goal is to align divisor & dividend, so we are shifting divisor to
    // the left

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

    while ((s21_is_less_basic(divisor, dividend) || s21_is_equal(divisor, dividend)) &&
           !get_bit(divisor, 95)) {
        // printf("1\n");
        shiftl(&divisor);
    }

    // Shifting (divisor) once to correctly align it with dividend
    if (s21_is_less_basic(dividend, divisor)) {
        // printf("2\n");
        shiftr(&divisor);
    }

    /**
     *  dividend: 0101010101010101
     *  divisor: 0101000000000000
     *
     *  An actial modision is done via substraction.
     *
     * @arg (modified_dividend) stores new value of (dividend) after
     * substraction. It will later be passed to the recursive call of sivision.
     */

    modified_dividend = binary_subtraction(dividend, divisor, &code);

    /**
     * @arg (original_divisor) is nesessary to modide by non-modified version of
     * divisor, because our original divisor was modified by shifting to the
     * left.
     */

    res = s21_integer_mod_private(modified_dividend, original_divisor);

    return res;
}
