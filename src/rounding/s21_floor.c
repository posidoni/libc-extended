#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    memset(result, 0, sizeof(*result));
    float res = 0;
    double exp = get_exponent(value);
    s21_from_decimal_to_float(value, &res);

#ifdef DEBUG
    printf("before=%f\n", res);
#endif

    res = floorf(res);

#ifdef DEBUG
    printf("after=%f\n", res);
#endif

    res = res > 0 ? res : -res;

    /* NOTE: this is a try to make exponent work (doesn't work, loses precision)
     */
    /* res = add_exponent(res, get_exponent(value)); */
    /* printf("after add_exponent=%f\n", res); */

    get_sign(value) ? set_sign_neg(result) : set_sign_pos(result);

    /* handle left part */
    char bits[96] = {'\0'};
    get_bit_string(res, bits);

    /* set the bits from string */
    set_bits_from_string(bits, result);

    /* NOTE: this doesn't work (always give 0 back) */
    s21_decimal tmp = {0};
    s21_mul(*result, get_power_of_ten(exp), &tmp);

    *result = tmp;
    set_exponent(result, exp);

    return CONVERTATION_OK;
}
