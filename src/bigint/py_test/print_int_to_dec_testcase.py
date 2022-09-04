from my_decimal import MyDecimal
from random import randrange
from sys import argv


def print_int_to_dec_testcase():
    a = MyDecimal(exponent=0, value=str(randrange(-1 * 2 ** 31, 2 ** 31 - 1)))
    print(int(a.decimal))
    a.print()


if __name__ == '__main__':
    for i in range(int(argv[1]), -1, -1):
        print_int_to_dec_testcase()
