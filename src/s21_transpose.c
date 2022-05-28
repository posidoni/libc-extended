#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
    if (A->columns != result->rows || A->rows != result->columns)
        return CALC_ERROR;

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[j][i] = A->matrix[i][j];
        }
    }

    return OK;
}
