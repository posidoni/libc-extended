#include "s21_decimal.h"

void get_bit_string(long double res, char *bits, int exponent) {
    res *= powl((long double)10, (long double)(D_MAX_EXP_VAL - exponent));

    for (int i = 0; res > 1e-6; i++) {
        res = floorl(res) / 2;
        if (res - floorl(res) > 1e-6)
            bits[i] = '1';
        else
            bits[i] = '0';
    }
}

void set_bits_from_string(char *bits, s21_decimal *result) {
    for (size_t i = strlen(bits) - 1; i < strlen(bits); i--)
        if (bits[i] - '0')
            ADD_BIT(result->bits[i / 32], (i % 32));
}
