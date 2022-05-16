#include "s21_math.h"

static long double s21_atan_pos_neg(long double magic, long double res, int mod, int *sp, long double x);
static int check_inf(double x);

long double s21_atan(double x) {
    long double res = 0.0L;
    const long double one_atan = 0.7853981633974480L;
    int modulo_x = (fabsl(x) < 0);

    /* Warning! Replaced sqrt(x^2) with fabs(x) in the original formula */
    long double magic = (M_PI * fabsl(x)) / (2 * x);
    int special = check_inf(x);

    /* Constants for atan 1.0. This case is special, Taylor series can't count this */
    if (x == 1.0)
        res = one_atan;
    if (x == -1.0)
        res = -one_atan;

    if (x != 0.0 && !special && fabsl(x) != 1.0) {
        for (int i = 0; i < 1000; i++) {
            if (modulo_x) {
                res += (pow(-1, i) * pow(x, 1 + 2 * i)) / (1 + 2 * i);
            } else {
                res += (pow(-1, i) * pow(x, (-1 - 2 * i))) / (1 + 2 * i);
            }
        }
    }

    return (is_nan(x)) ? NAN : s21_atan_pos_neg(magic, res, modulo_x, &special, x);
}

static long double s21_atan_pos_neg(long double magic, long double res, int mod, int *sp, long double x) {
    if (!mod && res != 0.0 && !(*sp)) {
        res = magic - res;
    }

    if (*sp) {
        if (x == INFINITY) {
            res = M_PI_2;
        } else {
            res = -1.0L * M_PI_2;
        }
    }

    return res;
}

static int check_inf(double x) {
    int flag = 0;

    if (!isfinite(x) && !is_nan(x)) {
        flag = 1;
    }

    return flag;
}