from my_decimal import MyDecimal
from sys import argv


def print_testcase():
    a = MyDecimal()
    a.print()

    a.decimal = a.decimal * -1
    a.print()

    # a.print(human=True)
    # new_a.print(human=True)


if __name__ == '__main__':
    for i in range(int(argv[1]), -1, -1):
        print_testcase()
