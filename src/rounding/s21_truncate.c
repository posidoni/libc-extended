#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    memset(result, 0, sizeof(*result));
    float res = 0;

    s21_from_decimal_to_float(value, &res);

    res = truncf(res);
    res = res > 0 ? res : -res;

    get_sign(value) ? set_sign_neg(result) : set_sign_pos(result);

    /* handle left part */
    char bits[96] = {'\0'};
    for (int i = 0; res > 1e-6; i++) {
        res = floor(res) / 2;
        if (res - floor(res) > 1e-6)
            bits[i] = '1';
        else
            bits[i] = '0';
    }

    /* set the bits from string */
    for (int i = strlen(bits) - 1; i >= 0; i--)
        if (bits[i] - '0')
            ADD_BIT(result->bits[i / 32], i % 32);

    return 0;
}
