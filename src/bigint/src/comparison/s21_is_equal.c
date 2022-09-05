#include "s21_decimal.h"

static bool bits_eq(const unsigned bits_a[4], const unsigned bits_b[4]) {
    return bits_a[0] == bits_b[0] && bits_a[1] == bits_b[1] &&
           bits_a[2] == bits_b[2] && bits_a[3] == bits_b[3];
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
    return (both_all_zeroes(a, b)) || bits_eq(a.bits, b.bits);
}

bool both_all_zeroes(s21_decimal a, s21_decimal b) {
    int res = TRUE;

    for (int i = 0; i < 3 && res; i++) {
        for (int j = 0; j < 32; j++) {
            if (IS_SET(a.bits[i], j) || IS_SET(b.bits[i], j)) {
                res = FALSE;
                break;
            }
        }
    }

    return res;
}
