//
// Created by Nana Daughterless on 6/18/22.
//

#include "main.h"


void run_round_test(int count) {
    char *number;
    char *result;

    generate_testcase(count, ROUND_PATH);

    while (count-- > 0) {
        get_testcase(&number, &result);

        s21_decimal decimal_num = str2decimal(number);

        s21_decimal decimal_res = str2decimal(result);
        s21_decimal s21_decimal_res = init_random_decimal();
        s21_round(decimal_num, &s21_decimal_res);

        if (!s21_is_equal(decimal_res, s21_decimal_res)) {
            printf("%s%s%s\n", COLOR_RED, "ERROR", COLOR_END);
            printf("s21_is_eq = %d\n", !s21_is_equal(decimal_res, s21_decimal_res));
            printf("%s%s%s\n%s\n", COLOR_ORANGE, "NUMBER:", COLOR_END, number);
            printf("%s%s%s\n%s\n", COLOR_ORANGE, "RESULT:", COLOR_END, result);
            printf("%s%s%s\n", COLOR_BLUE, "DECIMAL_NUMBER", COLOR_END);
            d_print_decimal(decimal_num);
            printf("%s%s%s\n", COLOR_GREEN, "S21 RESULT", COLOR_END);
            d_print_decimal(s21_decimal_res);
            printf("%s%s%s\n", COLOR_CYAN, "NEEDED RESULT", COLOR_END);
            d_print_decimal(decimal_res);
            scanf("*c"); rewind(stdin);
        } else {
            printf("%d - OK\n", count);
        }
    }

    free_testcase(count);
}
