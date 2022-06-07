#include "../s21_decimal.h"
#include "../tests/s21_decimal_test.h"

static bool s21_is_less_positive(s21_decimal a, s21_decimal b);

/*
    We assume that 1 (dec) is represented like this in s21_decimal:

    000001 000000 000000 000000
    (3) 0000 (uint)
    (2) 0000 (uint)
    (1) 0000 (uint)
    (0) 0001 (uint)

    Thus, we have the right to compare raw value of unsigned ints.
*/

static bool s21_is_less_positive(s21_decimal a, s21_decimal b) {
    // printf("BEFORE division: \n");
    // print_bits_r(a);
    // print_bits_r(b);

    /*
    (!) GET RID OF EXPONENT!

        1. Compare exponents
            if equal => start bit-by-bit comparison.

        2. If exponent A is bigger => A is smaller than B
        2. If exponent B is bigger => B is smaller than A

    */

    // s21_decimal_apply_exponent(&a);
    // s21_decimal_apply_exponent(&b);

    /* printf("FINAL SHIT\n"); */
    print_bits_r(a);
    print_bits_r(b);

    for (int i = 2; i >= 0; i--) {
        /* printf("[%d] A: %u B: %u\n", i, a.bits[i], b.bits[i]); */

        if (a.bits[i] == b.bits[i]) {
            continue;
        } else {
            return a.bits[i] < b.bits[i];
        }
    }

    return false;
}

int s21_is_less(s21_decimal a, s21_decimal b) {
    apply_exponent_to_decimal(&a);
    apply_exponent_to_decimal(&b);

    bool both_zeroes = both_all_zeroes(a, b);
    bool res = false;
    bool sign1 = get_sign(a), sign2 = get_sign(b);

    /* NEG < NEG */
    if (sign1 && sign2) {
        // set_sign_pos(&a);
        // set_sign_pos(&b);

        SET_BIT(a.bits[3], 1, 31);
        SET_BIT(b.bits[3], 1, 31);

        return s21_is_greater(a, b);
    }

    /* NEG < POS */
    if (sign1 && !sign2) {
        return true;
    }

    /* POS < NEG */
    if (!sign1 && sign2) {
        return false;
    }

    /* POS < POS */
    if (!both_zeroes && !sign1 && !sign2) {
        int res = s21_is_less_positive(a, b);
        return res;
    }

    return both_zeroes;
}
