#include "../s21_decimal.h"

static int get_float_exponent(float val) {
    int exponent = 0;
    while (val >= 1) {
        val /= 10;
        exponent++;
    }
    return !exponent ? 1 : exponent;
}

/* NOTE: this works, make sure to set the exponent if testing using online calc
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    if (!isnormal(src))
        return CONVERTATION_ERROR;
    if (src > MAX_DECIMAL || src < MIN_DECIMAL)
        return CONVERTATION_ERROR;

    bool is_negative = 0;
    if (signbit(src)) {
        src = -src;
        is_negative = 1;
    }

    /* get exponent */
    int exponent = get_float_exponent(src);

    char bits[128] = {'\0'};
    get_bit_string(src, bits, exponent);
    set_bits_from_string(bits, dst);

    /* set sign */
    if (is_negative)
        set_sign_neg(dst);

    /* set exponent */
    set_exponent(dst, D_MAX_EXP_VAL - exponent);

    return CONVERTATION_OK;
}
