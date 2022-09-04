#!python3

from decimal import getcontext, Decimal
from random import randrange

getcontext().prec = 128


class MyDecimal:
    def __init__(self, number: str = None, exponent: int = None, decimal: Decimal = None, value: str = None):
        if number:
            number = number.split()

            sign = -1 if int(number[0][0], base=2) else 1
            self.exponent = int(number[0][8:16], base=2)

            value = int(''.join(number[1:]), base=2)
            self.decimal = Decimal(sign * value) / Decimal(10 ** self.exponent)
        elif decimal and exponent is not None:
            self.exponent = exponent
            self.decimal = decimal
        elif value:
            self.exponent = exponent if exponent else 0
            self.decimal = Decimal(value)
        else:
            sign = (-1 if randrange(0, 2) else 1)
            self.exponent = randrange(0, 29)
            self.decimal = Decimal(sign * randrange(0, 2 ** 96 - 1)) / Decimal(10 ** self.exponent)

    def balancing_decimal(self, new_exp: int):
        while new_exp:
            self.exponent -= 1
            self.decimal = round(self.decimal, self.exponent)

    def shifting(self, count):
        over = 0
        while not over and count:
            if self.decimal * 10 >= 2 ** 96:
                over = 1
            else:
                self.exponent += 1
            count -= 1

    def balancing(self, other):
        if isinstance(other, self.__class__):
            diff = self.exponent - other.exponent

            if diff:
                if diff > 0:
                    other.shifting(diff)
                else:
                    self.shifting(-diff)
            diff = self.exponent - other.exponent
            if diff:
                if diff > 0:
                    self.balancing_decimal(diff)
                else:
                    other.balancing_decimal(-diff)

    def to_bin_form(self):
        line = f"{'1' if self.decimal < 0 else '0'}"
        for i in range(7):
            line += '0'
        tmp_exp = str(bin(self.exponent))[2:]
        line += '0' * (8 - len(tmp_exp)) + tmp_exp
        for i in range(16):
            line += '0'

        tmp_int = str(bin(int(self.decimal * 10 ** self.exponent)))[2:]
        line += '0' * (96 - len(tmp_int)) + tmp_int
        return line

    def print(self, human: bool = False, base: bool = False):
        if (human):
            print(f'\t\t{self.decimal:.28f}')

#define RED "\033[0;31m"
#define BRED "\033[1;31m"
#define URED "\033[4;31m"
#define RESET "\033[0m"
#define REDB "\033[41m"
#define REDHB "\033[0;101m"
#define HRED "\033[0;91m"
#define BHRED "\033[1;91m"
#define GRN "\033[0;92m"
#define PRETTY_PRINT(name) (UGRN name ENDCOLOR)
#define UGRN "\033[4;32m"
#define ENDCOLOR "\033[0m"

        if (not human or base):
            print(self.to_bin_form())

    def __add__(self, other):
        if isinstance(other, self.__class__):
            min_exp = min(self.exponent, other.exponent)

            self.balancing(other)

            return MyDecimal(exponent=min_exp, decimal=self.decimal + other.decimal)


a = MyDecimal(number=input())
a.print(human=True)
