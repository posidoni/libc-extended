#include "../s21_decimal_test.h"

/**
 * @brief Returns random signed decimal of specified size with exponent in range
 * [min; max].
 *
 * @param size - size array of bits (1,3)
 * @param exp - max exp (0....exp)
 *
 * @return s21_decimal
 */

s21_decimal get_random_decimal(int size, int exp) {
    s21_decimal res = {0};
    set_exponent(&res, get_rand(0, exp));

    set_random_sign(&res);

    for (int j = 0; j < size; j++) {
        for (int i = 31; i > 0; i--) {
            unsigned int x = rand() % 2;
            SET_BIT(res.bits[j], x, i);
        }
    }

    return res;
}

int get_rand(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void set_random_sign(s21_decimal *dec) {
    if (rand() % 2)
        set_sign_neg(dec);
    else
        set_sign_pos(dec);
}

float get_random_float(float min, float max) {
    assert(max > min);
    float random = ((float)rand()) / (float)RAND_MAX;
    float range = max - min;
    return random * range + min;
}
