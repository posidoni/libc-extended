#!python3
import math


def s21_acos(x):
    res = 0.0

    res = math.atan(math.sqrt(1 - pow(x, 2)) / x)

    return res

if __name__ == "__main__":
    print(s21_acos(0.3))
    print(math.acos(0.3))
    