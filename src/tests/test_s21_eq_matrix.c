#include "test_s21_matrix.h"

START_TEST(eq_matrix) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx = {0};
    s21_create_matrix(rows, cols, &mtx);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double rand_val = get_rand(DBL_MIN, DBL_MAX);
            m.matrix[i][j] = rand_val;
            mtx.matrix[i][j] = rand_val;
        }
    }
    ck_assert_int_eq(s21_eq_matrix(&m, &mtx), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
}
END_TEST

START_TEST(not_eq) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx = {0};
    s21_create_matrix(rows, cols, &mtx);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
            mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
        }
    }
    ck_assert_int_eq(s21_eq_matrix(&m, &mtx), FAILURE);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
}
END_TEST

Suite *suite_s21_eq_matrix(void) {
    Suite *s = suite_create("suite_s21_eq_matrix");
    TCase *tc = tcase_create("s21_eq_matrix");

    tcase_add_test(tc, not_eq);
    tcase_add_loop_test(tc, eq_matrix, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}
