from my_decimal import MyDecimal
from random import randrange
from sys import argv


def print_less_testcase():
    a = MyDecimal()
    a.print()
    # a.print(human=True)

    b = MyDecimal()
    b.print()

    print("YES" if a.decimal < b.decimal else "NO")


if __name__ == '__main__':
    if len(argv) == 1:
        argv.append(0)
    for i in range(int(argv[1]), -1, -1):
        print_less_testcase()
