#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    s21_decimal truncated = {0};

    int code = s21_truncate(src, &truncated);

    int sign = get_sign(src);

    if (!dst || code == CONVERTATION_ERROR)
        return CONVERTATION_ERROR;

    if (get_bit(truncated, 31) || truncated.bits[1] || truncated.bits[2])
        return CONVERTATION_ERROR;

    int tmp = 0;

    for (int i = 0; i < 31; i++)
        tmp += pow(2, i) * get_bit(truncated, i);

    if (tmp == INT_MIN && sign)
        return CONVERTATION_ERROR;

    if (sign)
        tmp = -tmp;

    *dst = tmp;

    return CONVERTATION_OK;
}
