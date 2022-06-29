#include "test_s21_matrix.h"

START_TEST(create_matrix) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[i][j] = 0;
            ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-06);
        }
    }
    ck_assert_int_eq(m.rows, rows);
    ck_assert_int_eq(m.columns, cols);
    s21_remove_matrix(&m);
}
END_TEST

START_TEST(no_rows) {
    const int rows = 0;
    const int cols = 10;
    matrix_t m = {0};
    ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

START_TEST(no_cols) {
    const int rows = 10;
    const int cols = 0;

    matrix_t m = {0};
    ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

Suite *suite_s21_create_matrix(void) {
    Suite *s = suite_create("suite_s21_create_matrix");
    TCase *tc = tcase_create("s21_create_matrix");

    tcase_add_loop_test(tc, create_matrix, 0, 100);
    tcase_add_test(tc, no_rows);
    tcase_add_test(tc, no_cols);

    suite_add_tcase(s, tc);
    return s;
}
