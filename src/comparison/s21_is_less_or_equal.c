#include "../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
    return s21_is_equal(a, b) || s21_is_less(a, b);
}

int s21_is_less_or_equal_abs(s21_decimal a, s21_decimal b) {
    set_sign_pos(&a);
    set_sign_pos(&b);
    return s21_is_equal_abs(a, b) || s21_is_less_abs(a, b);
}
