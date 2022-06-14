#include "../s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
    return s21_is_less(b, a);
}

// int s21_is_greater_abs(s21_decimal a, s21_decimal b) {
//     set_sign_pos(&a);
//     set_sign_pos(&b);
//     return s21_is_less(b, a);
// }
