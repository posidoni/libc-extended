from my_decimal import MyDecimal
from random import randrange
from sys import argv


def print_eq_testcase():
    a = MyDecimal()
    a.print()
    # a.print(human=True)

    if randrange(0, 2):
        if 28 - len(str(a.get_value())) > 0:
            add_exp = randrange(0, 28 - len(str(a.get_value())) + 1)
        else:
            add_exp = 0
        new_exp = a.exponent + add_exp
        b = MyDecimal(exponent=new_exp, value=str(a.get_value() * (10 ** add_exp)))
        b.print()
        # b.print(human=True)
        print("YES")
    else:
        b = MyDecimal()
        b.print()
        # b.print(human=True)
        print("NO")


if __name__ == '__main__':
    if len(argv) == 1:
        argv.append(0)
    for i in range(int(argv[1]), -1, -1):
        print_eq_testcase()
