#include "s21_math.h"

static long double s21_atan_pos_neg(long double magic, long double res, int mod,
                                    int *sp, long double x);
static int check_inf(double x);

long double s21_atan(double x) {
    long double res = 0.0;

    const long double one_atan = 0.7853981633974480L;

    int modulo_x = (s21_fabs(x) - 1.0 < EPS);

    /* Warning! Replaced sqrt(x^2) with fabs(x) in the original formula */
    long double magic = (S21_M_PI * s21_fabs(x)) / (2.0 * x);
    int special = check_inf(x);

    if (!is_finite(x) && s21_fabs(x) > EPS) {
        return S21_M_PI_2;
    }

    /* Constants for atan 1.0. This case is special, Taylor series can't count
     * this */
    if (s21_ldeq(x, 1.0))
        res = one_atan;
    if (s21_ldeq(x, -1.0))
        res = -one_atan;

    if (!s21_ldeq(x, 0.0) && !special && !s21_ldeq(s21_fabs(res), one_atan)) {
        static const int good_precision = 100000;
        for (int i = 0; i < good_precision; i++) {
            if (modulo_x) {
                res += (s21_pow(-1.0, i) * s21_pow(x, 1 + 2 * i)) / (1 + 2 * i);
            } else {
                res +=
                    (s21_pow(-1.0, i) * s21_pow(x, (-1 - 2 * i))) / (1 + 2 * i);
            }
        }
    }

    return (is_nan(x)) ? S21_NAN
                       : s21_atan_pos_neg(magic, res, modulo_x, &special, x);
}

static long double s21_atan_pos_neg(long double magic, long double res, int mod,
                                    int *sp, long double x) {
    if (!mod && !s21_ldeq(res, 0.0) && !(*sp)) {
        res = magic - res;
    }

    if (*sp) {
        if (s21_fabs(x) > EPS) {
            res = S21_M_PI_2;
            return res;
        } else {
            res = -1.0L * S21_M_PI_2;
        }
    }

    if (x > S21_M_PI_2) {
        return S21_M_PI_2;
    }

    if (x < -1.0L * S21_M_PI_2) {
        return -1.0L * S21_M_PI_2;
    }

    return res;
}

static int check_inf(double x) {
    int flag = 0;
    if (!is_finite(x) && !is_nan(x) && s21_ldeq(x, 0.0)) {
        flag = 1;
    }
    return flag;
}
