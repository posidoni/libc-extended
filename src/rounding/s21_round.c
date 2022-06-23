#include "../s21_decimal.h"

/* #define DEBUG */
/* #ifdef DEBUG */
/* #include "../tests/s21_decimal_test.h" */
/* #endif */

/**
 * @brief Rounds a value same as math.h round()
 * Implemented by truncating a value
 * 4134.4141 becomes 4134
 * Getting the remainder after subtraction
 * 4134.4141 - 4134 = 0.4141
 * comapring with 0.4141 >= 0.5 ? 0.4141 : 1
 *
 * @param value is a variable that will be rounded
 * @param result is the varible that gets the result
 * @return retuns to success or failure code
 */

int s21_round(s21_decimal value, s21_decimal *result) {
    memset(result, 0, sizeof(*result));

    /* Working with positive always, set sign later */
    int sign = get_sign(value);
    set_sign_pos(&value);

    s21_decimal truncated = {0};
    s21_truncate(value, &truncated);

#ifdef DEBUG
    printf("value = ");
    print_bits_r(value);
    printf("truncated = ");
    print_bits_r(truncated);
#endif

    s21_decimal fraction = {0};
    s21_mod(value, truncated, &fraction);

#ifdef DEBUG
    printf("fraction= ");
    print_bits_r(fraction);
#endif

    s21_decimal half = {{5}};
    set_exponent(&half, 1);

    int err = 0;
    if (s21_is_greater_or_equal(fraction, half)) {
        s21_decimal one = {{1}};
        *result = binary_addition(truncated, one, &err);
    } else {
        *result = truncated;
    }

    if (err)
        return CONVERTATION_ERROR;

    set_sign(result, sign);
    return CONVERTATION_OK;
}
