#!python3
import math

def s21_atan(x):
    magic = (math.pi * math.sqrt(pow(x, 2))) / (2 * x)
    print(magic)
    res = 0

    for i in range(0, 5):
        res += (pow(-1, i) * pow(x, (-1 - 2*i))) / (1 + 2 * i)


    return magic - res

if __name__ == "__main__":
    print(s21_atan(2))
    print(math.atan(2))
