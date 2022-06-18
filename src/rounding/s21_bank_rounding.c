#include "../s21_decimal.h"
#include "../tests/s21_decimal_test.h"
#include <stdio.h>

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
 * @param dec - Target of bank rounding.
 * @param times - Times the rounding is applied.
 * Each time it will decrement the exponent and eat 1 digit.
 */

void s21_bank_rounding(s21_decimal *dec, int times) {
    int sign = get_sign(*dec);
    set_sign_pos(dec);
    s21_decimal copy = *dec;

    while (times > 0) {
        int old_exp = get_exponent(*dec);
        set_exponent(dec, 0);
        s21_decimal remainder = s21_integer_mod(copy, get_power_of_ten(2));
        set_exponent(dec, old_exp - 1);

        set_exponent(dec, 0);
        s21_decimal new_value = {0};

        // s21_div(copy, get_power_of_ten(1), &new_value);
        // new_value = s21_integer_div(copy, get_power_of_ten(2), &new_value); does not work probably
        
        set_exponent(dec, old_exp - 1);

        set_exponent(&copy, 0);
        set_exponent(&new_value, 0);

        s21_div(copy, get_power_of_ten(1), &new_value);

        *dec = new_value; // decimal is divided by 10

        set_exponent(dec, old_exp - 1);

        /* Interesting mask trick by Vlad. Remainder in mod(a, 100) can never be more than 100 */
        int mask = (127 & remainder.bits[0]);

        if (bank_rounding(mask)) {
            s21_decimal one = get_power_of_ten(0);
            set_exponent(&one, old_exp - 1);

            s21_decimal tmp = {0};

            (void)s21_add(*dec, one, &tmp);

            *dec = tmp;

        }
        times--;
    }

    set_sign(dec, sign);
}
