#include "../s21_decimal.h"
#include <float.h>

/* NOTE : most likely not needed */
/* void swap_ui(unsigned *a, unsigned *b) { */
/*     unsigned tmp = *a; */
/*     *a = *b; */
/*     *b = tmp; */
/* } */

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    if (!isnormal(src))
        return CONVERTATION_ERROR;
    if (src > MAX_DECIMAL || src < MIN_DECIMAL)
        return CONVERTATION_ERROR;

    float val = floor(src) / 2;
    char bits[96] = {'\0'};

    for (int i = 0; val > 1e-6; i++) {

        if (val - floor(val) > 1e-6) {
            bits[i] = '1';
        } else {
            bits[i] = '0';
        }

        val = floor(val) / 2;
    }

    for (int i = strlen(bits) - 1; i >= 0; i--)
        if (bits[i] - '0')
            ADD_BIT(dst->bits[i / 32], i % 32);

#ifdef DEBUG
    printf("bits string =");
    puts(bits);
#endif

    /* NOTE: most likely not needed */
    /* NOTE: this is done for tests, not sure if need to keep */
    /* swap_ui(&dst->bits[0], &dst->bits[2]); */
    /* for (int i = 0; i < 3; i++) */
    /*     dst->bits[i] = reverse_bits(dst->bits[i]); */

    return CONVERTATION_OK;
}
