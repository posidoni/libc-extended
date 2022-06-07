#include "../../s21_decimal_test.h"

START_TEST(NULL_POINTER) {
    int test_int = 0;
    s21_decimal *decimal = NULL;
    convertation_result status = s21_from_int_to_decimal(test_int, decimal);
    ck_assert_int_eq(status, CONVERTATION_ERROR);
}

START_TEST(ZERO_INT) {
    int test_int = 0;
    s21_decimal *decimal = malloc(sizeof(s21_decimal));
    convertation_result status = s21_from_int_to_decimal(test_int, decimal);
    ck_assert_int_eq(status, CONVERTATION_OK);
    ck_assert_int_eq(test_int, decimal->bits[0]);
    ck_assert_int_eq(0, decimal->bits[1]);
    ck_assert_int_eq(0, decimal->bits[2]);
    ck_assert_int_eq(0, get_sign(*decimal));
    ck_assert_int_eq(0, get_exponent(*decimal));
    free(decimal);
}

START_TEST(MAX_INT) {
    int test_int = INT32_MAX;
    s21_decimal *decimal = malloc(sizeof(s21_decimal));
    convertation_result status = s21_from_int_to_decimal(test_int, decimal);
    ck_assert_int_eq(status, CONVERTATION_OK);
    ck_assert_int_eq(test_int, decimal->bits[0]);
    ck_assert_int_eq(0, decimal->bits[1]);
    ck_assert_int_eq(0, decimal->bits[2]);
    ck_assert_int_eq(0, get_sign(*decimal));
    ck_assert_int_eq(0, get_exponent(*decimal));
    free(decimal);
}

START_TEST(MIN_INT) {
    int test_int = INT32_MIN + 1;
    s21_decimal *decimal = malloc(sizeof(s21_decimal));
    convertation_result status = s21_from_int_to_decimal(-test_int, decimal);
    ck_assert_int_eq(status, CONVERTATION_OK);
    ck_assert_int_eq(-test_int, decimal->bits[0]);
    ck_assert_int_eq(0, decimal->bits[1]);
    ck_assert_int_eq(0, decimal->bits[2]);
    ck_assert_int_eq(0, get_sign(*decimal));
    ck_assert_int_eq(0, get_exponent(*decimal));
    free(decimal);
}

START_TEST(NEG_INT) {
    int test_int = -126123;
    s21_decimal *decimal = malloc(sizeof(s21_decimal));
    convertation_result status = s21_from_int_to_decimal(-test_int, decimal);
    ck_assert_int_eq(status, CONVERTATION_OK);
    ck_assert_int_eq(-test_int, decimal->bits[0]);
    ck_assert_int_eq(0, decimal->bits[1]);
    ck_assert_int_eq(0, decimal->bits[2]);
    ck_assert_int_eq(0, get_sign(*decimal));
    ck_assert_int_eq(0, get_exponent(*decimal));
    free(decimal);
}

START_TEST(POS_INT) {
    int test_int = 3752;
    s21_decimal *decimal = malloc(sizeof(s21_decimal));
    convertation_result status = s21_from_int_to_decimal(test_int, decimal);
    ck_assert_int_eq(status, CONVERTATION_OK);
    ck_assert_int_eq(test_int, decimal->bits[0]);
    ck_assert_int_eq(0, decimal->bits[1]);
    ck_assert_int_eq(0, decimal->bits[2]);
    ck_assert_int_eq(0, get_sign(*decimal));
    ck_assert_int_eq(0, get_exponent(*decimal));
    free(decimal);
}

Suite *suite_s21_from_int_to_decimal(void) {
    Suite *s = suite_create("suite_s21_from_int_to_decimal");
    TCase *tc = tcase_create("s21_from_int_to_decimal_tc");

    tcase_add_test(tc, NULL_POINTER);
    tcase_add_test(tc, ZERO_INT);
    tcase_add_test(tc, MAX_INT);
    tcase_add_test(tc, MIN_INT);
    tcase_add_test(tc, NEG_INT);
    tcase_add_test(tc, POS_INT);

    suite_add_tcase(s, tc);
    return s;
}
