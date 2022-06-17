#include "../s21_decimal.h"

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
    int second_is_even = (n / 10) % 2;

    if (rem > 5 || (rem == 5 && second_is_even)) {
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
    int code = 0;

    while (times > 0) {
        int old_exp = get_exponent(*dec);
        set_exponent(dec, 0);
        s21_decimal remainder = s21_integer_mod(*dec, get_power_of_ten(2));
        set_exponent(dec, old_exp - 1);
        s21_decimal new_value = s21_integer_div(*dec, get_power_of_ten(1), &new_value);

        /* Interesting mask trick by Vlad. Remainder in mod(a, 100) can never be more than 100 */
        int mask = (127 & remainder.bits[0]);

        if (bank_rounding(mask)) {
            *dec = binary_addition(*dec, get_power_of_ten(0), &code);
        }
    }
}
