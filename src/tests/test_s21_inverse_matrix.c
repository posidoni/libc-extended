#include "test_s21_matrix.h"

START_TEST(inverse_hardcoded) {
    /* const int size = rand() % 100 + 1; */
    const int size = 3;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);

    m.matrix[0][0] = 2;
    m.matrix[0][1] = 5;
    m.matrix[0][2] = 7;
    m.matrix[1][0] = 6;
    m.matrix[1][1] = 3;
    m.matrix[1][2] = 4;
    m.matrix[2][0] = 5;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = -3;

    matrix_t res = {0};
    s21_create_matrix(size, size, &res);
    s21_inverse_matrix(&m, &res);

    matrix_t expected = {0};
    s21_create_matrix(size, size, &expected);
    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = -1;
    expected.matrix[0][2] = 1;
    expected.matrix[1][0] = -38;
    expected.matrix[1][1] = 41;
    expected.matrix[1][2] = -34;
    expected.matrix[2][0] = 27;
    expected.matrix[2][1] = -29;
    expected.matrix[2][2] = 24;

    ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);

    s21_remove_matrix(&expected);
    s21_remove_matrix(&res);
    s21_remove_matrix(&m);
}
END_TEST

Suite *suite_s21_inverse_matrix(void) {
    Suite *s = suite_create(PRETTY_PRINT("s21_inverse_matrix"));
    TCase *tc = tcase_create("s21_inverse_matrix_tc");

    tcase_add_test(tc, inverse_hardcoded);

    suite_add_tcase(s, tc);
    return s;
}
