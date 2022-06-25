#include "test_s21_matrix.h"

START_TEST(mult_matrix) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx = {0};
    s21_create_matrix(cols, rows, &mtx);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m.matrix[i][j] = get_rand(-10e10, 10e10);

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            mtx.matrix[i][j] = get_rand(-10e10, 10e10);
    matrix_t check = {0};
    s21_create_matrix(m.rows, mtx.columns, &check);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < mtx.columns; j++) {
            check.matrix[i][j] = 0;
            for (int k = 0; k < m.columns; k++)
                check.matrix[i][j] += m.matrix[i][k] * mtx.matrix[k][j];
        }
    }

    matrix_t res = {0};
    s21_create_matrix(rows, rows, &res);
    ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_hardcode) {
    const int rows = 3;
    // const int rows = rand() % 100 + 1;
    const int cols = 3;
    // const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx = {0};
    s21_create_matrix(cols, rows, &mtx);

    int md = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m.matrix[i][j] = md++;

    // m.matrix[i][j] = get_rand(-10e10, 10e10);
    int k1 = 1;
    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            mtx.matrix[i][j] = k1++;
    // mtx.matrix[i][j] = get_rand(-10e10, 10e10);

    matrix_t check = {0};
    s21_create_matrix(m.rows, mtx.columns, &check);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < mtx.columns; j++) {
            check.matrix[i][j] = 0;
            for (int k = 0; k < m.columns; k++)
                check.matrix[i][j] += m.matrix[i][k] * mtx.matrix[k][j];
        }
    }

    matrix_t res = {0};
    s21_create_matrix(rows, rows, &res);

    ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);


    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

Suite *suite_s21_mult_matrix(void) {
    Suite *s = suite_create("suite_s21_mult_matrix");
    TCase *tc = tcase_create("s21_mult_matrix");

    tcase_add_loop_test(tc, mult_matrix, 0, 1000);
    tcase_add_test(tc, mult_hardcode);

    suite_add_tcase(s, tc);
    return s;
}
