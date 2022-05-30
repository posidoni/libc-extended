#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    return 1;
}

// {
//     int code = ARITHMETIC_OK;
//     while (value_1.bits[0] != 0) {
//         if ((value_1.bits[0] & 1) != 0) {
//             s21_add(*result, value_2, result);
//         }
//         shift_r(&value_1);
//         shift_l(&value_2);
//     }
//     return code;
// }
