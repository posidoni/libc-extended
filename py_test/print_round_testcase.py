from decimal import Decimal, ROUND_HALF_UP
from my_decimal import MyDecimal
from sys import argv


def print_round_testcase():
    a = MyDecimal()
    a.print()

    new_a = MyDecimal(exponent=0, decimal=Decimal(round(a.decimal)))
    new_a.decimal = a.decimal.quantize(Decimal('1.'), rounding=ROUND_HALF_UP)
    new_a.print()

    # a.print(human=True)
    # new_a.print(human=True)


if __name__ == '__main__':
    for i in range(int(argv[1]), -1, -1):
        print_round_testcase()
