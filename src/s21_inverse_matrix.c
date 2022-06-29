#include "s21_matrix.h"

void adjoint_inverse(matrix_t *A, matrix_t *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    if (s21_check_matrix(A))
        return INCORRECT_MATRIX;

    if (A->rows != A->columns)
        return CALC_ERROR;

    double d = 0.0;
    int code = s21_create_matrix(A->rows, A->columns, result);

    if (code == OK) {
        s21_determinant(A, &d);

        if (fabs(d) < 1e-6)
            return CALC_ERROR;

        matrix_t adj1 = {0};
        s21_create_matrix(A->rows, A->columns, &adj1);
        s21_calc_complements(A, &adj1);
        matrix_t adj = {0};
        s21_create_matrix(A->columns, A->rows, &adj);
        s21_transpose(&adj1, &adj);

        int size = A->rows;

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                result->matrix[i][j] = adj.matrix[i][j] / d;

        s21_remove_matrix(&adj);
    }

    return (code);
}
