#include "../s21_decimal.h"

bool bits_eq(const unsigned int bits_a[3], const unsigned int bits_b[3]) {
    return bits_a[0] == bits_b[0] && bits_a[1] == bits_b[1] &&
           bits_a[2] == bits_b[2];
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
    bool info = a.bits[3] == b.bits[3];
    return info && bits_eq(a.bits, b.bits);
}
