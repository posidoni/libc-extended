#include "s21_decimal.h"
#define DEBUG

#ifdef DEBUG
void print_bits(s21_decimal d);
#endif

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// int s21_add(s21_decimal a, s21_decimal b) {
//     s21_decimal res = {0};
//     // a negative b positive
//     if (get_sign(a) && !get_sign(b)) {
//         res = s21_sub(b, a);
//         // a positive b negative
//     } else if (!get_sign(a) && get_sign(b)) {
//         res = s21_sub(a, b);
//         // both positive
//     } else {
//         res = add(a, b);
//     }
//     return res;
// }
//
// int add(s21_decimal a, s21_decimal b) {
//     // FIXES NEEDED! TURNS OUT '.' CAN BE AT ANY POSITION UP TO 28
//     s21_decimal res = {0};
//     if (!get_exponent(a) && !get_exponent(b))
//         res = add_integers(a, b);
//     else
//         res = add_floats(a, b);
//     return res;
// }
//
//// msb = most significant bit
// int check_overflow(s21_decimal val, int msb) {
//     int res = IS_SET(val.bits[0], msb);
//     return res;
// }
//
// s21_decimal add_integers(s21_decimal a, s21_decimal b) {
//     s21_decimal res = {0};
//     unsigned int *b1 = a.bits;
//     unsigned int *b2 = b.bits;
//     bool cf = false;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 32; j++) {
//             int current = cf + IS_SET(b1[i], j) + IS_SET(b2[i], j);
//             if (current == 3) {
//                 ADD_BIT(res.bits[i], j);
//                 cf = true;
//             }
//             if (current == 2) {
//                 cf = true;
//             }
//             if (current == 1) {
//                 ADD_BIT(res.bits[i], j);
//                 cf = false;
//             }
//         }
//         if (cf)
//             return S21_INFINITY;
//     }
//     return res;
// }
//
#ifdef DEBUG
void print_bits(s21_decimal d) {
    for (int i = 0; i < 3; i++) {
        int x = 3;
        for (int j = 0; j < 32; j++) {
            printf("%u", IS_SET(d.bits[i], j));
            if (j == x && !(i == 2 && j == 31)) {
                x += 4;
                printf(" ");
            }
        }
    }
    printf("\n");
}
#endif
