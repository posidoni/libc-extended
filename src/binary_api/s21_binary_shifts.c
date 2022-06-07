#include "s21_core.h"

int shiftnl(s21_decimal *a, int n) {
    bool code = 0;
    while (n--) {
        code = shiftl(a);
        if (code) break;
    }
    return code;
}

s21_decimal shiftnl_ret(s21_decimal a, int n) {
    while (n--) {
        if (shiftl(&a)) break;
    }
    return a;
}

int shiftl(s21_decimal *a) {
    int b1_tmp = get_bit(*a, 31);
    a->bits[0] <<= 1;

    int b2_tmp = get_bit(*a, 63);
    a->bits[1] <<= 1;
    if (b1_tmp) set_bit_1(a, 32);

    int is_overflow = get_bit(*a, 95);
    a->bits[2] <<= 1;
    if (b2_tmp) set_bit_1(a, 64);
    return is_overflow;
}

void shiftnr(s21_decimal *a, int n) {
    while (n--) shiftr(a);
}

s21_decimal shiftnr_ret(s21_decimal a, int n) {
    while (n--) shiftr(&a);
    return a;
}

void shiftr(s21_decimal *a) {
    int b1_tmp = get_bit(*a, 64);
    a->bits[2] >>= 1;

    int b2_tmp = get_bit(*a, 32);
    a->bits[1] >>= 1;
    if (b1_tmp) set_bit_1(a, 63);

    a->bits[0] >>= 1;
    if (b2_tmp) set_bit_1(a, 31);
}
