#include "../../s21_decimal.h"

int shiftl(s21_decimal *a) {
    // Check if the 31th bit is set
    int b1_tmp = get_bit(*a, 31);
    a->bits[0] <<= 1;

    int b2_tmp = get_bit(*a, 63);
    a->bits[1] <<= 1;
    // binary shift to the left makes last bit equal to zero (because this is pow(a, 2))
    // b1_tmp - remembered sign
    if (b1_tmp)
        set_bit_1(a, 32);

    int is_overflow = get_bit(*a, 95);
    a->bits[2] <<= 1;

    if (b2_tmp)
        set_bit_1(a, 64);

    return (is_overflow);
}

int lshiftl(s21_decimal *a) {
    // Check if the 31th bit is set
    int b1_tmp = get_bit(*a, 31);
    a->bits[0] <<= 1;

    int b2_tmp = get_bit(*a, 63);
    a->bits[1] <<= 1;
    // binary shift to the left makes last bit equal to zero (because this is pow(a, 2))
    // b1_tmp - remembered sign
    if (b1_tmp)
        set_bit_1(a, 32);

    int is_overflow = get_bit(*a, 95);
    a->bits[2] <<= 1;

    if (b2_tmp)
        set_bit_1(a, 64);

    a->bits[3] <<= 1;
    if (is_overflow)
        set_bit_1(a, 96);
    return (is_overflow);
}

void shiftr(s21_decimal *a) {
    int b1_tmp = get_bit(*a, 64);
    a->bits[2] >>= 1;
    set_bit_0(a, 95);

    int b2_tmp = get_bit(*a, 32);
    a->bits[1] >>= 1;
    set_bit_0(a, 63);
    if (b1_tmp)
        set_bit_1(a, 63);

    a->bits[0] >>= 1;

    set_bit_0(a, 31);

    if (b2_tmp)
        set_bit_1(a, 31);
}
