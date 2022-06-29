#include "s21_matrix.h"

static void adjoint(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int code = OK;

    if (s21_check_matrix(A))
        code = INCORRECT_MATRIX;
    else if (A->rows != A->columns)
        code = CALC_ERROR;
    else
        code = s21_create_matrix(A->rows, A->columns, result);

    if (code == OK)
        adjoint(A, result);

    return (code);
}

static void adjoint(matrix_t *A, matrix_t *result) {
    if (A->rows == 1) {
        result->matrix[0][0] = 1;
        return;
    }

    int size = A->rows;
    double **tmp = malloc(sizeof(double *) * size);
    if (!tmp)
        s21_halt();

    for (int i = 0; i < size; i++) {
        tmp[i] = malloc(sizeof(double) * size);
        if (!tmp[i])
            s21_halt();
    }

    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            get_cofactor(A->matrix, tmp, i, j, size);
            result->matrix[i][j] = sign * s21_determinant_rec(tmp, size - 1);
            sign = -sign;
        }
    }
    for (int i = 0; i < size; i++)
        free(tmp[i]);
    free(tmp);
}
