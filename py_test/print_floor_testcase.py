from my_decimal import MyDecimal
from decimal import Decimal
from math import floor
from sys import argv


def print_round_testcase():
    a = MyDecimal()
    a.print()

    new_a = MyDecimal(exponent=0, decimal=Decimal(floor(a.decimal)))
    new_a.decimal = Decimal(floor(a.decimal))
    new_a.print()

    # a.print(human=True)
    # new_a.print(human=True)


if __name__ == '__main__':
    for i in range(int(argv[1]), -1, -1):
        print_round_testcase()
