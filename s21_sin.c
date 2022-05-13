#include "s21_math.h"

long double s21_sin(double x) {
    long double tmp = (long double)x;
    // fmod(tmp, M_PI / 180.0);
    //  printf("%Lf\n", 180.0 / M_PI);
    //  fmod(x, (180.0 / M_PI));  // s21_fmod (!)
    long double res = 0;
    for (int i = 0; i < 5 && (2 * i + 1) <= 20; i++) {
        // printf("%Lf\n", pow(x, 2 * i + 1));
        // printf("%Lf\n", pow(-1, i));

        res += pow(-1, i) * (pow(x, 2 * i + 1) / (long double)factorials[2 * i + 1]);  // s21_pow (!)
        // printf("RES%d: %Lf\n", i, res);
    }
    return res;
}