#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int len1 = len(value.bits[0]);
    int len2 = len(value.bits[1]);
    int len3 = len(value.bits[2]);

    int exp = get_exponent(value);
    while () {
        --exp;
    }

    set_exponent(result, 0);
}

int get_digit(int n, int pos) { return (n % (int)pow(10, (pos)) / (int)pow(10, pos - 1)); }

int len(int n) {
    int res = 0;
    while (n) {
        n /= 10;
        res++;
    }
    return res;
}
