#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *const A) {
    for (int i = 0; i < A->rows; i++)
        free(A->matrix[i]);

    free(A->matrix);
}

void s21_halt(void) {
    fprintf(stderr, "Malloc error\n");
    perror(errno);
    exit(1);
}
