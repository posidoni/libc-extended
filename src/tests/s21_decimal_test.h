#ifndef SRC_TESTS_S21_DECIMAL_TEST_H_
#define SRC_TESTS_S21_DECIMAL_TEST_H_

#include <assert.h>
#include <check.h>
#include <float.h>
#include <stdio.h>
#include <time.h>

#include "../s21_decimal.h"
#include "helpers/printers.h"
#include "helpers/s21_int128_helpers.h"

void apply_exponent_to_decimal(s21_decimal *dec);

void print_python(s21_decimal dec);

// helpers
int get_rand(int min, int max);
void set_random_sign(s21_decimal *dec);
float get_random_float(float min, float max);
s21_decimal get_random_decimal(int size, int exp);

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
