#include "../s21_decimal_test.h"

void print_mpz_binary(mpz_t mpz_val) {
    mpz_out_str(stdout, 2, mpz_val);
    puts("");
}

void print_mpz_decimal(mpz_t mpz_val) {
    mpz_out_str(stdout, 10, mpz_val);
    puts("");
}

void print_bits_no_exp(s21_decimal d) {
    int no_set = 0;

    for (int i = 0; i < 3; i++) {
        int x = 3;
        for (int j = 0; j < 32; j++) {
            if (i == 0 && !IS_SET(d.bits[0], j) && !no_set) {
                continue;
            } else if (i == 0 && IS_SET(d.bits[0], j)) {
                no_set = 1;
            }

            if (IS_SET(d.bits[i], j))
                printf("%s", HRED);
            printf("%u", IS_SET(d.bits[i], j));
            if (j == x && !(i == 2 && j == 31)) {
                x += 4;
                // printf("");
            }
            printf("%s", RESET);
        }
    }
    printf("\n");
}

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
