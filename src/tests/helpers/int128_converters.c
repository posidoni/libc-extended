#include "../s21_decimal_test.h"

s21_decimal ll_to_decimal(long long val) {
    s21_decimal res = {0};
    if (val < 0) {
        set_sign_neg(&res);
        val = -val;
    }

    for (int i = 0; val; i++, val /= 2) {
        if (val % 2)
            ADD_BIT(res.bits[i / 32], i);
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

long long get_random_ll() {
    unsigned long long val = 0;
    for (int i = 0; i < 64; i++)
        if (rand() % 2)
            ADD_BIT(val, i);

    return val;
}
