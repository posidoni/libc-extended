#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    for (int i = 0; i < 4; i++)
        result->bits[i] = value.bits[i];

    set_sign(result, get_sign(value));

    return CONVERTATION_OK;
}
