#include "../s21_decimal.h"

/**
 * @brief Rounds a value same as math.h round()
 * Implemented by truncating a value
 * 4134.4141 becomes 4134
 * Getting the remainder after subtraction
 * 4134.4141 - 4134 = 0.4141
 * comapring with 0.4141 >= 0.5 ? 0.4141 : 1
 *
 * @param value is a variable that will be rounded
 * @param result is the varible that gets the result
 * @return retuns to success or failure code
 */

int s21_round(s21_decimal value, s21_decimal *result) {
    memset(result, 0, sizeof(*result));
    int never_error = 0;
    int sign = get_sign(value);
    s21_decimal one = get_power_of_ten(0);
    s21_decimal zeroDotFive = {0};
    zeroDotFive.bits[0] = 5;
    s21_decimal mod_res = {0};
    set_exponent(&zeroDotFive, 1);

    /* print_python(zeroDotFive); */
    s21_mod(value, one, &mod_res);
    /* printf("%d %d \n", get_exponent(mod_res), get_exponent(zeroDotFive)); */
    set_sign(&mod_res, POS);

    s21_truncate(value, result);

    s21_normalize(&mod_res, &zeroDotFive);

    if (s21_is_greater(mod_res, zeroDotFive) ||
        s21_is_equal(mod_res, zeroDotFive)) {
        /* print_python(mod_res); */
        /* print_python(zeroDotFive); */
        *result = binary_addition(*result, one, &never_error);
    }

    set_sign(result, sign);
    return CONVERTATION_OK;
}
