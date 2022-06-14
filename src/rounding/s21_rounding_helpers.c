#include "../s21_decimal.h"

void get_bit_string(float res, char *bits) {
    for (int i = 0; res > 1e-6; i++) {
        res = floorf(res) / 2;
        if (res - floorf(res) > 1e-6)
            bits[i] = '1';
        else
            bits[i] = '0';
    }
}

void set_bits_from_string(char *bits, s21_decimal *result) {
    for (int i = strlen(bits) - 1; i >= 0; i--)
        if (bits[i] - '0')
            ADD_BIT(result->bits[i / 32], i % 32);
}

// float add_exponent(float val, int exp) {
//     while (exp--)
//         val *= 10.0F;
//     return val;
// }
