#include "s21_math.h"

long double s21_fast_pow(long double base, long long int exp) {
    long double res;
    if (exp >= 0) {
        res = 1;
        while (exp) {
            if (exp & 1)
                res *= base;
            base *= base;
            exp >>= 1;
        }
    } else {
        res = 1 / s21_fast_pow(base, -exp);
    }
    return res;
}

long double s21_pow(double base, double exp) {
    long double res;

    int b_n = is_nan(base);
    int b_f = is_finite(base);
    int e_n = is_nan(exp);
    int e_f = is_finite(exp);
    int e_i = s21_fabs(exp - s21_floor(exp)) <= EPS;

    //    // If base is finite and negative and exp is finite and non-integer,
    //    // a domain error occurs and a range error may occur.
    //    if (b_f && base < -EPS && e_f && !e_i) {
    //        return S21_NAN;
    //    }
    //
    //    // If base is zero and exp is zero, a domain error may occur.
    //    if (s21_fabs(base) < EPS && s21_fabs(exp) < EPS) {
    //        return S21_NAN;
    //    }
    //
    //    // If base is zero and exp is negative, a domain error or a pole error
    //    may occur. if (s21_fabs(base) < EPS && exp < -EPS) {
    //        return S21_NAN;
    //    }

    // 1 pow(+0, exp), where exp is a negative odd integer, returns +∞ and
    // raises FE_DIVBYZERO
    if (b_f && !b_n && base > 0 && base <= EPS && e_i && ((int)exp) < 0 &&
        ((int)exp) % 2) {
        return S21_INF;
    }

    // 2 pow(-0, exp), where exp is a negative odd integer, returns -∞ and
    // raises FE_DIVBYZERO
    if (b_f && !b_n && base > 0 && base <= EPS && e_i && ((int)exp) < 0 &&
        ((int)exp) % 2) {
        return -S21_INF;
    }

    // 3 pow(±0, exp), where exp is negative, finite, and is an even integer or
    // a non-integer, returns +∞ and raises FE_DIVBYZERO
    if (b_f && !b_n && s21_fabs(base) < EPS && e_f &&
        ((e_i && !(((int)exp) % 2)) || !e_i)) {
        return S21_INF;
    }

    // 4 pow(±0, -∞) returns +∞ and may raise FE_DIVBYZERO
    if (b_f && !b_n && s21_fabs(base) < EPS && !e_n && !e_f && exp < 0) {
        return S21_INF;
    }

    // 5 pow(+0, exp), where exp is a positive odd integer, returns +0
    if (b_f && !b_n && base > 0 && base <= EPS && e_i && ((int)exp) % 2) {
        return +0;
    }

    // 6 pow(-0, exp), where exp is a positive odd integer, returns -0
    if (b_f && !b_n && base < 0 && base >= -EPS && e_i && ((int)exp) % 2) {
        return -0;
    }

    // 7 pow(-0, exp), where exp is a positive odd integer, returns -0
    if (b_f && !b_n && base < 0 && base >= -EPS && e_i && ((int)exp) % 2) {
        return -0;
    }

    // 8 pow(±0, exp), where exp is positive non-integer or a positive even
    // integer, returns +0
    if (b_f && !b_n && s21_fabs(base) < EPS &&
        ((!e_i && s21_fabs(exp) > EPS) || (e_i && !(((int)exp) % 2)))) {
        return +0;
    }

    // 9 pow(-1, ±∞) returns 1
    if (b_f && !b_n && s21_fabs(base + 1) < EPS && !e_f && !e_n) {
        return 1;
    }

    // 10 pow(+1, exp) returns 1 for any exp, even when exp is NaN
    if (b_f && !b_n && s21_fabs(base - 1) < EPS) {
        return 1;
    }

    // 11 pow(base, ±0) returns 1 for any base, even when base is NaN
    if (s21_fabs(exp) < EPS) {
        return 1;
    }

    // 12 pow(base, exp) returns NaN and raises FE_INVALID if base is finite and
    // negative and exp is finite and non-integer.
    if (b_f && base < -EPS && e_f && !e_i) {
        return S21_NAN;
    }

    // 13 pow(base, -∞) returns +∞ for any |base|<1
    if (s21_fabs(base) - 1 < EPS && !e_n && !e_f && exp < 0) {
        return S21_INF;
    }

    // 14 pow(base, -∞) returns +0 for any |base|>1
    if (s21_fabs(base) - 1 > EPS && !e_n && !e_f && exp < 0) {
        return +0;
    }

    // 15 pow(base, +∞) returns +0 for any |base|<1
    if (s21_fabs(base) - 1 < EPS && !e_n && !e_f && exp > 0) {
        return +0;
    }

    // 16 pow(base, +∞) returns +∞ for any |base|>1
    if (s21_fabs(base) - 1 > EPS && !e_n && !e_f && exp > 0) {
        return S21_INF;
    }

    // 17 pow(-∞, exp) returns -0 if exp is a negative odd integer
    if (!b_n && !b_f && base < 0 && e_i && exp < 0 && ((int)exp) % 2) {
        return -0;
    }

    // 18 pow(-∞, exp) returns +0 if exp is a negative non-integer or negative
    // even integer
    if (!b_n && !b_f && base < 0 &&
        ((!e_i && exp < 0) || (e_i && exp < 0 && !(((int)exp) % 2)))) {
        return +0;
    }

    // 19 pow(-∞, exp) returns -∞ if exp is a positive odd integer
    if (!b_n && !b_f && base < 0 && (e_i && exp > 0 && ((int)exp) & 1)) {
        return -S21_INF;
    }

    // 20 pow(-∞, exp) returns +∞ if exp is a positive non-integer or positive
    // even integer
    if (!b_n && !b_f && base < 0 &&
        ((!e_i && exp > 0) || (e_i && exp > 0 && !(((int)exp) % 2)))) {
        return +S21_INF;
    }

    // 21 pow(+∞, exp) returns +0 for any negative exp
    if (!b_n && !b_f && base > 0 && exp < -EPS) {
        return +0;
    }

    // 20 pow(+∞, exp) returns +∞ for any positive exp
    if (!b_n && !b_f && base > 0 && exp > EPS) {
        return +S21_INF;
    }

    if (b_n || e_n) {
        return S21_NAN;
    }

    if (exp > EPS) {
        if (e_i) {
            res = s21_fast_pow(base, exp);
        } else {
            res = s21_exp(exp * s21_log(base));
        }
    } else {
        if (e_i) {
            res = s21_fast_pow(base, exp);
        } else {
            res = (long double)1 / s21_exp(-exp * s21_log(base));
        }
    }

    return res;
}
