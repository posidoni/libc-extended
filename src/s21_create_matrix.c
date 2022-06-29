#include "s21_matrix.h"

int s21_create_matrix(const int rows, const int columns, matrix_t *result) {
    int code = INCORRECT_MATRIX;

    if (rows > 0 && columns > 0) {
        result->columns = columns;
        result->rows = rows;
        result->matrix = calloc(rows, sizeof(double *));
        code = MALLOC_FAILED;

        if (result->matrix) {
            for (int i = 0; i < rows; i++) {
                result->matrix[i] = calloc(columns, sizeof(double));
                if (!result->matrix[i])
                    break;
            }
            code = OK;
        }
    }

    return (code);
}
