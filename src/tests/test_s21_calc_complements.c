#include "test_s21_matrix.h"

START_TEST(complements_hardcoded) {
    const int size = 3;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 2;
    m.matrix[2][0] = 5;
    m.matrix[2][1] = 2;
    m.matrix[2][2] = 1;

    matrix_t expected = {0};
    s21_create_matrix(size, size, &expected);
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;
    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;
    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;

    matrix_t res = {0};
    s21_create_matrix(size, size, &res);
    s21_calc_complements(&m, &res);

    for (int i = 0; i < res.rows; i++) {
        for (int j = 0; j < res.columns; j++) {
            printf("%lf ", res.matrix[i][j]);
        }
        printf("\n");
    }

    ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
}
END_TEST

Suite *suite_s21_calc_complements(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_calc_complements"));
    TCase *tc = tcase_create("s21_calc_complements_tc");

    tcase_add_test(tc, complements_hardcoded);

    suite_add_tcase(s, tc);
    return s;
}
