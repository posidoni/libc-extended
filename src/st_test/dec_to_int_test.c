//
// Created by Nana Daughterless on 6/21/22.
//

#include "main.h"


void run_dec_to_int_test(int count) {
    char *number;
    char *result;

    generate_testcase(count, DEC_TO_INT_PATH);

    while (count-- > 0) {
        get_testcase(&number, &result);

        s21_decimal decimal_num = str2decimal(number);

        int res = strtol(result, NULL, 10);

        int s21_res;
        s21_from_decimal_to_int(decimal_num, &s21_res);

        int diff = res - s21_res;
        if (diff) {
            printf("%s%s%s\n", COLOR_RED, "ERROR", COLOR_END);
            printf("s21_is_eq = %d\n", diff);
            printf("%s%s%s\n%s\n", COLOR_ORANGE, "NUMBER:", COLOR_END, number);
            printf("%s%s%s\n%s\n", COLOR_ORANGE, "RESULT:", COLOR_END, result);
            printf("%s%s%s\n", COLOR_BLUE, "DECIMAL_NUMBER", COLOR_END);
            d_print_decimal(decimal_num);
            printf("%s%s%s\n%d\n", COLOR_GREEN, "S21 RESULT", COLOR_END, s21_res);
            printf("%s%s%s\n%d\n", COLOR_CYAN, "NEEDED RESULT", COLOR_END, res);
            scanf("*c"); rewind(stdin);
        } else {
            printf("%d - OK\n", count);
        }
    }

    free_testcase(count);
}
