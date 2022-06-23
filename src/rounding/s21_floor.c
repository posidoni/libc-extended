#include "../s21_decimal.h"

/**
 * @brief Round down the given number
 * Simply truncated the number (will discard zeroes)
 * (exp = 7) 51351.5315153 becomes 51351
 * Then multiply by the pow(10, exponent)
 * (exp = 7) 51351 becomes 51351.0000000
 *
 * For negatives we add one (
 * i.e -1321.14121 becomes -1322.00000
 * )
 *
 * @param value given value
 * @param result truncated value
 * @return returns an error code
 */

int s21_floor(s21_decimal value, s21_decimal *result) {
    memset(result, 0, sizeof(*result));

    int sign = get_sign(value);
    set_sign_pos(&value);

    s21_decimal truncated = {0};
    s21_truncate(value, &truncated);

    /* Round down for negative numbers -12.321351 becomes -13.00000 */
    if (sign == NEG && get_exponent(value)) {
        /* check if there is a fraction before round down */
        s21_decimal zero = {0};
        s21_decimal fraction = {0};

        s21_sub(value, truncated, &fraction);
        int is_zero_fraction = s21_is_equal(fraction, zero);

        if (!is_zero_fraction) {
            /* i.e -420.00 - 1 = -421.00*/
            int code = 0;
            s21_decimal one = {{1}};
            truncated = binary_addition(truncated, one, &code);

            if (code)
                return CONVERTATION_ERROR;
        }
    }

    *result = truncated;

    set_sign(result, sign);

    return CONVERTATION_OK;
}
