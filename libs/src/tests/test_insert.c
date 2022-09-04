#include "../tests_includes/s21_tests.h"

START_TEST(insert_test1) {
    char src[] = "Shlepa";
    char str[] = "I love my . He is very kind!";
    s21_size_t index = 10;
    char expected[] = "I love my Shlepa. He is very kind!";
    char *got = (char *)s21_insert(src, str, index);
    ck_assert_str_eq(got, expected);
    if (got) free(got);
} END_TEST


START_TEST(insert_test2) {
    char src[] = "Hello, ";
    char str[] = "Aboba!";
    s21_size_t index = 0;
    char expected[] = "Hello, Aboba!";
    char *got = (char *)s21_insert(src, str, index);
    ck_assert_str_eq(got, expected);
    if (got) free(got);
} END_TEST


START_TEST(insert_test3) {
    char src[] = "";
    char str[] = "";
    s21_size_t index = 100;
    char *expected = NULL;
    char *got = (char *)s21_insert(src, str, index);
    ck_assert_ptr_eq(got, expected);
    if (got) free(got);
} END_TEST


START_TEST(insert_test4) {
    char *src = NULL;
    char *str = NULL;
    s21_size_t index = 100;
    char *expected = NULL;
    char *got = (char *)s21_insert(src, str, index);
    ck_assert_ptr_eq(got, expected);
    if (got) free(got);
} END_TEST


START_TEST(insert_test5) {
    char src[] = "Monkey";
    char str[] = "Space  ";
    s21_size_t index = 6;
    char expected[] = "Space Monkey ";
    char *got = (char *)s21_insert(src, str, index);
    ck_assert_str_eq(got, expected);
    if (got) free(got);
} END_TEST

Suite *suite_insert(void) {
    Suite *s = suite_create("suite_insert");
    TCase *tc = tcase_create("insert_tc");

    tcase_add_test(tc, insert_test1);
    tcase_add_test(tc, insert_test2);
    tcase_add_test(tc, insert_test3);
    tcase_add_test(tc, insert_test4);
    tcase_add_test(tc, insert_test5);

    suite_add_tcase(s, tc);
    return s;
}
