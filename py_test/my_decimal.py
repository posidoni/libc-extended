from decimal import getcontext, Decimal
from random import randrange

getcontext().prec = 128


class MyDecimal:
    def __init__(self, number: str = None, exponent: int = None, decimal: Decimal = None, value: str = None):
        if number:
            number = number.replace(':', '').split('-')

            sign = -1 if int(number[0][0], base=2) else 1
            self.exponent = int(number[0][1:].replace('O', ''), base=2)

            value = int(''.join(number[1:]), base=2)
            self.decimal = Decimal(sign * value) / Decimal(10 ** self.exponent)
        elif decimal:
            self.exponent = exponent
            self.decimal = decimal
        elif value:
            self.exponent = exponent
            if exponent:
                self.exponent = exponent
            else:
                self.exponent = 0
            self.decimal = Decimal(value) / Decimal(10 ** self.exponent)
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
        tmp_exp = str(bin(self.exponent)).split('b')[-1]
        line += '0' * (8 - len(tmp_exp)) + tmp_exp
        for i in range(16):
            line += '0'

        tmp_int = str(bin(int(self.decimal * 10 ** self.exponent))).split('b')[-1]
        line += '0' * (96 - len(tmp_int)) + tmp_int
        return line

    def get_value(self) -> int:
        return int(self.decimal * 10 ** self.exponent)

    def __add__(self, other):
        if isinstance(other, self.__class__):
            min_exp = min(self.exponent, other.exponent)

            self.balancing(other)

            return MyDecimal(exponent=min_exp, decimal=self.decimal + other.decimal)

    def print(self, human: bool = False, base: bool = False):
        if human:
            print(f'{self.decimal:.28f}')

        if not human or base:
            print(self.to_bin_form())
