#include "../s21_decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
    bool res = false;
    if (get_sign(a) < get_sign(b)) {
        res = true;
    } else if (get_sign(a) == get_sign(b)) {
        if (get_exponent(a) > get_exponent(a)) {
            res = true;
        } else if (get_exponent(a) == get_exponent(b)) {
            if (a.bits[2] < b.bits[2]) {
                res = true;
            } else if (a.bits[2] == b.bits[2]) {
                if (a.bits[1] < b.bits[1]) {
                    res = true;
                } else if (a.bits[1] == b.bits[1]) {
                    /* Comparison of low bits */
                    res = a.bits[0] < b.bits[0];
                } else {
                    res = false;
                }
            } else {
                res = false;
            }
        } else {
            res = false;
        }
    } else {
        res = false;
    }
    return res;
}
