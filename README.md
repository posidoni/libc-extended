# S21_Decimal

## Table of contents
* [General info](https://github.com/AndreyZhelannikov/s21_decimal/tree/main#general-info)
* [Goal & requirements](https://github.com/AndreyZhelannikov/s21_decimal/tree/main#goal--requirements)
* [Key learnings](https://github.com/AndreyZhelannikov/s21_decimal/tree/main#key-learnings)
* [Build](https://github.com/AndreyZhelannikov/s21_decimal/tree/main#build)
* [Credits](https://github.com/AndreyZhelannikov/s21_decimal/tree/main#credits)

## General info 

Implementation of `decimal` value type in C language. This type represents 96-bit signed real number featuring opratinons without floating point imprecision. The library also provides an API for working with this type.

## Goal & requirements

In this project our task was to implement `decimal` type, that is 96-bit signed real number, and provide an API for working with it.

This type may be used instead of `IEEE 754` floats for calculations where floating point imprecision is unacceptable, for example, in financial transactions. 

`Decimal` also may be used as an analogue to Java `BigInteger` or 'BigInt' in JavaScript for scientific calculations.

## Key learnings
- Got familiar with basic matrices processing functions & their implementation
- Became more confident with using recursion (used for `determinant`, `calc_complements`, `inverse_matrix`)
- Discovered [GSL](https://www.gnu.org/software/gsl/) & used it for testing my functions
- Tried out Python & [Numpy](https://github.com/numpy/numpy) for testing correctness of my calculations

## Specification of `decimal`

### Type definition

``` c
    // insert our struct here

    typedef enum {
    s21_NORMAL_VALUE = 0,
    s21_INFINITY = 1,
    s21_NEGATIVE_INFINITY = 2,
    s21_NAN = 3
    } value_type_t;

    typedef struct 
    {
        int bits[4];
        value_type_t value_type;
    } s21_decimal;
```

The binary representation of a Decimal value consists of a 1-bit sign, a 96-bit integer number, and a scaling factor used to divide the 96-bit integer and specify what portion of it is a decimal fraction. The scaling factor is implicitly the number 10, raised to an exponent ranging from 0 to 28. Therefore, the binary representation of a Decimal value the form, ((-2^96 to 2^96) / 10^(0 to 28)), where -(2^96-1) is equal to MinValue, and 2^96-1 is equal to MaxValue.

Decimal number can be implemented as a four-element array of 32-bit signed integers (`int bits[4];`).

`bits[0]`, `bits[1]`, and `bits[2]` contain the low, middle, and high 32 bits of the 96-bit integer number accordingly.

`bits[3]` contains the scale factor and sign, and consists of following parts:
- Bits 0 to 15, the lower word, are unused and must be zero.
- Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the power of 10 to divide the integer number.
- Bits 24 to 30 are unused and must be zero.
- Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.

Note that the bit representation differentiates between negative and positive zero. These values can be treated as being equal in all operations.

### API Overview


### Arithmetic Operators

| Operator name | Operators  | Function | 
| ------ | ------ | ------ |
| Addition | + | s21_decimal s21_add(s21_decimal, s21_decimal) |
| Subtraction | - | s21_decimal s21_sub(s21_decimal, s21_decimal) |
| Multiplication | * | s21_decimal s21_mul(s21_decimal, s21_decimal) | 
| Division | / | s21_decimal s21_div(s21_decimal, s21_decimal) |
| Modulo | Mod | s21_decimal s21_mod(s21_decimal, s21_decimal) |

If an error occurs during the operation, the error type is written to the value_type variable  

*Note on the numbers that do not fit into the mantissa:*
- *When getting numbers that do not fit into the mantissa during arithmetic operations, use bank rounding (for example, 79,228,162,514,264,337,593,543,950,335 - 0.6 = 79,228,162,514,264,337,593,543,950,334)*

*Note on the mod operation:*
- *If an overflow occurred as a result, discard the fractional part (for example, 70,000,000,000,000,000,000,000,000,000 % 0.001 = 0.000)*


### Comparison Operators

| Operator name | Operators  | Function | 
| ------ | ------ | ------ |
| Less than | < | int s21_is_less(s21_decimal, s21_decimal) |
| Less than or equal to | <= | int s21_is_less_or_equal(s21_decimal, s21_decimal) | 
| Greater than | > |  int s21_is_greater(s21_decimal, s21_decimal) |
| Greater than or equal to | >= | int s21_is_greater_or_equal(s21_decimal, s21_decimal) | 
| Equal to | == |  int s21_is_equal(s21_decimal, s21_decimal) |
| Not equal to | != |  int s21_is_not_equal(s21_decimal, s21_decimal) |

Return value:
- 0 - TRUE
- 1 - FALSE

### Convertors and parsers

| Convertor/parser | Function | 
| ------ | ------ |
| From int  | int s21_from_int_to_decimal(int src, s21_decimal *dst) |
| From float  | int s21_from_float_to_decimal(float src, s21_decimal *dst) |
| To int  | int s21_from_decimal_to_int(s21_decimal src, int *dst) |
| To float  | int s21_from_decimal_to_float(s21_decimal src, float *dst) |

Return value - code error:
- 0 - SUCCESS
- 1 - CONVERTING ERROR

*Note on the conversion of a float type number:*
- *If the numbers are too small (0 < |x| < 1e-28), return an error and value equal to 0, value_type = 0*
- *If the numbers are too large (|x| > 79,228,162,514,264,337,593,543,950,335) or are equal to infinity, return an error and value_type of infinity with the corresponding sign*
- *When processing a number with the float type, convert all the digits contained in it*

*Note on the conversion from decimal type to int:*
- *If there is a fractional part in a decimal number, it should be discarded (for example, 0.9 is converted to 0)*


### Another functions

| Description | Function | 
| ------ | ------ |
| Rounds a specified Decimal number to the closest integer toward negative infinity. | s21_decimal s21_floor(s21_decimal) |	
| Rounds a decimal value to the nearest integer. | s21_decimal s21_round(s21_decimal) |
| Returns the integral digits of the specified Decimal; any fractional digits are discarded, including trailing zeroes. | s21_decimal s21_truncate(s21_decimal) |
| Returns the result of multiplying the specified Decimal value by negative one. | s21_decimal s21_negate(s21_decimal) |

## Build

```
$ git clone ..
$ cd repo/src/
$ make
```

## Credits
- Developers: [Mikhail Kuznetsov (@posidoni)](https://github.com/AndreyZhelannikov), [Andrey Jhelannikov(@capricey)](https://github.com/AndreyZhelannikov), [Stepan Fedorov (@nanadaug)](https://github.com/co-cy), [Anton Bezludniy(@tarticar)](https://github.com/bezlant).
- SC21 for providing this task as a part of our curriculum 🙂💚