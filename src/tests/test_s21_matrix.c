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

START_TEST(sum_matrix) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx = {0};
    s21_create_matrix(rows, cols, &mtx);
    matrix_t check = {0};
    s21_create_matrix(rows, cols, &check);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
            mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
            check.matrix[i][j] = m.matrix[i][j] + mtx.matrix[i][j];
        }
    }
    matrix_t res = {0};
    s21_create_matrix(rows, cols, &res);
    ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

Suite *suite_s21_sum_matrix(void) {
    Suite *s = suite_create("suite_s21_sum_matrix");
    TCase *tc = tcase_create("s21_sum_matrix");

    tcase_add_loop_test(tc, sum_matrix, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}

START_TEST(sub_matrix) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx = {0};
    s21_create_matrix(rows, cols, &mtx);
    matrix_t check = {0};
    s21_create_matrix(rows, cols, &check);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
            mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
            check.matrix[i][j] = m.matrix[i][j] - mtx.matrix[i][j];
        }
    }
    matrix_t res = {0};
    s21_create_matrix(rows, cols, &res);
    ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

Suite *suite_s21_sub_matrix(void) {
    Suite *s = suite_create("suite_s21_sub_matrix");
    TCase *tc = tcase_create("s21_sub_matrix");

    tcase_add_loop_test(tc, sub_matrix, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}

START_TEST(mult_number_matrix) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t check = {0};
    s21_create_matrix(rows, cols, &check);
    double mult_number = get_rand(-10e5, 10e5);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
            check.matrix[i][j] = m.matrix[i][j] * mult_number;
        }
    }
    matrix_t res = {0};
    s21_create_matrix(rows, cols, &res);
    ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

Suite *suite_s21_mult_number_matrix(void) {
    Suite *s = suite_create("suite_s21_mult_number_matrix");
    TCase *tc = tcase_create("s21_mult_number_matrix");

    tcase_add_loop_test(tc, mult_number_matrix, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}

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

START_TEST(simple_mult) {
    const int rows = 2;
    const int cols = 3;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx = {0};
    s21_create_matrix(cols, rows, &mtx);

    for (int i = 0, c = 1; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m.matrix[i][j] = c++;

    for (int i = 0, c = 7; i < cols; i++)
        for (int j = 0; j < rows; j++)
            mtx.matrix[i][j] = c++;

    matrix_t check = {0};
    s21_create_matrix(m.rows, mtx.columns, &check);
    check.matrix[0][0] = 58;
    check.matrix[0][1] = 64;
    check.matrix[1][0] = 139;
    check.matrix[1][1] = 154;

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
    tcase_add_test(tc, simple_mult);

    suite_add_tcase(s, tc);
    return s;
}

START_TEST(transpose_matrix) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);

    matrix_t check = {0};
    s21_create_matrix(cols, rows, &check);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double rand_val = get_rand(-10e10, 10e10);
            m.matrix[i][j] = rand_val;
            check.matrix[j][i] = rand_val;
        }
    }

    matrix_t res = {0};
    s21_create_matrix(cols, rows, &res);
    ck_assert_int_eq(s21_transpose(&m, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST
Suite *suite_s21_transpose_matrix(void) {
    Suite *s = suite_create("suite_s21_transpose_matrix");
    TCase *tc = tcase_create("s21_transpose_matrix");

    tcase_add_loop_test(tc, transpose_matrix, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}
