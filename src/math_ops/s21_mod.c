#include "../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int code = ARITHMETIC_OK;

    // probably not working 0 tests
    s21_decimal div;
    s21_decimal mul;
    code = s21_div(value_1, value_2, &div);
    s21_mul(value_2, div, &mul);
    s21_sub(value_1, mul, result);

    return code;
}
