#include "../s21_decimal.h"

/**
 * @brief Rounds a value same as math.h round()
 * Implemented by truncating a value
 * 4134.4141 becomes 4134
 * Getting the remainder after subtraction
 * 4134.4141 - 4134
 * becomes 0.4141 Diving the resulting value (without exp) by 10
 * 4141 / 10
 * becomes 4 Added one if > 5 or keeping it as it is
 * 4141
 * Return the exponent by multipling the result by 10^exp
 * 41410000
 * Set the exponent
 * 4141.0000
 *
 *
 * @param value is a variable that will be rounded
 * @param result is the varible that gets the result
 * @return retuns to success or failure code
 */

int s21_round(s21_decimal value, s21_decimal *result) {
    memset(result, 0, sizeof(*result));

    int exponent = get_exponent(value);

    /* Working with positive always, set sign later */
    int sign = get_sign(value);
    set_sign_pos(&value);

    s21_decimal truncated = {0};
    s21_truncate(value, &truncated);

    s21_decimal rem = {0};
    s21_sub(value, truncated, &rem);
    set_exponent(&rem, 0);

    s21_decimal divided = {0};

    const s21_decimal ten = get_power_of_ten(1);

    while (s21_is_greater(rem, ten)) {
        s21_div(rem, ten, &divided);
        rem = divided;
    }

    s21_decimal rounded = {0};
    int code = ARITHMETIC_OK;

    /* +1 or leave it as it was*/

    int bank_rounding = 0;
    s21_from_decimal_to_int(divided, &bank_rounding);

    if (bank_rounding >= 5)
        code = s21_add(truncated, get_power_of_ten(0), &rounded);
    else
        rounded = truncated;

    *result = rounded;

    if (code != ARITHMETIC_OK)
        return CONVERTATION_ERROR;
    if (s21_mul(rounded, get_power_of_ten(exponent), result) != ARITHMETIC_OK)
        return CONVERTATION_ERROR;

    set_exponent(result, exponent);
    set_sign(result, sign);
    return CONVERTATION_OK;
}
