#ifndef TEST
#define TEST

#define RED "\e[0;31m"
#define BRED "\e[1;31m"
#define URED "\e[4;31m"
#define RESET "\e[0m"
#define REDB "\e[41m"
#define REDHB "\e[0;101m"
#define HRED "\e[0;91m"
#define BHRED "\e[1;91m"

#include <check.h>
#include <float.h>
#include <stdio.h>
#include <time.h>

#include "../s21_decimal.h"
#include "gmp.h"

#define GRN "\e[0;92m"

#define PRETTY_PRINT(name) (UGRN name ENDCOLOR)
#define UGRN "\e[4;32m"
#define ENDCOLOR "\e[0m"

// (!) HACK
void tmp_normalize_exponent(s21_decimal *dec);

// decimal manipulation
s21_decimal get_random_int_decimal(void);

// gmp manipulation
s21_decimal convert_gmp_to_decimal(mpz_t input);
void convert_decimal_to_gmp(mpz_t *gmp, s21_decimal *dec);
int get_random_pair(s21_decimal *in, mpz_t *in_mpz_copy, int size);
void apply_exponent_to_mpz(mpz_t *src, int exp);

// helpers
int get_rand(int min, int max);
// debug
void print_mpz_binary(mpz_t mpz_val);
void print_mpz_decimal(mpz_t mpz_val);
void print_bits_set(s21_decimal d, int set_n);
void print_bits_r_set(s21_decimal d, int set_n);
void print_bits(s21_decimal d);
void print_bits_r(s21_decimal d);
void print_bits_no_exp(s21_decimal d);

s21_decimal get_random_decimal_size(int size, int min_exp, int max_exp);

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

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  //  TEST
