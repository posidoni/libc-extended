#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (s21_check_matrix(A) || s21_check_matrix(B))
        return INCORRECT_MATRIX;

    if (A->columns != B->rows)
        return CALC_ERROR;

    int code = s21_create_matrix(A->rows, B->columns, result);

    if (code == OK) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                result->matrix[i][j] = 0;
                for (int m = 0; m < B->rows; m++)
                    result->matrix[i][j] += A->matrix[i][m] * B->matrix[m][j];
            }
        }
    }


    return code;
}

