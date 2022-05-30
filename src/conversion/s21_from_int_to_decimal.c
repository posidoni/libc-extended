#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    convertation_result status = CONVERTATION_OK;
    if (dst) {
        init_decimal(dst);

        if (src >= 0) {
            dst->bits[0] = src;
        } else {
            set_sign_neg(dst);
            dst->bits[0] = src;
        }
    } else {
        status = CONVERTATION_ERROR;
    }
    return status;
}
