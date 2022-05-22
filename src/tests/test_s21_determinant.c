#include "test_s21_matrix.h"

START_TEST(determinant_hardcoded) {
    const int rows = 3;
    const int cols = 3;
    matrix_t m1 = {0};

    s21_create_matrix(rows, cols, &m1);
    int m = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m1.matrix[i][j] = m++;
        }
    }
    m1.matrix[2][2] = 0;
    double result = 0;
    int got = s21_determinant(&m1, &result);
    ck_assert_double_eq_tol(result, 27, 1e-6);
    ck_assert_int_eq(got, OK);
    s21_remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_no_zeros) {
    const int rows = 5;
    const int cols = 5;
    matrix_t m1 = {0};

    s21_create_matrix(rows, cols, &m1);
    int m = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m1.matrix[i][j] = m++;
        }
    }
    double result = 0;
    int got = s21_determinant(&m1, &result);
    ck_assert_double_eq_tol(result, 0, 1e-6);
    ck_assert_int_eq(got, OK);
    s21_remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_nan) {
    int rows = get_rand(3, 100);
    int cols = rows + 1;
    matrix_t m1 = {0};
    s21_create_matrix(rows, cols, &m1);
    double result = 0;
    int got = s21_determinant(&m1, &result);
    ck_assert_int_eq(got, CALC_ERROR);
    ck_assert_double_nan(result);
    s21_remove_matrix(&m1);
}
END_TEST

// START_TEST(determinant_rand) {
//     char numpy[512] = "";
//     char s21_determinant[512] = "./s21_grep ";
//     char flags[512] = "-d";

//     system("echo > grep/test/files/tmp1");
//     system("echo > grep/test/files/tmp2");

//     system("chmod +x ./math_py.py")

//     int grep_v = system(grep);
//     if (grep_v == 1 || grep_v == 0) {
//         system(s21_grep);
//         int val = system("diff grep/test/files/tmp1 grep/test/files/tmp2");

//         char str[2048];
//         sprintf(str, "\nTEST N:%d\n%s%s\n%s%s\n", _i, BLUE, grep, s21_grep, RESET);
//         ck_assert_msg(val == 0, str);
//     }
// }
// END_TEST

Suite *suite_s21_determinant(void) {
    Suite *s = suite_create("suite_s21_determinant");
    TCase *tc = tcase_create("s21_determinant_tc");

    // TODO: add test cases of calculating determinant from custom python script
    tcase_add_test(tc, determinant_hardcoded);
    tcase_add_test(tc, determinant_no_zeros);
    tcase_add_test(tc, determinant_nan);

    suite_add_tcase(s, tc);
    return s;
}
