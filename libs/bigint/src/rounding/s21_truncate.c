#include "../s21_decimal.h"

/**
 * @brief Truncates a floating point number and discards the floating part
 * (i.e 4.513513515 becomes 4)
 * Implemented by simply dividing our large number by the power of 10
 * (i.e exponent = 1, 110110110 (182)
 *               ---------
 *                    1010 (10)
 *               =========
 *                   10010 (18)
 * )
 *
 * @param value Given value to truncate
 * @param result Truncated value
 * @return Error code is returned
 */

int s21_truncate(s21_decimal value, s21_decimal *result) {
    memset(result, 0, sizeof(*result));

    int sign = get_sign(value);
    int exponent = get_exponent(value);
    set_sign_pos(&value);

    /* set sign & exponent to 0 for future division */
    value.bits[3] = 0;

    if (!exponent) {
        *result = value;
    } else {
        while (exponent--) {
            if (s21_div(value, get_power_of_ten(1), result))
                return CONVERTATION_ERROR;
            value = *result;
        }
    }

    set_sign(result, sign);

    return CONVERTATION_OK;
}
