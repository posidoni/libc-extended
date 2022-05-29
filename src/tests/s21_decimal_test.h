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

#include "../s21_decimal.h"

Suite *suite_s21_add(void);
Suite *suite_s21_sub(void);
Suite *suite_s21_mul(void);
Suite *suite_s21_div(void);
Suite *suite_s21_mod(void);
Suite *suite_s21_is_less(void);
Suite *suite_s21_is_less_or_equal(void);
Suite *suite_s21_is_greater(void);
Suite *suite_s21_is_greater_or_equal(void);
Suite *suite_s21_is_equal(void);
Suite *suite_s21_is_not_equal(void);
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

void print_bits(s21_decimal d);

#endif  //  TEST