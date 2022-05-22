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