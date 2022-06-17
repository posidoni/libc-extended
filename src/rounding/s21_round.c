#include "../s21_decimal.h"

#ifdef DEBUG
#include "../tests/s21_decimal_test.h"
#endif

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

#ifdef DEBUG
    printf("value = ");
    print_bits_r(value);
    printf("truncated = ");
    print_bits_r(truncated);
#endif

    s21_decimal mul_by_10 = value;
    set_exponent(&mul_by_10, exponent - 1);
    s21_decimal truncated_mul10 = {0};
    s21_truncate(mul_by_10, &truncated_mul10);

#ifdef DEBUG
    printf("truncated_mul10= ");
    print_bits_r(truncated_mul10);
#endif

    s21_decimal rem = {0};
    s21_mod(truncated_mul10, get_power_of_ten(1), &rem);

#ifdef DEBUG
    printf("rem = ");
    print_bits_r(rem);
#endif

    s21_decimal rounded = {0};
    int code = ARITHMETIC_OK;

    /* +1 or leave it as it was*/

    int bank_rounding = 0;
    s21_from_decimal_to_int(rem, &bank_rounding);

#ifdef DEBUG
    printf("bank_round = %d\n", bank_rounding);
#endif

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
