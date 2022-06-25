#include "s21_matrix.h"

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
            }
            res = OK;
        }
    }

    return res;
}
