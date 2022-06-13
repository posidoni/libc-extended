#include "../s21_decimal_test.h"

__int128_t int128_round(int sum) {
    __int128_t digit = sum;
    while (digit > 10)
        digit /= 10;
    if (digit >= 5)
        sum++;
    return sum;
}

__int128_t int128_pow(int val, int exp) {
    __int128_t res = 1;
    while (exp--)
        res *= val;
    return res;
}

s21_decimal ll_to_decimal(long long val) {
    s21_decimal res = {0};
    if (val < 0) {
        set_sign_neg(&res);
        val = -val;
    }

    for (uint64_t i = 0; val; i++, val /= 2) {
        if (val % 2)
            res.bits[i / 32] |= (1U << i);
    }

    return res;
}

s21_decimal bigint_to_decimal(__int128_t src) {
    s21_decimal res = {0};

    for (int i = 0, k = 0; i < 3; i++)
        for (int j = 0; j < 32; j++, k++)
            if (IS_SET(src, k))
                ADD_BIT(res.bits[i], j);

    return res;
}

long long get_random_ll(void) {
    long long int val = 0;

    for (uint64_t i = 0; i < 64; i++)
        if (rand() % 2)
            val |= (1U << i);

    return val;
}

short int get_random_short(void) {
    short int val = 0;
    for (int i = 0; i < 16; i++)
        if (rand() % 2)
            ADD_BIT(val, i);

    return val;
}
