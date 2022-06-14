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
    for (int i = 0; i < strlen(bits); i++)
        if (bits[i] - '0')
            ADD_BIT(result->bits[2 - i / 32], (i % 32));

    s21_decimal temp = *result;
    while (!shiftl(&temp)) {
        shiftl(result);
        temp = *result;
    }
}

// float add_exponent(float val, int exp) {
//     while (exp--)
//         val *= 10.0F;
//     return val;
// }
