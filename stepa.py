#!python3
import math
from xml.etree.ElementTree import PI

# // In the case of the natural logarithm, there is an easy way to reduce the range. Real numbers are almost universally represented in terms of a mantissa and an exponent: x=m*2p, where p is an integer and m is between 1 and 2. Thus log(x) = log(m)+p*log(2). The latter term, p*log(2), is just a multiplication by a known constant. The problem thus reduces to finding the logarithm of a number between 1 and 2 (or between 1/2 and 1). A further range reduction can be made by using the fact that √2 is logarithmically in the middle of [1,2). Thus all that is needed is a way to calculate the logarithm of a number between 1 and √2. This is typically done with a rational polynomial. The ratio of a second order polynomial polynomial to a third order works quite nicely for this.

def s21_acos(x):
    # res = math.sqrt(2 - 2 * x)
    res = math.pi / 2
    sum = 0

    for i in range(0, 30):
        sum += (pow(x, 1+2*i) * pow(0.5, i)) / (math.factorial(i) + 2 * i * math.factorial(i))


    return res - sum

if __name__ == "__main__":
    print(s21_acos(-0.3))
    print(math.acos(-0.3))



