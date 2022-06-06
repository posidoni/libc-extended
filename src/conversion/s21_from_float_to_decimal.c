#include "../s21_decimal.h"
#include <float.h>
/* #define DEBUG */

static int get_float_exponent(float val) {
    int exp = 0;
    while (val > 1) {
        val /= 10;
        exp++;
    }
    return exp;
}

static void get_bit_string(float src, char bits[static 1]) {
    for (int i = 0; src > 1e-6; i++) {
        src = floor(src) / 2;
        if (src - floor(src) > 1e-6)
            bits[i] = '1';
        else
            bits[i] = '0';
    }

#ifdef DEBUG
    printf("bits string=");
    puts(bits);
#endif
}

static void str_to_set_bits(s21_decimal *dst, char bits[static 1]) {
    for (int i = strlen(bits) - 1; i >= 0; i--)
        if (bits[i] - '0')
            ADD_BIT(dst->bits[i / 32], i % 32);
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    if (!isnormal(src))
        return CONVERTATION_ERROR;
    if (src > MAX_DECIMAL || src < MIN_DECIMAL)
        return CONVERTATION_ERROR;

    /* handle sign */
    if (signbit(src)) {
        src = -src;
        set_sign_neg(dst);
    }
    /* handle left part */

    char bits[96] = {'\0'};
    get_bit_string(src, bits);

    if (strlen(bits) > 96)
        return CONVERTATION_ERROR;

    str_to_set_bits(dst, bits);

    /* set exponent */
    int exp = get_float_exponent(src);
    set_exponent(dst, exp);

    /* handle right part */
    float right = (src - floor(src)) * pow(10, D_MAX_EXP_VAL - exp);
    unsigned idx = strlen(bits) - 1;
    memset(bits, '\0', 96);
    get_bit_string(right, bits);

    for (unsigned i = 0, j = idx; i < strlen(bits) && j < 96; i++, j++) {
        if (bits[i] - '0')
            ADD_BIT(dst->bits[j / 32], j % 32);
    }

#ifdef DEBUG
    printf("right=%f\n", right);
#endif
    return CONVERTATION_OK;
}
