from py_test import MyDecimal

decimal = MyDecimal(input().strip('\" '))

print("\tEXPONENT:\t\t\t", decimal.exponent)
print(f"\tFINALY:\t\t\t\t{decimal.decimal:.28f}")
# print()
