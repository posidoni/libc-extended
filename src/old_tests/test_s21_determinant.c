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
END_TEST START_TEST(determinant_no_zeros) {
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

Suite *suite_s21_determinant(void) {
    Suite *s = suite_create("suite_s21_determinant");
    TCase *tc = tcase_create("s21_determinant_tc");

    tcase_add_test(tc, determinant_hardcoded);
    tcase_add_test(tc, determinant_no_zeros);

    suite_add_tcase(s, tc);
    return s;
}
