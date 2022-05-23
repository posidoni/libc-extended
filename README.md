## Table of contents
* [General info](https://github.com/MikhailKuzntsov1/s21_math/tree/main#general-info)
* [Goal & requirements](https://github.com/MikhailKuzntsov1/s21_math/tree/main#goal--requirements)
* [Key learnings](https://github.com/MikhailKuzntsov1/s21_math/tree/main#key-learnings)
* [Build](https://github.com/MikhailKuzntsov1/s21_math/tree/main#build)
* [Overview of implemented functions](https://github.com/MikhailKuzntsov1/s21_math/tree/main#overview-of-implemented-functions)
* [Credits](https://github.com/MikhailKuzntsov1/s21_math/tree/main#credits)

## General info 

Implementation of some libc `math.h` functions with at least 1e-6 precision. Fully covered by
unit-tests.

## Goal & requirements 

The goal of this project was to learn how core mathematical functions are implemented in computers. In order to achieve
desired precision with reasonable performance our team had to learn different optimization methods. This project was
especially valuable for those team members who were not familiar with Taylor polynomial series and underlying
mathematical formulas.

## Key learnings
- 'Peculiarities' of working with floats (correct comparison, role of EPS, precision, etc.)
- Some interesting math algos (Quake 3 fast isqrt, Newton method, Taylor series, etc.)
- Refreshed trigonometry, learned useful optimization formulas
- Taylor polynomial series

## Overview of implemented "math.h" functions

| No. | Function | Description |
| --- | -------- | ----------- |
| 1 | `int abs(int x)` | computes absolute value of an integer value |
| 2 | `long double acos(double x)` | computes arc cosine |
| 3 | `long double asin(double x)` | computes arc sine |
| 4 | `long double atan(double x)` | computes arc tangent |
| 5 | `long double ceil(double x)` | returns the nearest integer not less than the given value |
| 6 | `long double cos(double x)` | computes cosine |
| 7 | `long double exp(double x)` | returns e raised to the given power |
| 8 | `long double fabs(double x)` | computes absolute value of a floating-point value |
| 9 | `long double floor(double x)` | returns the nearest integer not greater than the given value |
| 10 | `long double fmod(double x, double y)` | remainder of the floating-point division operation |
| 11 | `long double log(double x)` | computes natural logarithm |
| 12 | `long double pow(double base, double exp)` | raises a number to the given power |
| 13 | `long double sin(double x)` | computes sine |
| 14 | `long double sqrt(double x)` | computes square root |
| 15 | `long double tan(double x)` | computes tangent |  

## Build

```
$ git clone ...
$ cd repo/src/
$ make test
$ ./test
$ make gcov_report /* To check test coverage, requires lcov utility */
```

## Credits
- Developers: [Mikhail Kuznetsov (@posidoni)](https://github.com/MikhailKuzntsov1), [Andrey Jhelannikov(@capricey)](https://github.com/AndreyZhelannikov), [Stepan Fedorov (@nanadaug)](https://github.com/co-cy), [Anton Bezludniy(@tarticar)](https://github.com/bezlant).
- Any feedback & bug-reports are highly appreciated! 
- SC21 for providing this task 🙂💚
