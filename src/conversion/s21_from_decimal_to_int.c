#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int sign = get_sign(src);
    if (!dst)
        return CONVERTATION_ERROR;

    int exp = get_exponent(src);

    float tmp = 0;
    for (int i = 0; i < 96; i++)
        tmp += pow(2, i) * get_bit(src, i);

    while (exp--)
        tmp /= 10;

    if (sign)
        tmp *= -1.0F;

    if (tmp > INT_MAX || tmp < INT_MIN)
        return CONVERTATION_ERROR;

    *dst = tmp;

    return CONVERTATION_OK;
}
