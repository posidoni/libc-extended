//
// Created by Nana Daughterless on 6/21/22.
//

#include "main.h"

void run_float_to_dec_test(int count) {
  char *number;
  char *result;

  generate_testcase(count, FLOAT_TO_DEC_PATH);

  while (count-- > 0) {
    get_testcase(&number, &result);

    float num = strtof(number, NULL);
    s21_decimal res = str2decimal(result);

    s21_decimal s21_res;
      int ret_error = s21_from_float_to_decimal(num, &s21_res);

    float s21_res_f;

    s21_from_decimal_to_float(s21_res, &s21_res_f);

    if (num != s21_res_f) {
      printf("%s%s%s\n", COLOR_RED, "ERROR", COLOR_END);
      printf("%s%s%s\n%d\n", COLOR_RED, "RETURN ERROR: ", COLOR_END, ret_error);

      printf("%s%s%s\n%f\n", COLOR_ORANGE, "NUMBER:", COLOR_END, num);
      printf("%s%s%s\n%s\n", COLOR_ORANGE, "RESULT:", COLOR_END, result);
      printf("%s%s%s\n", COLOR_GREEN, "S21 RESULT", COLOR_END);
      d_print_decimal(s21_res);
      printf("%s%s%s\n%f\n", COLOR_CYAN, "NEEDED RESULT", COLOR_END, num);
      scanf("*c");
      rewind(stdin);
    } else {
      printf("%d - OK\n", count);
    }
  }

  free_testcase(count);
}
