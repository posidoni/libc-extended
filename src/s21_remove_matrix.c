#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *const A) {
    if (A) {
        for (int i = 0; i < A->rows; i++)
            free(A->matrix[i]);

        free(A->matrix);
    }
}

/**
 * @brief This function exists to safely exit program in case
 * of the memory allocation failure. Suggestion to myself:
 * learn to use `at exit` functions.
 */

noreturn void s21_halt(void) {
    fprintf(stderr, "Malloc error\n");
    perror("Memory error");
    exit(0);
}

