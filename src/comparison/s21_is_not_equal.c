#include "../s21_decimal.h"

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
    return !s21_is_equal(a, b);
}

// int s21_is_not_equal_abs(s21_decimal a, s21_decimal b) {
//     return !s21_is_equal_abs(a, b);
// }
