#include "../s21_decimal.h"

static int get_float_exponent(float val) {
    int exp = 0;
    while (val > 1) {
        val /= 10;
        exp++;
    }
    return exp;
}

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

    /* handle left part */
    char bits[128] = {'\0'};
    get_bit_string(src, bits);

    if (strlen(bits) > 96)
        return CONVERTATION_ERROR;

    s21_decimal left = {0};
    set_bits_from_string(bits, &left);

    /* set exponent */
    int exp = get_float_exponent(src);

    /* handle right part */
    const int total_digits = 29;
    float fright = (src - floor(src)) * pow(10, total_digits - exp);

    memset(bits, '\0', 128);
    get_bit_string(fright, bits);

    /* remove trailing zeros */
    for (size_t i = strlen(bits) - 1; bits[i] == '0'; i--)
        bits[i] = '\0';

    s21_decimal right = {0};
    for (size_t i = 0; i < strlen(bits); i++) {
        if (bits[i] - '0')
            ADD_BIT(right.bits[i / 32], i % 32);
    }

    s21_add(left, right, dst);
    /* handle sign */
    if (is_negative)
        set_sign_neg(dst);

    /* handle exponent */
    set_exponent(dst, exp);

    return CONVERTATION_OK;
}
