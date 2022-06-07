#include "../s21_decimal.h"
#include "../tests/s21_decimal_test.h"

static bool s21_is_greater_positive(s21_decimal a, s21_decimal b);

/*
    We assume that 1 (dec) is represented like this in s21_decimal:

    000001 000000 000000 000000
    (3) 0000 (uint)
    (2) 0000 (uint)
    (1) 0000 (uint)
    (0) 0001 (uint)

    Thus, we have the right to compare raw value of unsigned ints.
*/

static bool s21_is_greater_positive(s21_decimal a, s21_decimal b) {
    for (int i = 2; i >= 0; i--) {
        printf("[%d] A: %u B: %u\n", i, a.bits[i], b.bits[i]);

        if (a.bits[i] == b.bits[i]) {
            continue;
        } else {
            return a.bits[i] > b.bits[i];
        }
    }

    return false;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
    apply_exponent_to_decimal(&a);
    apply_exponent_to_decimal(&b);

    bool both_zeroes = both_all_zeroes(a, b);
    bool res = false;
    bool sign1 = get_sign(a), sign2 = get_sign(b);

    /* NEG > NEG */
    if (sign1 && sign2) {
        set_sign_pos(&a);
        set_sign_pos(&b);
        return s21_is_less(a, b);
    }

    /* NEG > POS */
    if (sign1 && !sign2) {
        return false;
    }

    /* POS > NEG */
    if (!sign1 && sign2) {
        return true;
    }

    /* POS > POS */
    if (!both_zeroes) {
        return s21_is_greater_positive(a, b);
    }

    return both_zeroes ? false : res;
}
