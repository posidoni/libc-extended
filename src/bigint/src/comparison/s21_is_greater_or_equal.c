#include "../s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
    return s21_is_equal(a, b) || s21_is_greater(a, b);
}
