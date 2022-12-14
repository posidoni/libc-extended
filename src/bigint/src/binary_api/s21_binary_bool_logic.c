#include "s21_decimal.h"

s21_decimal bit_xor(s21_decimal a, s21_decimal b) {
    s21_decimal result = {0};
    result.bits[0] = a.bits[0] ^ b.bits[0];
    result.bits[1] = a.bits[1] ^ b.bits[1];
    result.bits[2] = a.bits[2] ^ b.bits[2];
    return result;
}

s21_decimal bit_lxor(s21_decimal a, s21_decimal b) {
    s21_decimal result = {0};
    result.bits[0] = a.bits[0] ^ b.bits[0];
    result.bits[1] = a.bits[1] ^ b.bits[1];
    result.bits[2] = a.bits[2] ^ b.bits[2];
    result.bits[3] = a.bits[3] ^ b.bits[3];
    return result;
}

s21_decimal bit_and(s21_decimal a, s21_decimal b) {
    s21_decimal result = {0};
    result.bits[0] = a.bits[0] & b.bits[0];
    result.bits[1] = a.bits[1] & b.bits[1];
    result.bits[2] = a.bits[2] & b.bits[2];
    return result;
}

s21_decimal bit_land(s21_decimal a, s21_decimal b) {
    s21_decimal result = {0};
    result.bits[0] = a.bits[0] & b.bits[0];
    result.bits[1] = a.bits[1] & b.bits[1];
    result.bits[2] = a.bits[2] & b.bits[2];
    result.bits[3] = a.bits[3] & b.bits[3];
    return result;
}

s21_decimal bit_not(s21_decimal a) {
    s21_decimal result = {0};
    result.bits[0] = ~a.bits[0];
    result.bits[1] = ~a.bits[1];
    result.bits[2] = ~a.bits[2];
    return result;
}
