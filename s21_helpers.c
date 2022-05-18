#include "s21_math.h"

/* God, I wish C had C++ templates & overloading ... (~Misha) */

s21_bool s21_ldeq(long double a, long double b) { return (a < b + EPS_8 && a > b - EPS_8); }

s21_bool s21_deq(double a, double b) { return (a < b + EPS_8 && a > b - EPS_8); }

s21_bool s21_feq(float a, float b) { return (a < b + EPS_8 && a > b - EPS_8); }
