#include <stdio.h>

#include "../s21_decimal.h"
#include "../tests/s21_decimal_test.h"

static int bank_rounding(int n);

/**
 * @brief Bank rounding logic. From wiki:
 * "Rather than rounding 0.5 and higher up, and 0.4 and lower down, bankers rounding rounds 0.5 to the nearest even number."
 *
 * @param n - int [0; 99], as we need 2 numbers to decide whether or not applu bank rounding
 * @return int - 1 if the rounding is applied, 0 - otherwise
 */

static int bank_rounding(int n) {
    int res = 0;

    int rem = n % 10;
    int second_is_odd = (n / 10) % 2;

    // Bank rounding applies when the second is odd. Examples: 0.95, 0.75
    // because bank rounding downs to nearest even number -> 1.00, 8.00, etc.
    // zero will be discarded. 0.5 -> 0.0

    if (rem > 5 || (rem == 5 && second_is_odd)) {
        res = 1;
    }

    return res;
}

/**
 * @brief Applies bank rounding to provided decimal. Bank rounding can never overflow a decimal,
 * if it is used correctly (i.e. if the decimal has exponent >= 1).
 *
 * @warning (@bezlant): code might seem like a mess but it really works.
 *
 * @param dec - Target of bank rounding.
 * @param times - Times the rounding is applied.
 * Each time it will decrement the exponent and eat 1 digit.
 */

void s21_bank_rounding(s21_decimal *dec, int times) {
    int code = 0;

    int sign = get_sign(*dec);
    int exp = get_exponent(*dec);
    set_sign_pos(dec);

    while (times > 0) {
        s21_decimal mod = {0}, ten = get_power_of_ten(1), hun = get_power_of_ten(2);

        s21_int_mod(*dec, hun, &mod);

        int mask = (127 & mod.bits[0]);

        s21_int_div(*dec, ten, dec);

        set_exponent(dec, exp - 1);

        if (bank_rounding(mask)) {
            // THIS BREAKS EVERYTHING (!) BINARY ADDITION IS TOO STUPID AND ASSUMS WE HAVE 0 EXP
            s21_decimal one = {1, 0, 0, 0};
            s21_decimal copy = *dec;
            *dec = binary_addition(copy, one, &code);
            set_exponent(dec, exp - 1);
        }

        times--;
    }

    set_sign(dec, sign);
}

// int bank_round(s21_decimal *a, int n) {
//     while (n--) {
//         s21_decimal mod_res = init_zero_decimal(), ten, hun;
//         s21_from_int_to_decimal(100, &hun);
//         s21_from_int_to_decimal(10, &ten);
//         stupid_mod(*a, hun, &mod_res);
//         // d_print_decimal(*a);
//         // change_endian(&mod_res);
//         int mask = 127 & mod_res.bits[0];
//         int_div(*a, ten, a);
//         int exp = get_exponent(*a) - 1;
//         set_exponent(a, exp);
//         if (bank_rounding(mask)) {
//             s21_decimal one = {1, 0, 0, 0};
//             very_stupid_add(*a, one, a, 0, 0);
//         }
//     }
//     return 0;
// }
