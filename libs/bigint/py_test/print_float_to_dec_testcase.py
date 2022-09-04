from my_decimal import MyDecimal
from sys import argv


def print_float_to_dec_testcase():
    a = MyDecimal()
    a.print(human=True)
    a.print()


if __name__ == '__main__':
    for i in range(int(argv[1]), -1, -1):
        print_float_to_dec_testcase()
