#include "s21_decimal.h"

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
    int sign = get_sign(value);
    memset(result, 0, sizeof(*result));
    int never_error = 0;

    const s21_decimal one = get_power_of_ten(0);
    const s21_decimal zero = {0};
    s21_decimal mod_res = {0};

    s21_mod(value, one, &mod_res);
    s21_truncate(value, result);

    if (get_sign(value) && s21_is_not_equal(value, zero) &&
        s21_is_not_equal(mod_res, zero)) {
        *result = binary_addition(*result, one, &never_error);
    }

    set_sign(result, sign);

    return CONVERTATION_OK;
}
