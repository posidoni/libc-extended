#include "s21_math.h"

long double s21_tan(double x) {
    if (is_nan(x) || !is_finite(x)) return S21_NAN;
    x = fmodl(x, 2 * M_PI);
    return s21_sin(x) / s21_cos(x);
}

// Not working
// long double s21_tan(double x) {
//     static int test_n = 0;
//     printf("TESTN:%d : %lf", test_n++, x);

//     long double res = 0;
//     long double m = 1;

//     x = s21_fmod(x, S21_M_PI);
//     if (x < 0) {
//         x = -x;
//         m = -m;
//     }
//     if (x > S21_M_PI_2) {
//         x = x - S21_M_PI;
//         printf("  : 1 ");
//     }
//     int rev = 0;
//     if (x > M_PI_2 / 2.0) {
//         printf(" 2 ");
//         x = M_PI_2 - x;
//         rev = 1;
//     }
//     if (x > M_PI_2 / 4.0) {
//         printf(" 3 ");
//         long double tan_2 = x / 2.0 + (powl(x / 2.0, 3.0) / 3.0) + (2.0 * powl(x / 2.0, 5.0) / 15.0) +
//                             (17.0 * powl(x / 2.0, 7.0) / 315.0) + (62.0 * powl(x / 2.0, 9.0) / 2835.0);
//         if (rev)
//             res = (1.0 - powl(tan_2, 2) / (2.0 * tan_2));
//         else
//             res = (2.0 * tan_2) / (1.0 - powl(tan_2, 2));
//         rev = 0;
//     } else {
//         res = x + (powl(x, 3.0) / 3.0) + (2.0 * powl(x, 5.0) / 15.0) + (17.0 * powl(x, 7.0) / 315.0) +
//               (62.0 * powl(x, 9.0) / 2835.0);
//     }
//     if (rev) res = 1.0 / res;

//     printf("\n");

//     return res * m;
// }
