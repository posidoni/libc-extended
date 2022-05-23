#include "s21_math.h"

static long double s21_atan_pos_neg(long double magic, long double res, int mod,
                                    int *sp, long double x);
static int check_inf(double x);

long double s21_atan(double x) {
    long double res = 0.0;

    const long double one_atan = 0.7853981633974480L;
<<<<<<< HEAD
    int modulo_x = (fabsl(x) < 0.0L);

<<<<<<< HEAD:s21_atan.c
<<<<<<< HEAD
    /* Warning! Replaced sqrt(x^2) with fabs(x) in the original formula */
    long double magic = (M_PI * fabsl(x)) / (2 * x);
    
    int special = check_inf(x);

    /* Constants for atan 1.0. This case is special, Taylor series can't count this */
    if (x == 1.0L)
        res = one_atan;
    if (x == -1.0L)
        res = -one_atan;

    if (x != 0.0 && !special && fabsl(x) != 1.0) {
        for (int i = 0; i < 10000; i++) {
=======
    int modulo_x = (s21_fabs(x) < 0);
=======
    int modulo_x = (s21_fabs(x) < 1.0);
>>>>>>> 79b848b (Fixed acos / asin (stable), added correct doubles equality, added good tests)
=======
    int modulo_x = (s21_fabs(x) - 1.0 < EPS);
>>>>>>> 21502c1 (Fix project structure):src/s21_atan.c

    /* Warning! Replaced sqrt(x^2) with fabs(x) in the original formula */
    long double magic = (S21_M_PI * s21_fabs(x)) / (2.0 * x);
    int special = check_inf(x);

    if (!is_finite(x) && s21_fabs(x) > EPS) {
        return S21_M_PI_2;
    }

<<<<<<< HEAD:s21_atan.c
<<<<<<< HEAD
<<<<<<< HEAD
    if (x != 0.0 && !special && s21_fabs(x) != 1.0) {
        for (int i = 0; i < 10; i++) {
>>>>>>> 71bf06a (s21_)
=======
=======

>>>>>>> 7beee38 (fixed atan (needed better precision around 1))
    /* Constants for atan 1.0. This case is special, Taylor series can't count this */
    if (s21_ldeq(x, 1.0)) res = atan(x);
    if (s21_ldeq(x, -1.0)) res = atan(x);
=======
    /* Constants for atan 1.0. This case is special, Taylor series can't count
     * this */
    if (s21_ldeq(x, 1.0))
        res = one_atan;
    if (s21_ldeq(x, -1.0))
        res = -one_atan;
>>>>>>> 21502c1 (Fix project structure):src/s21_atan.c

    if (!s21_ldeq(x, 0.0) && !special && !s21_ldeq(s21_fabs(res), one_atan)) {
<<<<<<< HEAD:s21_atan.c
<<<<<<< HEAD
<<<<<<< HEAD
        for (int i = 0; i < 10000; i++) {
>>>>>>> 79b848b (Fixed acos / asin (stable), added correct doubles equality, added good tests)
=======
=======
        // TODO Move iter... to const
>>>>>>> 85ddb17 (Add TODO)
        for (int i = 0; i < 100000; i++) {
>>>>>>> 7beee38 (fixed atan (needed better precision around 1))
=======
        static const int good_precision = 100000;
        for (int i = 0; i < good_precision; i++) {
>>>>>>> 3b6eab5 (Minor fix, uncommented targets in makefile, removed math.h, GCOV untested):src/s21_atan.c
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
