#include "../s21_decimal.h"

int s21_normalize(s21_decimal *value_1, s21_decimal *value_2) {
    int e1 = get_exponent(*value_1);
    int e2 = get_exponent(*value_2);
    set_exponent(value_1, 0);
    set_exponent(value_2, 0);

    s21_decimal big = e1 > e2 ? *value_2 : *value_1;
    int e_big = min(e1, e2);
    s21_decimal small = e1 > e2 ? *value_1 : *value_2;
    int e_small = max(e1, e2);

    int of_check = 0;
    s21_decimal big_overflow = big;
    while (e_big < e_small) {
        big_overflow = binary_multiplication(big_overflow, get_power_of_ten(1), &of_check);
        if (of_check)
            break;
        e_big++;
        big = big_overflow;
    }

    while (e_big < e_small) {
        s21_decimal ten = get_power_of_ten(1);
        s21_decimal last = {0};
        s21_decimal before_last = {0};
        s21_int_mod(small, ten, &last);
        s21_int_div(small, ten, &before_last);
        s21_int_mod(before_last, ten, &before_last);

        int ilast, ibefore_last;
        s21_from_decimal_to_int(last, &ilast);
        s21_from_decimal_to_int(before_last, &ibefore_last);
        int never_error = 0;
        s21_int_div(small, ten, &small);
        if (ilast < 5) {
        } else if (ilast == 5) {
            if (ibefore_last % 2 == 1) {
                small = binary_addition(small, get_power_of_ten(0), &never_error);
            }
        } else if (ilast > 5) {
            small = binary_addition(small, get_power_of_ten(0), &never_error);
        }
        e_small--;
    }
    set_exponent(value_1, e_small);
    set_exponent(value_2, e_small);
    if (e1 > e2) {
        *value_2 = big;
        *value_1 = small;
    } else {
        *value_2 = small;
        *value_1 = big;
    }

    return e_small;
}
