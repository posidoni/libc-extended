//
// Created by Nana Daughterless on 6/21/22.
//

#include "main.h"


void run_int_to_dec_test(int count) {
    char *number;
    char *result;

    generate_testcase(count, INT_TO_DEC_PATH);

    while (count-- > 0) {
        get_testcase(&number, &result);


        int num = strtol(number, NULL, 10);
        s21_decimal res = str2decimal(result);

        s21_decimal s21_res;
        s21_from_int_to_decimal(num, &s21_res);

        if (!s21_is_equal(res, s21_res)) {
            printf("%s%s%s\n", COLOR_RED, "ERROR", COLOR_END);
            printf("%s%s%s\n%s\n", COLOR_ORANGE, "NUMBER:", COLOR_END, number);
            printf("%s%s%s\n%s\n", COLOR_ORANGE, "RESULT:", COLOR_END, result);
            printf("%s%s%s\n", COLOR_GREEN, "S21 RESULT", COLOR_END);
            d_print_decimal(s21_res);
            printf("%s%s%s\n", COLOR_CYAN, "NEEDED RESULT", COLOR_END);
            d_print_decimal(res);
            scanf("*c"); rewind(stdin);
        } else {
            printf("%d - OK\n", count);
        }
    }

    free_testcase(count);
}
