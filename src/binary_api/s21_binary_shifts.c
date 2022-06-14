/**
 * @file s21_binary_shifts.c
 * @author Andrey Jhelannikov
 * @brief All binary shifts.
 * - ✅ All team members are familiar with used abstractions.
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 */

#include "../s21_decimal.h"

/**
 * @brief Shift N times to the left
 * @warning while shifting to the left overflow may happen, as this
 * operation is equivalent to pow(a, 2) n times.
 */

// int shiftnl(s21_decimal *a, int n) {
//     bool code = 0;
//     while (n--) {
//         code = shiftl(a);
//         if (code) break;
//     }
//     return code;
// }

// s21_decimal shiftnl_ret(s21_decimal a, int n) {
//     while (n--) {
//         if (shiftl(&a)) break;
//     }
//     return a;
// }

int shiftl(s21_decimal *a) {
    // Check if the 31th bit is set
    int b1_tmp = get_bit(*a, 31);
    a->bits[0] <<= 1;

    int b2_tmp = get_bit(*a, 63);
    a->bits[1] <<= 1;
    // binary shift to the left makes last bit equal to zero (because this is pow(a, 2))
    // b1_tmp - remembered sign
    if (b1_tmp) set_bit_1(a, 32);

    int is_overflow = get_bit(*a, 95);
    a->bits[2] <<= 1;

    if (b2_tmp) set_bit_1(a, 64);

    return (is_overflow);
}

/**
 * @brief Shift N times to the right. Overflow is not possible while
 * shifting to the right, because this is log(a, 2);
 */

void shiftr(s21_decimal *a) {
    int b1_tmp = get_bit(*a, 64);
    a->bits[2] >>= 1;
    set_bit_0(a, 95);

    int b2_tmp = get_bit(*a, 32);
    a->bits[1] >>= 1;
    set_bit_0(a, 63);
    if (b1_tmp) set_bit_1(a, 63);

    a->bits[0] >>= 1;

    set_bit_0(a, 31);

    if (b2_tmp) set_bit_1(a, 31);
}

// void shiftnr(s21_decimal *a, int n) {
//     while (n--) shiftr(a);
// }

// s21_decimal shiftnr_ret(s21_decimal a, int n) {
//     while (n--) shiftr(&a);
//     return a;
// }
