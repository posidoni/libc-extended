#ifndef S21_INT128_HELPERS_
#define S21_INT128_HELPERS_

#include "s21_decimal.h"

// int128 manipulation
s21_decimal bigint_to_decimal(__int128_t src);
s21_decimal ll_to_decimal(long long val);
long long get_random_ll(void);
__int128_t int128_pow(int val, int exp);
short int get_random_short(void);

#endif  // S21_INT128_HELPERS_
