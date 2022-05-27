#include "s21_decimal.h"

/* https://stackoverflow.com/questions/8981913/how-to-perform-round-to-even-with-floating-point-numbers
 */

int s21_round(s21_decimal value, s21_decimal *result);
// s21_decimal s21_round(s21_decimal n) {
//     if (n.value_type == s21_NORMAL_VALUE) {
//         int exp = get_exponent(n);
//         if (exp && IS_SET(n.bits[0], (exp - 1))) {
//             // handle tie: check if bits before are set for 100 case (tie)
//             if (!(IS_SET(n.bits[0], (exp - 2))) &&
//                 !(IS_SET(n.bits[0], (exp - 3)))) {
//                 if (IS_SET(n.bits[0], exp)) {
//                     s21_decimal add_to_round = {0};
//                     ADD_BIT(add_to_round.bits[0], exp);
//                     n = s21_add(n, add_to_round);
//                 }
//             } else {
//                 s21_decimal add_to_round = {0};
//                 ADD_BIT(add_to_round.bits[0], exp);
//                 n = s21_add(n, add_to_round);
//             }
//         }
//     }
//     return n;
// }
