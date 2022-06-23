from my_decimal import MyDecimal
from sys import argv


def print_truncate_testcase():
    a = MyDecimal()
    a.print()

    new_a = MyDecimal(exponent=0, decimal=(a.decimal // 1))
    new_a.decimal = a.decimal // 1
    new_a.print()

    # a.print(human=True)
    # new_a.print(human=True)


if __name__ == '__main__':
    for i in range(int(argv[1]), -1, -1):
        print_truncate_testcase()
