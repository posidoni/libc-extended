#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
    if (s21_check_matrix(A))
        return INCORRECT_MATRIX;

    if (A->rows != A->columns)
        return CALC_ERROR;

    if (A->rows == 1)
        *result = A->matrix[0][0];
    else
        *result = s21_determinant_rec(A->matrix, A->rows);

    return OK;
}

double s21_determinant_rec(double **mat, int dim) {
    if (dim == 1)
        return mat[0][0];

    double det = 0.0;
    // @bugfix: Sign should NOT be static
    double sign = 1.0;

    for (int i = 0; i < dim; i++) {
        matrix_t tmp = {0};
        int code = s21_create_matrix(dim - 1, dim - 1, &tmp);
        if (code == MALLOC_FAILED)
            s21_halt();

        for (int m = 1; m < dim; m++) {
            int p = 0;
            for (int n = 0; n < dim; n++) {
                /* If we are on the same column as our 'anchor' value */
                if (n == i)
                    continue;
                /* Filling out our tmp value with the valus from the base
                 * matr
                 */
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
