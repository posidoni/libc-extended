//
// Created by Nana Daughterless on 6/21/22.
//

#include "main.h"


void run_less_test(int count) {
    char *number;
    char *number2;
    char *result;

    generate_testcase(count, LESS_PATH);

    while (count-- > 0) {
        get_testcase(&number, &number2);
        get_testcase2(&result);

        s21_decimal decimal_num = str2decimal(number);
        s21_decimal decimal_num2 = str2decimal(number2);

        int is_eq = !strcmp(result, "YES");
        if (is_eq != s21_is_less(decimal_num, decimal_num2)) {
            printf("%s%s%s\n", COLOR_RED, "ERROR", COLOR_END);
            printf("%s%s%s\n%s\n", COLOR_ORANGE, "NUMBER:", COLOR_END, number);
            printf("%s%s%s\n%s\n", COLOR_ORANGE, "NUMBER2:", COLOR_END, number2);
            printf("%s%s%s\n", COLOR_BLUE, "DECIMAL_NUMBER", COLOR_END);
            d_print_decimal(decimal_num);
            printf("%s%s%s\n", COLOR_BLUE, "DECIMAL_NUMBER2", COLOR_END);
            d_print_decimal(decimal_num2);
            printf("%s%s%s\n%d\n", COLOR_GREEN, "S21 RESULT", COLOR_END, s21_is_less(decimal_num, decimal_num2));
            printf("%s%s%s\n%d\n", COLOR_CYAN, "NEEDED RESULT", COLOR_END, is_eq);
            scanf("*c"); rewind(stdin);
        } else {
            printf("%d - OK\n", count);
        }
    }

    free_testcase(count);
}
