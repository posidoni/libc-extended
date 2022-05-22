#include "s21_matrix.h"

static const double EPS = 1e-6;

int s21_create_matrix(const int rows, const int columns, matrix_t *result) {
    int res = INCORRECT_MATRIX;

    if (rows > 0 && columns > 0) {
        result->columns = columns;
        result->rows = rows;
        result->matrix = calloc(rows, sizeof(double *));
        res = MALLOC_FAILED;

        if (result->matrix) {
            for (int i = 0; i < rows; i++) {
                result->matrix[i] = calloc(columns, sizeof(double));
                if (!result->matrix[i])
                    return MALLOC_FAILED;
                // (?) memory cleanup after failed malloc (?)
            }
            res = OK;
        }
    }

    return res;
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
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS)
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

// int s21_calc_complements(matrix_t *A, matrix_t *result) {
// }

// int s21_determinant(matrix_t *A, double *result) {
// }

// int s21_inverse_matrix(matrix_t *A) {
// }
