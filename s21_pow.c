#include "s21_math.h"
#include "math.h"

long double s21_pow(double base, double exp) {
    // TODO REPLACE MATH 2 S21_MATH
    long double res;
    if (base > EPS) {
        if (fabs(exp) > EPS) {
            res = expl(exp * logl(base));
        } else {
            res = (long double) 1 / expl(-exp * logl(base));
        }
    } else {
        res = -NAN;
    }
    return res;
}

//int main() {
//    long double base = -8;
//    long double exp = 0.3;
//    printf("%Lf\n%Lf", s21_pow(base, exp), powl(base, exp));
//}