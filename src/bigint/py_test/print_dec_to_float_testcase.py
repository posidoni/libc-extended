from my_decimal import MyDecimal
from sys import argv


def print_dec_to_float_testcase():
    a = MyDecimal()
    a.print()
    a.print(human=True)


if __name__ == '__main__':
    for i in range(int(argv[1]), -1, -1):
        print_dec_to_float_testcase()
