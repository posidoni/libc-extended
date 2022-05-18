#include "s21_math.h"

/* God, I wish C had C++ templates & overloading ... (~Misha) */

<<<<<<< HEAD
s21_bool s21_ldeq(long double a, long double b) { return (a < b + EPS_8 && a > b - EPS_8); }

s21_bool s21_deq(double a, double b) { return (a < b + EPS_8 && a > b - EPS_8); }

s21_bool s21_feq(float a, float b) { return (a < b + EPS_8 && a > b - EPS_8); }
=======
s21_bool s21_ldeq(long double a, long double b) {
    // TODO fabs(a - b) < EPS) ? why not? [OPTIONAL]
    return (a < b + EPS_8 && a > b - EPS_8);
}

s21_bool s21_deq(double a, double b) {
    // TODO fabs(a - b) < EPS) ? why not? [OPTIONAL]
    return (a < b + EPS_8 && a > b - EPS_8);
}

s21_bool s21_feq(float a, float b) {
    // TODO fabs(a - b) < EPS) ? why not? [OPTIONAL]
    return (a < b + EPS_8 && a > b - EPS_8);
}
>>>>>>> 85ddb17 (Add TODO)
