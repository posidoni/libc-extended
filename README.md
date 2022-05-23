## General info 
Implementation of libc `string.h` functions with some additions, including `sscanf` and `ssprintf` with all specifiers and flags. Fully covered with unit-tests under TDD approach. 

![build_launch_gif](assets/build_launch.gif)

## Table of contents
* [General info](##General info)
* [Goal & requirements](##Goal & requirements)
* [Key learnings](##Key learnings)
* [Build & usage](##Build & usage)
* [Credits](##Credits)

## Goal & requirements 
The goal of this project was to get comfortable with strings handling in C, explore tokenization and solidify our knowledge & skills of structured programming. 

## Key learnings
- Working with strings in C
- Functions with variable number of arguments
- Creating & linking static libs, building project with Makefile
- Unit-testing with Check framework, exploring TDD approach
- Exploring & evaluating test coverage with gcov

The most valuable discovery out of all of them is definitely TDD methodology. The experience of getting instant feedback by unit tests while writing `sscanf` was invaluable and kept me motivated during refactoring & bug fixes sessions.

## Build & usage
```
$ git clone ...
$ cd repo/src/
$ make test
$ ./test
$ make gcov_report /* To check test coverage, requires lcov utility */
```
## Credits
- Developers: [Mikhail Kuznetsov (@posidoni)](https://github.com/MikhailKuzntsov1), [Andrey Jhelannikov(@capricey)](https://github.com/AndreyZhelannikov),[Stepan Fedorov (@nanadaug)](https://github.com/co-cy), [Anton Bezludniy(@tarticar)](https://github.com/bezlant) 
- Peer reviewers: @gerardys (Vlad), [@sparelis (Dasha)](https://github.com/GrusnyDance), [@deltajed (Ramin)](https://github.com/RamaObama) & others 
- Our team's lecture on this project is available on [Youtube (in Russian)](https://www.youtube.com/watch?v=ks3Banj3j7g). Any feedback & bug-reports are highly appreciated! 
- SC21 for providing this task 🙂💚
- Unfortunately, commit history was lost after migrating repo from Gitlab to Github :(