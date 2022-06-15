#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int sign = get_sign(src);
    if (!dst)
        return CONVERTATION_ERROR;

    int exponent = get_exponent(src);

    *dst = 0;
    for (int i = 0; i < 96; i++)
        *dst += pow(2, i) * get_bit(src, i);

    while (exponent--)
        *dst /= 10;

    if (sign)
        *dst *= -1.0F;

    return CONVERTATION_OK;
}
