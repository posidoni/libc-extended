## Table of contents
* [General info](https://github.com/MikhailKuzntsov1/s21_string/tree/main#general-info)
* [Goal & requirements](https://github.com/MikhailKuzntsov1/s21_string/tree/main#goal--requirements)
* [Key learnings](https://github.com/MikhailKuzntsov1/s21_string/tree/main#key-learnings)
* [Build & usage](https://github.com/MikhailKuzntsov1/s21_string/tree/main#build)
* [Credits](https://github.com/MikhailKuzntsov1/s21_string/tree/main#credits)

### Overview of some "math.h" functions

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

## General info 

Implementation of some libc `math.h` functions with at least 1e-6 precision. Fully covered by
unit-tests.

Implementation of libc `string.h` functions with some additions, including `sscanf` and `ssprintf` with all specifiers and flags. Fully covered with unit-tests under TDD approach. 

<div align="center"><img src="assets/build_launch.gif"></div>
<div align="center"><sub>Build & launching unit-tests</sub></div>

## Goal & requirements 
The goal of this project was to get comfortable with strings handling in C, explore tokenization and solidify our knowledge & skills of structured programming, while trying to replicate libc strings handling functions.

## Key learnings
- Working with strings in C
- Functions with variable number of arguments
- Creating & linking static libs, building project with Makefile
- Unit-testing with Check framework, exploring TDD approach
- Exploring & evaluating test coverage with gcov

The most valuable discovery out of all of them is definitely TDD methodology. The experience of getting instant feedback by unit tests while writing `sscanf` was invaluable and kept me motivated during refactoring & bug fixes sessions.

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
- Peer reviewers: @gerardys (Vlad), [@sparelis (Dasha)](https://github.com/GrusnyDance), [@deltajed (Ramin)](https://github.com/RamaObama) & others.
- Our team's lecture on this project is available on [Youtube (in Russian)](https://www.youtube.com/watch?v=ks3Banj3j7g). Any feedback & bug-reports are highly appreciated! 
- SC21 for providing this task 🙂💚
- Unfortunately, commit history was lost after migrating repo from Gitlab to Github :(