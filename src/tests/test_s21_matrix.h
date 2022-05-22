#ifndef TEST
#define TEST

#include <check.h>
#include <stdlib.h>
#include <time.h>

#include "../s21_matrix.h"

Suite *suite_s21_eq_matrix(void);
Suite *suite_s21_create_matrix(void);
Suite *suite_s21_sum_matrix(void);
Suite *suite_s21_sub_matrix(void);
Suite *suite_s21_mult_number_matrix(void);
Suite *suite_s21_mult_matrix(void);
Suite *suite_s21_transpose_matrix(void);

void run_tests(void);
void run_testcase(Suite *testcase);

double get_rand(double min, double max);
#endif  //  TEST
