#include "../s21_decimal.h"

static void handle_exponent_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int *code);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (eq_zero(value_2)) return S21_NAN;

    int code = ARITHMETIC_OK;

    /* TODO: add mod checking to determine which version of division to launch (INT) vs (FLOAT) */

    handle_exponent_div(value_1, value_2, result, &code);

    if (get_sign(value_1) != get_sign(value_2)) set_sign_neg(result);

    return code;
}

static void handle_exponent_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int *code) {
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
        /* We must set 1 bit in result, because we will move this bit in div to the left */
        init_zero(result);
        result->bits[0] = 1;

        *result = s21_integer_div(value_1, value_2, result, code);

        while (res_exp < 0) {
            *result = binary_multiplication(*result, get_power_of_ten(1), code);
            res_exp++;
        }

        set_exponent(result, res_exp);
    }
}
