#include "../s21_decimal_test.h"

int get_random_pair(s21_decimal *in, mpz_t *in_mpz_copy, int size) {
    /* NOTE: Negatives disabled for now */

    if (rand() % 2)
        set_sign_neg(in);
    else
        set_sign_pos(in);

    char mpz_bin_str[96] = {0};
    for (int j = 0, m = 0; j < size; j++)
        for (int i = 0; i < 32; i++, m++) {
            if (rand() % 2) {
                ADD_BIT(in->bits[j], i);
                mpz_bin_str[m] = '1';
            } else {
                ZERO_BIT(in->bits[j], i);
                mpz_bin_str[m] = '0';
            }
        }

    for (int j = 0; j < 3; j++)
        in->bits[j] = reverse_bits(in->bits[j]);

    /* TODO: Changes needed */
    int exp = get_rand(0, 28);
    set_exponent(in, exp);

    bool res = mpz_set_str(*in_mpz_copy, mpz_bin_str, 2);

/* #define DEBUG */
#if defined(DEBUG)
    printf("%s", HRED);
    printf("EXPONENT WAS: %d\n", exp);
    printf("LINE: %d IN %s\n", __LINE__, __FILE__);
    mpz_out_str(stdout, 10, *in_mpz_copy);
    printf("\n");
#endif

    apply_exponent_to_mpz(in_mpz_copy, exp);

#if defined(DEBUG)
    printf("LINE: %d IN %s\n", __LINE__, __FILE__);
    mpz_out_str(stdout, 10, *in_mpz_copy);
    printf("\n");
    printf("%s", RESET);
#endif

    if (get_sign(*in))
        mpz_neg(*in_mpz_copy, *in_mpz_copy);

    return res;
}

void apply_exponent_to_mpz(mpz_t *src, int exp) {
    mpz_t mpz_ten_const;
    mpz_init(mpz_ten_const);
    mpz_set_ui(mpz_ten_const, 10);

    while (exp) {
        mpz_fdiv_q(*src, *src, mpz_ten_const);
        exp--;
    }

    mpz_clear(mpz_ten_const);
}

s21_decimal get_random_int_decimal(void) {
    s21_decimal res = {0};

    if (rand() % 2)
        set_sign_neg(&res);
    else
        set_sign_pos(&res);

    for (int j = 0; j < 1; j++) {
        for (int i = 31; i > 0; i--) {
            unsigned int x = rand() % 2;
            SET_BIT(res.bits[0], x, i);
        }
    }

    return res;
}

void print_mpz_binary(mpz_t mpz_val) {
    mpz_out_str(stdout, 2, mpz_val);
    puts("");
}
void print_mpz_decimal(mpz_t mpz_val) {
    mpz_out_str(stdout, 10, mpz_val);
    puts("");
}

void print_bits(s21_decimal d) {
    for (int i = 0; i < 4; i++) {
        if (i == 3)
            printf(" ");
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

int get_rand(int min, int max) { return (rand() % (max - min + 1)) + min; }
