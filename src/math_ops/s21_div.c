#include "../s21_decimal.h"

s21_decimal binary_division(s21_decimal value_1, s21_decimal value_2, int *err);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int code = 0;
    *result = binary_division(value_1, value_2, &code);
    return code;
}

/*
public static void DivMod (Int128 dividend, Int128 divisor, out Int128 quotient, out Int128 remainder)
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

 for i in range(31,-1,-1): # starting our loop

        if b << i <= a  : # checking if b multiplied by 2**i is <= a
            a -= b << i   # subtracting b << i from a
            ans += 1 << i # adding 2 power i to the answer

*/
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
s21_decimal binary_division(s21_decimal value_1, s21_decimal value_2, int *code) {
    s21_decimal one;
    s21_decimal quotient;
    s21_decimal temp;
    init_zero(&one);
    init_zero(&quotient);
    init_zero(&temp);

    set_bit_1(&one, 95);

    for (int i = 95; i >= 0; --i) {
        if (s21_is_less_or_equal(binary_addition(temp, shiftnl_ret(value_2, i), code), value_1)) {
            printf("I: %d\n", i);
            temp = binary_addition(temp, shiftnl_ret(value_2, i), code);
            quotient = bit_or(quotient, one);
        }
        shiftr(&one);
    }
    print_bits_r(temp);
    set_exponent(&quotient, 0);
    return quotient;
}
