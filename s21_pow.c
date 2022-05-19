#include "math.h"
#include "s21_math.h"

long double s21_fast_pow(long double base, long long int exp) {
<<<<<<< HEAD
    long double res;
<<<<<<< HEAD

    if (base > EPS) {
        if (fabs(exp) > EPS) {
            res = expl(exp * logl(base));
        } else {
            res = (long double)1 / expl(-exp * logl(base));
=======
=======
    long double res;    
>>>>>>> 5969fca (Stable, 100% tests. Fix bugs in pow tests)
    if (exp >= 0) {
        res = 1;
        while (exp) {
            if (exp & 1)
                res *= base;
            base *= base;
            exp >>= 1;
>>>>>>> 90d402d (Added more check in pow)
        }

    } else {
        res = 1 / s21_fast_pow(base, -exp);
    }

    return res;
}

long double s21_pow(double base, double exp) {
    // TODO REPLACE MATH 2 S21_MATH
    // TODO Move the definition below
    long double res;

    int b_n = is_nan(base);
    int b_f = is_finite(base);
    int e_n = is_nan(exp);
    int e_f = is_finite(exp);
    int e_i = s21_fabs(exp - s21_floor(exp)) <= EPS;

    // If base is finite and negative and exp is finite and non-integer,
    // a domain error occurs and a range error may occur.
    if (b_f && base < -EPS && e_f && !e_i) {
        // TODO CHANGE ERROR
        return S21_NAN;
    }

    // If base is zero and exp is zero, a domain error may occur.
    if (fabs(base) < EPS && fabs(exp) < EPS) {
        // TODO CHANGE ERROR
        printf("2 \n");
        return S21_NAN;
    }

    // If base is zero and exp is negative, a domain error or a pole error may occur.
    if (fabs(base) < EPS && exp < -EPS) {
        // TODO CHANGE ERROR
        return S21_NAN;
    }

    // 1 pow(+0, exp), where exp is a negative odd integer, returns +∞ and raises FE_DIVBYZERO
    if (base > 0 && base <= EPS && e_i && ((int)exp) < 0 && ((int)exp) % 2) {
        // TODO CHANGE ERROR
        return S21_INF;
    }

    // 2 pow(-0, exp), where exp is a negative odd integer, returns -∞ and raises FE_DIVBYZERO
    if (base > 0 && base <= EPS && e_i && ((int)exp) < 0 && ((int)exp) % 2) {
        // TODO CHANGE ERROR
        return -S21_INF;
    }

    // 3 pow(±0, exp), where exp is negative, finite, and is an even integer or a non-integer, returns +∞ and raises FE_DIVBYZERO
    if (fabs(base) < EPS && e_f && ((e_i && !(((int)exp) % 2)) || !e_i)) {
        // TODO CHANGE ERROR
        return S21_INF;
    }

    // 4 pow(±0, -∞) returns +∞ and may raise FE_DIVBYZERO
    if (fabs(base) < EPS && !e_f && exp < 0) {
        // TODO CHANGE ERROR
        return S21_INF;
    }

    // 5 pow(+0, exp), where exp is a positive odd integer, returns +0
    if (base > 0 && base <= EPS && e_i && ((int)exp) % 2) {
        return +0;
    }

    // 6 pow(-0, exp), where exp is a positive odd integer, returns -0
    if (base < 0 && base >= -EPS && e_i && ((int)exp) % 2) {
        return -0;
    }

    // 7 pow(-0, exp), where exp is a positive odd integer, returns -0
    if (base < 0 && base >= -EPS && e_i && ((int)exp) % 2) {
        return -0;
    }

    // 8 pow(±0, exp), where exp is positive non-integer or a positive even integer, returns +0
    if (fabs(base) < EPS && ((!e_i && fabs(exp) > EPS) || (e_i && !(((int)exp) % 2)))) {
        return +0;
    }

    // 9 pow(-1, ±∞) returns 1
    if (fabs(base + 1) < EPS && !e_f) {
        return 1;
    }

    // 10 pow(+1, exp) returns 1 for any exp, even when exp is NaN
    if (fabs(base - 1) < EPS) {
        return 1;
    }

    // 11 pow(base, ±0) returns 1 for any base, even when base is NaN
    if (fabs(exp) < EPS) {
        return 1;
    }

    // 12 pow(base, exp) returns NaN and raises FE_INVALID if base is finite and negative and exp is finite and non-integer.
    if (b_f && base < -EPS && e_f && !e_i) {
        printf("HERE \n");
        return S21_NAN;
    }

    // 13 pow(base, -∞) returns +∞ for any |base|<1
    if (fabs(base - 1) < EPS && !e_f && exp < 0) {
        return S21_INF;
    }

    // 14 pow(base, -∞) returns +0 for any |base|>1
    if (fabs(base - 1) > EPS && !e_f && exp < 0) {
        return +0;
    }

    // 15 pow(base, +∞) returns +0 for any |base|<1
    if (fabs(base - 1) < EPS && !e_f && exp > 0) {
        return +0;
    }

    // 16 pow(base, +∞) returns +∞ for any |base|>1
    if (fabs(base - 1) > EPS && !e_f && exp > 0) {
        return S21_INF;
    }

    // 17 pow(-∞, exp) returns -0 if exp is a negative odd integer
    if (!b_f && base < 0 && e_i && exp < 0 && ((int)exp) % 2) {
        return -0;
    }

    // 18 pow(-∞, exp) returns +0 if exp is a negative non-integer or negative even integer
    if (!b_f && base < 0 && ((!e_i && exp < 0) || (e_i && exp < 0 && !(((int)exp) % 2)))) {
        return +0;
    }

    // 19 pow(-∞, exp) returns -∞ if exp is a positive odd integer
    if (!b_f && base < 0 && (e_i && exp > 0 && ((int)exp) & 1)) {
        return -S21_INF;
    }

    // 20 pow(-∞, exp) returns +∞ if exp is a positive non-integer or positive even integer
    if (!b_f && base < 0 && ((!e_i && exp > 0) || (e_i && exp > 0 && !(((int)exp) % 2)))) {
        return +S21_INF;
    }

    // 21 pow(+∞, exp) returns +0 for any negative exp
    if (!b_f && base > 0 && exp < -EPS) {
        return +0;
    }

    // 20 pow(+∞, exp) returns +∞ for any positive exp
    if (!b_f && base > 0 && exp > EPS) {
        return +S21_INF;
    }

    if (b_n || e_n) {
        return S21_NAN;
    }

    if (exp > EPS) {
        if (e_i) {
            res = s21_fast_pow(base, exp);
        } else {
            res = expl(exp * logl(base));
        }
    } else {
        if (e_i) {
            res = s21_fast_pow(base, exp);
        } else {
            res = (long double)1 / expl(-exp * logl(base));
        }
    }

    return res;
}
