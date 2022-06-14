#ifndef SRC_TESTS_S21_DECIMAL_TEST_H_
#define SRC_TESTS_S21_DECIMAL_TEST_H_

#define RED "\033[0;31m"
#define BRED "\033[1;31m"
#define URED "\033[4;31m"
#define RESET "\033[0m"
#define REDB "\033[41m"
#define REDHB "\033[0;101m"
#define HRED "\033[0;91m"
#define BHRED "\033[1;91m"

#include <check.h>
#include <float.h>
#include <stdio.h>
#include <time.h>

#include "../s21_decimal.h"
#include "gmp.h"

#define GRN "\033[0;92m"

#define PRETTY_PRINT(name) (UGRN name ENDCOLOR)
#define UGRN "\033[4;32m"
#define ENDCOLOR "\033[0m"

// (!) HACK
void apply_exponent_to_decimal(s21_decimal *dec);

// decimal manipulation
s21_decimal get_random_decimal(int size, int exp);

s21_decimal convert_gmp_to_decimal(mpz_t input);

void convert_decimal_to_gmp(mpz_t *gmp, s21_decimal *dec);
int get_random_pair(s21_decimal *in, mpz_t *in_mpz_copy, int size);
void apply_exponent_to_mpz(mpz_t *src, int exp);
void mpz_sint_sum(mpz_t *res, int64_t compound_val);

// int128 manipulation
s21_decimal bigint_to_decimal(__int128_t src);
s21_decimal ll_to_decimal(long long val);
long long get_random_ll(void);
__int128_t int128_pow(int val, int exp);
__int128_t int128_round(int sum);

short int get_random_short(void);

/* GMP wrappers */
void gmp_sum_int(mpz_t *res, int64_t compound_val);

// helpers
int get_rand(int min, int max);
void set_random_sign(s21_decimal *dec);

// debug
void print_mpz_binary(mpz_t mpz_val);
void print_mpz_decimal(mpz_t mpz_val);
void print_bits_set(s21_decimal d, int set_n);
void print_bits_r_set(s21_decimal d, int set_n);
void print_bits(s21_decimal d);
void print_bits_r(s21_decimal d);
void print_bits_no_exp(s21_decimal d);
void debug_print_pair(s21_decimal *dec, mpz_t *big, bool exp_applied);

/* Our functions test */
Suite *suite_convert_gmp_to_decimal(void);
Suite *suite_convert_decimal_to_gmp(void);

/* Decimal function tests */
Suite *suite_s21_add(void);
Suite *suite_s21_sub(void);
Suite *suite_s21_mul(void);
Suite *suite_s21_div(void);
Suite *suite_s21_mod(void);
Suite *suite_s21_is_less(void);
Suite *suite_s21_is_less_or_equal(void);
Suite *suite_s21_is_greater(void);
Suite *suite_s21_is_greater_or_equal(void);
Suite *suite_s21_is_or_not_equal(void);
Suite *suite_s21_from_int_to_decimal(void);
Suite *suite_s21_from_float_to_decimal(void);
Suite *suite_s21_from_decimal_to_int(void);
Suite *suite_s21_from_decimal_to_float(void);
Suite *suite_s21_floor(void);
Suite *suite_s21_round(void);
Suite *suite_s21_truncate(void);
Suite *suite_s21_negate(void);
Suite *suite_s21_integer_div_wrapper(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  //  SRC_TESTS_S21_DECIMAL_TEST_H_
