#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int sign = get_sign(src);
    if (!dst)
        return CONVERTATION_ERROR;

    int exponent = get_exponent(src);
    long double tmp = 0;

    for (int i = 0; i < 96; i++)
        tmp += pow(2, i) * get_bit(src, i);

    while (exponent--)
        tmp /= 10.0;

    if (sign)
        tmp *= -1.0;

    *dst = tmp;

    return CONVERTATION_OK;
}
