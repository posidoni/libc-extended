#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
    int code = s21_create_matrix(A->columns, A->rows, result);

    if (code == OK) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
    }

    return code;
}

void get_cofactor(double **m, double **tmp, int skip_row, int skip_col,
                  int size) {
    for (int row = 0, i = 0, j = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row != skip_row && col != skip_col) {
                tmp[i][j] = m[row][col];
                j++;

                /* dims of submatr are always = size - 1 of big matr. */
                if (j == size - 1) {
                    /* Go to the beginning of the new row*/
                    j = 0;
                    i++;
                }
            }
        }
    }
}
