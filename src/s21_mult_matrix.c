#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (result->rows != A->rows || result->columns != B->columns || A->columns != B->rows || A->rows != B->columns)
        return CALC_ERROR;

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;
            for (int m = 0; m < B->rows; m++)
                result->matrix[i][j] += A->matrix[i][m] * B->matrix[m][j];
        }
    }

    return OK;
}
