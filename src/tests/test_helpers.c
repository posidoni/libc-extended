#include "s21_decimal_test.h"

void print_bits(s21_decimal d) {
    for (int i = 0; i < 3; i++) {
        int x = 3;
        for (int j = 0; j < 32; j++) {
            if (IS_SET(d.bits[i], j)) printf("%s", HRED);
            printf("%u", IS_SET(d.bits[i], j));
            if (j == x && !(i == 2 && j == 31)) {
                x += 4;
                printf(" ");
            }
            printf("%s", RESET);
        }
    }
    printf("\n");
}

void print_bits_r(s21_decimal d) {
    for (int i = 2; i >= 0; --i) {
        int x = 28;
        for (int j = 31; j >= 0; --j) {
            if (IS_SET(d.bits[i], j)) printf("%s", HRED);
            printf("%u", IS_SET(d.bits[i], j));
            if (j == x && !(i == 0 && j == 0)) {
                x -= 4;
                printf(" ");
            }
            printf("%s", RESET);
        }
    }
    printf("\n");
}