#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int sign = get_sign(src);
    if (!dst)
        return CONVERTATION_ERROR;

    if (sign)
        *dst *= -1;
    return CONVERTATION_OK;
}
