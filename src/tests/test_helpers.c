#include "s21_decimal_test.h"

int reverse_bits_int(int in) {
    int res = 0;
    int i = 0, j = 15;

    while (i < 16) {
        SET_BIT(res, IS_SET(in, j), i);
        i++;
        j--;
    }

    return res;
}

s21_decimal convert_gmp_to_decimal(mpz_t input) {
    s21_decimal res = {0};
    mpz_export(res.bits, 0, 1, sizeof(res.bits[0]), -1, 0, input);
    return res;
}

int get_rand(int min, int max) {
    int val = (int)rand() % 2;
    return min + val * (max - min);
}

int s21_get_random_decimal_and_npz_copy(s21_decimal *in, mpz_t *in_npz_copy) {
    /* TODO: Decimal has sign, but mpz doesn't...can't convert mpz when negative
     */
    /* if (rand() % 2) { */
    if (0) {
        set_sign_neg(in);
    } else {
        set_sign_pos(in);
    }

    char npz_bin_str[1024] = {'\0'};

    for (int j = 0, m = 0; j < 3; j++) {
        for (int i = 0; i < 32; i++) {
            unsigned int bit = (rand() % 2);

            if (bit) {
                ADD_BIT(in->bits[j], i);
                npz_bin_str[m] = '1';
            } else {
                npz_bin_str[m] = '0';
            }
            m++;
        }
    }

    /* Normalizes our */
    for (int j = 0; j < 3; j++)
        in->bits[j] = reverse_bits_u32(in->bits[j]);

    /* TODO: Changes needed */
    int exp = 0;  // get_rand(0, 0);
    set_exponent(in, exp);

    mpz_init(*in_npz_copy);
    mpz_set_si(*in_npz_copy, 0);
    int flag = mpz_set_str(*in_npz_copy, npz_bin_str, 2);

/* #define DEBUG */
#if defined(DEBUG)
    printf("EXPONENT WAS: %d\n", exp);
    printf("LINE: %d IN %s\n", __LINE__, __FILE__);
    mpz_out_str(stdout, 10, *in_npz_copy);
    printf("\n");
#endif

    /* FIXME: this breaks everythig */
    s21_apply_exponent_to_npz(in_npz_copy, exp);

#if defined(DEBUG)
    printf("LINE: %d IN %s\n", __LINE__, __FILE__);
    mpz_out_str(stdout, 10, *in_npz_copy);
    printf("\n");
#endif

    return flag;
}

unsigned int reverse_bits_u32(unsigned int n) {
    unsigned int res = 0;
    for (int i = 0; i < 32; i++) {
        res = res << 1;
        res = res | (n & 1);

        n = n >> 1;
    }

    return res;
}

void s21_apply_exponent_to_npz(mpz_t *src, int exp) {
    mpz_t mpz_ten_const;
    mpz_init(mpz_ten_const);
    mpz_set_si(mpz_ten_const, 10);

    while (exp) {
        mpz_fdiv_q(*src, *src, mpz_ten_const);
        exp--;
    }

    mpz_clear(mpz_ten_const);
}

void print_bits(s21_decimal d) {
    for (int i = 0; i < 3; i++) {
        int x = 3;
        for (int j = 0; j < 32; j++) {
            if (IS_SET(d.bits[i], j))
                printf("%s", HRED);
            printf("%u", IS_SET(d.bits[i], j));
            if (j == x && !(i == 2 && j == 31)) {
                x += 4;
                printf("");
            }
            printf("%s", RESET);
        }
    }
    printf("\n");
}

s21_decimal get_random_int_decimal(void) {
    s21_decimal res;

    set_exponent(&res, 0);

    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 31; i++) {
            SET_BIT(res.bits[j], (rand() % 2), i);
        }
    }

    return res;
}

void print_bits_r(s21_decimal d) {
    for (int i = 2; i >= 0; --i) {
        int x = 28;
        for (int j = 31; j >= 0; --j) {
            if (IS_SET(d.bits[i], j))
                printf("%s", HRED);
            printf("%u", IS_SET(d.bits[i], j));
            if (j == x && !(i == 0 && j == 0)) {
                x -= 4;
                printf("");
            }
            printf("%s", RESET);
        }
    }
    printf("\n");
}

void print_bits_r_set(s21_decimal d, int set_n) {
    int x = 28;
    for (int j = 15; j >= 0; --j) {
        if (IS_SET(d.bits[set_n], j))
            printf("%s", HRED);
        printf("%u", IS_SET(d.bits[set_n], j));
        if (j == x && !(set_n == 0 && j == 0)) {
            x -= 4;
            printf("");
        }
        printf("%s", RESET);
    }

    printf("\n");
}

void print_bits_set(s21_decimal d, int set_n) {
    int x = 28;
    for (int j = 0; j < 16; ++j) {
        if (IS_SET(d.bits[set_n], j))
            printf("%s", HRED);
        printf("%u", IS_SET(d.bits[set_n], j));
        if (j == x && !(set_n == 0 && j == 0)) {
            x -= 4;
            printf("");
        }
        printf("%s", RESET);
    }

    printf("\n");
}
