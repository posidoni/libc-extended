#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    float integral;
    float fractional = modf(src, &integral);
    set_exponent(dst, 6);
}
