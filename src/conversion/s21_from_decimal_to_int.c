#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    if (!get_exponent(src) && dst) {
        *dst = 0;
        for (size_t i = 0, j = sizeof(int) * 4 - 1; i < sizeof(int) * 4; i++, j--) {
            if (IS_SET(src.bits[0], j)) {
                SET_BIT(*dst, 1, i);
            }
        }

        /* Checks the sign of INPUT decimal & sets the sign bit of int */
        SET_BIT(*dst, get_sign(src), (sizeof(int) * 4 - 1));
    } else {
        int exp = get_exponent(src);

        s21_decimal src_no_exp = {0};
        set_exponent(&src_no_exp, 0);

        while (exp) {
            // BINARY DIV HERE
            exp--;
        }

        s21_from_decimal_to_int(src_no_exp, dst);
    }

    return ARITHMETIC_OK;
}