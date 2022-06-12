#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    memset(result, 0, sizeof(*result));
    int exp = get_exponent(value);

    return CONVERTATION_OK;
}
