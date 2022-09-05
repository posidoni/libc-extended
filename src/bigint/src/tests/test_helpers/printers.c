#include "s21_decimal_test.h"

void print_bits_r(s21_decimal d) {
    for (int i = 3; i >= 0; --i) {
        if (i == 2)
            printf(" ");
        int x = 28;
        for (int j = 31; j >= 0; --j) {
            if (IS_SET(d.bits[i], j))
                printf("%s", HRED);
            printf("%u", IS_SET(d.bits[i], j));
            if (j == x && !(i == 0 && j == 0)) {
                x -= 4;
                // printf("");
            }
            printf("%s", RESET);
        }
    }
    printf("\n");
}

void print_string(char *src, s21_decimal d) {
    for (int i = 3; i >= 0; --i) {
        if (i == 2)
            sprintf(src++, " ");
        int x = 28;
        for (int j = 31; j >= 0; --j) {
            sprintf(src++, "%c", '0' + IS_SET(d.bits[i], j));
            if (j == x && !(i == 0 && j == 0)) {
                x -= 4;
            }
        }
    }
}

void print_python(s21_decimal dec) {
    char dec1[50000] = {0};
    print_string(dec1, dec);
    char cmd[90000] = {0};
    sprintf(cmd, "echo  \"%s\"  | python3 stepa.py", dec1);
    system(cmd);
    // float a = 0;
    // s21_from_decimal_to_float(dec, &a);
    // printf("\t\tC Float:\t%.28f\n", a);
}
