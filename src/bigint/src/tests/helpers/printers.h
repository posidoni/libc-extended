#ifndef PRINTERS_H_
#define PRINTERS_H_

#include "../../s21_decimal.h"

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

void print_bits_set(s21_decimal d, int set_n);
void print_bits_r_set(s21_decimal d, int set_n);
void print_bits(s21_decimal d);
void print_bits_r(s21_decimal d);
void print_string(char *src, s21_decimal d);

#endif  // PRINTERS_H_
