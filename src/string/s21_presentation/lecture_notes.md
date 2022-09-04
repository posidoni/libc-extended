# [Lecture Link](https://www.youtube.com/watch?v=ks3Banj3j7g)

# I. Инструменты разработчика & командная работа

## (1) Debugging C/C++ Code - GDB / LLDB
- [LLDB VSCode extension](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb)
    - Minimal .json config (check docs)
- [Online GDB](https://www.onlinegdb.com/) for debugging very small functions

## (2) ASan - Address sanitizer
- [Доклад Алексея Веселовского на C++ Russia](https://www.youtube.com/watch?v=7WyBAUJ8UA8) - обязательно рекомендуется к просмотру
- `-fsanitize=address` на стадию компиляции и линковки
- НЕ сдавать Вертеру с этим флагом. Использовать исключительно при разработке.
- Находит не все, но большинство ошибок
- Не сочетается с gcov, valgrind, leaks
- Очень помогает с heap/stack buffer overflow, heap use after free, etc.

## (3) Git / Trello / Notion 
- [Git Book](https://git-scm.com/book/en/v2) - для асинхронной работы
- [Test Driven Development](https://en.wikipedia.org/wiki/Test-driven_development) - обязательно к прочтению

## (4) Valgrind
- [Valgrind для школьных маков](https://github.com/LouisBrunner/valgrind-macos)
- Рекомендуемая команда для запуска VG: `valgrind --leak-check=full --show-leak-kinds=all --track-origins=y    es --verbose --log-file=valgrind-report.txt"`
- Предварительно *обязательно* ставить NOFORK_MODE во фреймфорке Check

# II. Стандартная библиотека. Сборка проекта

## Makefile
- 2 набора объектных файлов:
    - чистые (для сборки статической либы)
    - с gcov флагами
- Вертер НЕ проверяет тесты, при автопроверке используется только s21_string.a
- Рекомендуемая структура проекта:

```
> src
    - Makefile
    - s21_string.a
    - s21_string.h
    - s21_strtok.c
    - s21_sprintf.c
    ...
    - s21_strlen.c

    > tests
        > objs
        - s21_tests.h
        - test_s21_strlen.c
    > objs
```


# III. C# String Class

## Основные моменты:
- Данный бонус настоятельно рекомендуется делать, т.к. в нем не очень сложные функции
- Все malloc / calloc должны быть защищены. Это делается следующим образом:

``` c
/* Incorrect (!) */

char *my_str = malloc(sizeof(char) * 100);

for (int i = 0; i < 100; i++) {
    my_str[i] = 'A'; // Possible NULL ptr dereference !
}


/* Correct (!) */

char *my_str = malloc(sizeof(char) * 100);

if (my_str) {
    for (int i = 0; i < 100; i++) {
        my_str[i] = 'A'; // Possible NULL ptr dereference !
    }
    free(my_str);
} else {
    /* Malloc returned NULL, usually this means OOM */
    perror("Error!");
}
```
- В тестах после использования функций рекомендуется делать free


