#include "../s21_decimal.h"

static int get_float_exponent(float val) {
    int exponent = 0;
    while (val >= 1) {
        val /= 10;
        exponent++;
    }
    return !exponent ? 1 : exponent;
}

/* NOTE: this works, make sure to set the exponent if testing using online calc
*/



/*

    I SUPPOSE THAT THE BUG IS THAT WE THINK 11.123123123123 to much for our decimal,
    because we did not apply bank rounding

*/


int s21_from_float_to_decimal(float src, s21_decimal *dst) {

    // I suspect that defines are not correct. Please, double check them. I guess, there is a problem with floating point + 28 more digits
    // #define MAX_DECIMAL 7.92281625143e+28
    // #define MIN_DECIMAL -7.92281625143e+28

    if (!isnormal(src))
        return CONVERTATION_ERROR;
    if (src > MAX_DECIMAL || src < MIN_DECIMAL)
        return CONVERTATION_ERROR;

    bool is_negative = 0;
    if (signbit(src)) {
        src = -src;
        is_negative = 1;
    }

    /* get exponent */
    int exponent = get_float_exponent(src);

    char bits[128] = {'\0'};
    get_bit_string(src, bits, exponent);
    set_bits_from_string(bits, dst);

    /* set sign */
    if (is_negative)
        set_sign_neg(dst);

    /* set exponent */
    set_exponent(dst, D_MAX_EXP_VAL - exponent);

    return CONVERTATION_OK;
}

// typedef union {
//     int ui;
//     float fl;
// } floatbits;

// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//     dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
//     dst->value_type = s21_NORMAL_VALUE;
//     int result = FALSE, sign = getFloatSign(&src), exp = getFloatExp(&src);

//     if (isinf(src) && !sign)
//         dst->value_type = s21_INFINITY;
//     else if (isinf(src) && sign)
//         dst->value_type = s21_NEGATIVE_INFINITY;
//     else if (isnan(src))
//         dst->value_type = s21_NAN;

//     if (dst && dst->value_type == s21_NORMAL_VALUE && src != 0) {
//         double temp = (double)fabs(src);
//         int off = 0;
//         for (; off < 28 && (int)temp / (int)pow(2, 21) == 0; temp *= 10, off++) {
//         }
//         temp = round(temp);
//         if (off <= 28 && (exp > -94 && exp < 96)) {
//             floatbits mant;
//             temp = (float)temp;
//             for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {
//             }
//             mant.fl = temp;
//             exp = getFloatExp(&mant.fl);
//             dst->bits[exp / 32] |= 1 << exp % 32;
//             for (int i = exp - 1, j = 22; j >= 0; i--, j--)
//                 if ((mant.ui & (1 << j)) != 0) dst->bits[i / 32] |= 1 << i % 32;
//             dst->bits[3] = (sign << 31) | (off << 16);
//             result = TRUE;
//         }
//     }
//     return result;
// }
