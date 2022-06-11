#include "../s21_decimal.h"

void smart_set_bit(s21_decimal *a, int pos) {
    SET_BIT(a->bits[pos / 32], 1, pos % 32);
}

int smart_get_bit(s21_decimal a, int pos) {
    return IS_SET(a.bits[pos / 32], pos % 32);
}
