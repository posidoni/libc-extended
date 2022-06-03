#include "../s21_decimal_test.h"

typedef union {
    float f;
    struct {
        unsigned int mantisa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } parts;
} float_cast;

START_TEST(float_to_dec) {
    /* s21_decimal res = {0}; */
    /* s21_from_float_to_decimal(0, &res); */
    float_cast x = {.f = 1};
    printf("mantisa = %u\n", x.parts.mantisa);
    printf("exponent = %u\n", x.parts.exponent);
    printf("sign = %u\n", x.parts.sign);
}
END_TEST

Suite *suite_s21_from_float_to_decimal(void) {
    Suite *s = suite_create("suite_s21_from_float_to_decimal");
    TCase *tc = tcase_create("s21_from_float_to_decimal_tc");

    tcase_add_test(tc, float_to_dec);

    suite_add_tcase(s, tc);
    return s;
}
