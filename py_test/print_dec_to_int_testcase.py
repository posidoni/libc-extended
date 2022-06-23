from my_decimal import MyDecimal
from sys import argv


def print_dec_to_int_testcase():
    a = MyDecimal()
    a.print()
    g = abs(int(a.decimal))
    print(f'{"-" if a.decimal < 0 else ""}{g % 2**31}')


if __name__ == '__main__':
    for i in range(int(argv[1]), -1, -1):
        print_dec_to_int_testcase()
