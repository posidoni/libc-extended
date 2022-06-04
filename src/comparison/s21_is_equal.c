#include "../s21_decimal.h"

static bool both_all_zeroes(s21_decimal a, s21_decimal b);

bool bits_eq(const unsigned int bits_a[3], const unsigned int bits_b[3]) {
    return bits_a[0] == bits_b[0] && bits_a[1] == bits_b[1] &&
           bits_a[2] == bits_b[2];
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
    bool info = a.bits[3] == b.bits[3];
    return (both_all_zeroes(a, b)) ? true : info && bits_eq(a.bits, b.bits);
}

static bool both_all_zeroes(s21_decimal a, s21_decimal b) {
    int res = true;
    
    for (int i = 0; i < 3 && res; i++) {
        for (int j = 0; j < 32; j++) {
            if (IS_SET(a.bits[i], j) || IS_SET(a.bits[i], j)) {
                res = false;
                break;
            }
        }
    }

    return res;
}
