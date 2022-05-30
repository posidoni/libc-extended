#include "../s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
    bool res = 0;
    if (get_sign(a) > get_sign(b)) {
        res = 1;
    } else if (get_sign(a) == get_sign(b)) {
        if (get_exponent(a) < get_exponent(a)) {
            res = 1;
        } else if (get_exponent(a) == get_exponent(b)) {
            if (a.bits[2] > b.bits[2]) {
                res = 1;
            } else if (a.bits[2] == b.bits[2]) {
                if (a.bits[1] > b.bits[1]) {
                    res = 1;
                } else if (a.bits[1] == b.bits[1]) {
                    res = a.bits[0] > b.bits[0];
                } else {
                    res = 0;
                }
            } else {
                res = 0;
            }
        } else {
            res = 0;
        }
    } else {
        res = 0;
    }
    return res;
}
