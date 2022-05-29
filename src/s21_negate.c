#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];

    if (value.bits[3] >> 31) {
        ZERO_BIT(result->bits[3], 31);
    } else {
        ADD_BIT(result->bits[3], 31);
    }
    return CONVERTATION_OK;
}
