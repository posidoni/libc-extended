#ifndef TEST
#define TEST

#include <check.h>
#include "../gsl/include/gsl/gsl_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../s21_matrix.h"
#include <check.h>
#include <gsl/gsl_matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// suite_s21_inverse_matrix() //

void run_tests(void);
void run_testcase(Suite *testcase);
void copy_s21_matr_to_gsl(int rows, int cols, matrix_t *res, gsl_matrix *gsl_got);
void fill_s21_gsl_random(int rows, int cols, matrix_t *m, gsl_matrix *gsl_in);
double get_rand(double min, double max);


#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;92m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define URED "\e[4;31m"
#define ENDCOLOR "\e[0m"

#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

#define PRETTY_PRINT(string) (UGRN string ENDCOLOR)

#endif  //  TEST
