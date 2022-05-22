#include "s21_matrix.h"

int s21_create_matrix(const int rows, const int columns, matrix_t *result) {
    if (rows <= 0 || columns <= 0)
        return INCORRECT_MATRIX;
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (!result->matrix)
        return MALLOC_FAILED;
    for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (!result->matrix[i])
            return MALLOC_FAILED;
    }
    return OK;
}

void s21_remove_matrix(matrix_t *const A) {
    for (int i = 0; i < A->rows; i++)
        free(A->matrix[i]);
    free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    if (A->rows != B->rows || A->columns != B->columns)
        return CALC_ERROR;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07)
                return FAILURE;

    return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (A->rows != B->rows || A->columns != B->columns)
        return CALC_ERROR;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];

    return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (A->rows != B->rows || A->columns != B->columns)
        return CALC_ERROR;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];

    return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    if (result->rows != A->rows || result->columns != A->columns)
        return CALC_ERROR;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] * number;
    return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if ((A->columns != B->rows) || (A->rows != B->columns))
        return CALC_ERROR;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;
            for (int k = 0; k < A->columns; k++)
                result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
    }
    return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    if (result->rows != A->columns || result->columns != A->rows)
        return CALC_ERROR;

    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[j][i] = A->matrix[i][j];
    return OK;
}

/* int s21_calc_complements(matrix_t *A, matrix_t *result) { */

/* } */
