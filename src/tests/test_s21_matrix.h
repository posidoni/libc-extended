#ifndef TEST
#define TEST

#include <check.h>
#include <errno.h>
#include <gsl/gsl_matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "../gsl/include/gsl/gsl_matrix.h"
#include "../s21_matrix.h"

Suite *suite_s21_eq_matrix(void);
Suite *suite_s21_create_matrix(void);
Suite *suite_s21_sum_matrix(void);
Suite *suite_s21_sub_matrix(void);
Suite *suite_s21_mult_number(void);
Suite *suite_s21_transpose(void);
Suite *suite_s21_mult_matrix(void);
Suite *suite_s21_determinant(void);
Suite *suite_s21_calc_complements(void);
Suite *suite_s21_inverse_matrix(void);

void run_tests(void);
void run_testcase(Suite *testcase);
void copy_s21_matr_to_gsl(int rows, int cols, matrix_t *res,
                          gsl_matrix *gsl_got);
void fill_s21_gsl_random(int rows, int cols, matrix_t *m, gsl_matrix *gsl_in);
double get_rand(double min, double max);

#endif  //  TEST
