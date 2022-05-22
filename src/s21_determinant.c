#include "s21_matrix.h"

static double s21_determinant_rec(double **mat, int dim);

int s21_determinant(matrix_t *A, double *result) {
    if (A->rows != A->columns || A->rows <= 0 || A->columns <= 0) {
        *result = NAN;
        return CALC_ERROR;
    }

    *result = s21_determinant_rec(A->matrix, A->rows);

    return OK;
}

static double s21_determinant_rec(double **mat, int dim) {
    if (dim == 1)
        return mat[0][0];
    if (dim == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }

    double det = 0.0;
    static double sign = 1.0;

    for (int i = 0; i < dim; i++) {
        matrix_t tmp = {0};
        s21_create_matrix(dim - 1, dim - 1, &tmp);

        for (int m = 1; m < dim; m++) {
            int p = 0;
            for (int n = 0; n < dim; n++) {
                /* If we are on the same column as our 'anchor' value */
                if (n == i)
                    continue;
                /* Filling out our tmp value with the valus from the base matr */
                tmp.matrix[m - 1][p] = mat[m][n];
                p++;
            }
        }

        det += sign * mat[0][i] * s21_determinant_rec(tmp.matrix, dim - 1);
        sign = -sign;
        s21_remove_matrix(&tmp);
    }

    return det;
}
