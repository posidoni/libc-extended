#include "s21_matrix.h"

// The determinant is a number that is associated to each square matrix and calculated from the elements using special formulas.
// Tip: The determinant can only be calculated for a square matrix.

// The determinant of a matrix equals the sum of the products of elements of the row (column) and the corresponding algebraic complements.

// Finding the determinant of matrix A by the first row:

//     1 2 3
// A = 4 5 6
//     7 8 9

// |A| = 1 × 5 6 - 2 × 4 6 + 3 × 4 5 = 1 × (5 × 9 - 8 × 6) - 2 × (4 × 9 - 6 × 7) + 3 × (4 × 8 - 7 × 5)
//           8 9       7 9       7 8
// |A| = 1 × (45 - 48) - 2 × (36 - 42) + 3 × (32 - 35) = -3 + 12 + (-9) = 0
// |A| = 0
// If it is impossible to calculate the determinant of the given matrix, the function must return the value NAN.

static double s21_determinant_rec(double **mat, int dim);

int s21_determinant(matrix_t *A, double *result) {
    if (A->rows != A->columns || A->rows <= 0) {
        *result = NAN;
        return CALC_ERROR;
    }

    *result = s21_determinant_rec(A->matrix, A->rows);

    return OK;
}

//

static double s21_determinant_rec(double **mat, int dim) {
    if (dim == 1)
        return mat[0][0];
    if (dim == 2) {
        double res = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        printf("RES: %lf\n", res);
        return res;
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

// int findDet(int** a, int n) {  //Рекурсивная функция вычисления определителя матрицы
//     if (n == 1)
//         return a[0][0];
//     else if (n == 2)
//         return a[0][0] * a[1][1] - a[0][1] * a[1][0];
//     else {
//         int d = 0;
//         for (int k = 0; k < n; k++) {
//             int** m = new int*[n - 1];
//             for (int i = 0; i < n - 1; i++) {
//                 m[i] = new int[n - 1];
//             }
//             for (int i = 1; i < n; i++) {
//                 int t = 0;
//                 for (int j = 0; j < n; j++) {
//                     if (j == k)
//                         continue;
//                     m[i - 1][t] = a[i][j];
//                     t++;
//                 }
//             }
//             d += pow(-1, k + 2) * a[0][k] * findDet(m, n - 1);
//             clearMemory(m, n - 1);  //Освобождаем память, выделенную под алгебраическое дополнение
//         }
//         return d;  //Возвращаем определитель матрицы
//     }
// }