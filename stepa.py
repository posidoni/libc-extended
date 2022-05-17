#!python3
import math

# // In the case of the natural logarithm, there is an easy way to reduce the range. Real numbers are almost universally represented in terms of a mantissa and an exponent: x=m*2p, where p is an integer and m is between 1 and 2. Thus log(x) = log(m)+p*log(2). The latter term, p*log(2), is just a multiplication by a known constant. The problem thus reduces to finding the logarithm of a number between 1 and 2 (or between 1/2 and 1). A further range reduction can be made by using the fact that √2 is logarithmically in the middle of [1,2). Thus all that is needed is a way to calculate the logarithm of a number between 1 and √2. This is typically done with a rational polynomial. The ratio of a second order polynomial polynomial to a third order works quite nicely for this.

def s21_log(x):
    res = 0
    log2 = 0.6931471805599453

    if x <= 2.0:
        for i in range(1, 100):
            a = pow(-1, i)
            b = pow((-1 + x), i)
            res -= (a * b) / i
    else:
        m = 0.0
        p = 0
        while x > 2:
            m =  x / 2.0
            x /= 2.0
            p += 1

        print(m, p, x)
        res = s21_log(m) + (p) * log2

    return res

if __name__ == "__main__":
    print(s21_log(0.3))
    print(math.log(0.3))

    print(s21_log(5))
    print(math.log(5))



    print(s21_log(1))
    print(math.log(1))

    print(math.log(500))
    print(math.log(500))


