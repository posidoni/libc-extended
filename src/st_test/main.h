//
// Created by Nana Daughterless on 6/18/22.
//

#ifndef SRC_ST_TEST_MAIN_H_
#define SRC_ST_TEST_MAIN_H_

#define BITS_IN_INT 32
#define BITS_COUNT 3
#define ALL_BIT (BITS_IN_INT * BITS_COUNT)

#define DECIMAL_INFO 3
#define START_EXP_BIT 16
#define END_EXP_BIT 23
#define SIGN_BIT 31

#define MAX_EXPONENT 28


#define COLOR_HEADER "\033[95m"
#define COLOR_BLUE "\033[94m"
#define COLOR_CYAN "\033[96m"
#define COLOR_GREEN "\033[92m"
#define COLOR_ORANGE "\033[93m"
#define COLOR_RED "\033[91m"
#define COLOR_END "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_UNDERLINE "\033[4m"

#define PYTHON "python3"
#define TRUNCATE_PATH " py_test/print_truncate_testcase.py"
#define ROUND_PATH " py_test/print_round_testcase.py"
#define FLOOR_PATH " py_test/print_floor_testcase.py"
#define NEGATE_PATH " py_test/print_negate_testcase.py"

#define DEC_TO_FLOAT_PATH " py_test/print_dec_to_float_testcase.py"
#define DEC_TO_INT_PATH " py_test/print_dec_to_int_testcase.py"
#define FLOAT_TO_DEC_PATH " py_test/print_float_to_dec_testcase.py"
#define INT_TO_DEC_PATH " py_test/print_int_to_dec_testcase.py"

#define EQ_PATH " py_test/print_eq_testcase.py"
#define LESS_PATH " py_test/print_less_testcase.py"

#define REDIRECT " >> "
#define REDIRECT_FILE "input"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../s21_decimal.h"

#define EPS 1e-7

static long long cur_testcase = 0;

static char ** numbers;
static char ** results;
static char ** results2;

#define BUFFER_SIZE 1024

s21_decimal str2decimal(const char *number);

void print_decimal(s21_decimal a);
void d_print_decimal(s21_decimal a);
char* decimal2str(s21_decimal a);

void generate_testcase(int count, char *command_path);
void free_testcase(int count);
void get_testcase(char **number, char **result);
void get_testcase2(char **result2);


// another
void run_truncate_test(int count);
void run_round_test(int count);
void run_floor_test(int count);
void run_negate_test(int count);

// conversion
void run_dec_to_float_test(int count);
void run_dec_to_int_test(int count);
void run_float_to_dec_test(int count);
void run_int_to_dec_test(int count);

// compracion
void run_eq_test(int count);
void run_less_test(int count);

s21_decimal init_random_decimal();

#endif  // SRC_ST_TEST_MAIN_H_
