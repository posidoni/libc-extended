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
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
}

int s21_transpose(matrix_t *A, matrix_t *result) {
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
}

int s21_determinant(matrix_t *A, double *result) {
}

int s21_inverse_matrix(matrix_t *A) {
}
