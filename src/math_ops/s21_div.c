#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int code = 0;
    *result = binary_division(value_1, value_2, &code);
    return code;
}

s21_decimal binary_division(s21_decimal value_1, s21_decimal value_2, int *code) {
    if (s21_is_equal(value_2, get_power_of_ten(0))) return value_1;

    s21_decimal result = {0};
    for (int i = 94; i >= 0; --i) {
        if (s21_is_less_or_equal(shiftnl_ret(value_2, i), value_1)) {
            value_1 = binary_subtraction(value_1, shiftnl_ret(value_2, i), code);
            result = bit_or(result, shiftnl_ret(get_power_of_ten(0), i));
        }
    }
    return result;
}
/*
  long long quotient = 0, temp = 0;

  // test down from the highest bit and
  // accumulate the tentative value for
  // valid bit
  for (int i = 31; i >= 0; --i) {

    if (temp + (divisor << i) <= dividend) {
      temp += divisor << i;
      quotient |= 1LL << i;
    }
  }
  //if the sign value computed earlier is -1 then negate the value of quotient
  if(sign==-1) quotient=-quotient;

  return quotient;
*/
/*s21_decimal binary_division(s21_decimal value_1, s21_decimal value_2, int
*code) { s21_decimal one = {0}; s21_decimal quotient = {0}; s21_decimal temp =
{0};

    set_bit_1(&one, 95);

    for (int i = 95; i >= 0; --i) {
        // printf("%d : ", i);
        // print_bits_r(one);
        if (s21_is_less_or_equal(binary_addition(temp, shiftnl_ret(value_2, i),
code), value_1)) { printf("I: %d\n", i); temp = binary_addition(temp,
shiftnl_ret(value_2, i), code); quotient = bit_or(quotient, one);
        }
        shiftr(&one);
    }
    set_exponent(&quotient, 0);
    return quotient;
}
*/

/*
public static void DivMod (Int128 dividend, Int128 divisor, out Int128 quotient,
out Int128 remainder)
{
    quotient = dividend;
    remainder = 0;
    for (int i = 0; i < 128; i++)
    {
        // Left shift Remainder:Quotient by 1
        remainder <<= 1;
        if (quotient < 0)
            remainder._lo |= 1;
        quotient <<= 1;

        if (remainder >= divisor)
        {
            remainder -= divisor;
            quotient++;
        }
    }
}
*/

// s21_decimal binary_division(s21_decimal value_1, s21_decimal value_2, int *code) {
//     s21_decimal quotient = value_2;
//     s21_decimal remainder = {0};

//     for (int i = 95; i >= 0; --i) {
//         shiftl(&remainder);
//         shiftl(&quotient);

//         if (s21_is_greater_or_equal(remainder, value_2)) {
//             remainder = binary_subtraction(remainder, value_2, code);
//             quotient = binary_addition(quotient, get_power_of_ten(0), code);
//         }
//     }
//     return quotient;
// }

/*
 for i in range(31,-1,-1): # starting our loop

        if b << i <= a  : # checking if b multiplied by 2**i is <= a
            a -= b << i   # subtracting b << i from a
            ans += 1 << i # adding 2 power i to the answer

*/
