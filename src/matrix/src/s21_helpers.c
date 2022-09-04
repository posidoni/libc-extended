#include "s21_matrix.h"

int s21_check_matrix(matrix_t *m) {
    int code = OK;

    if (!m || m->rows < 1 || m->columns < 1) {
        code = INCORRECT_MATRIX;
    }

    return code;
}
