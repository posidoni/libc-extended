#include "s21_decimal_test.h"

static s21_decimal s21_copy_128_bits(__int128_t src);

START_TEST(add_test1) {
    //
    s21_decimal v1, v2, sum;

    init_zero(&v1);
    init_zero(&v2);
    for (int i = 0; i < 96; ++i) set_bit_1(&v1, i);
    set_bit_0(&v1, 92);
    set_bit_0(&v1, 93);
    set_bit_0(&v1, 94);
    set_bit_0(&v1, 95);
    // for (int i = 0; i < 33; ++i)
    // if (rand() % 2) set_bit_1(&v2, i);

    // s21_from_int_to_decimal(1, &v1);
    s21_from_int_to_decimal(1, &v2);

    set_exponent(&v1, 0);
    set_exponent(&v2, 1);
    int code = s21_add(v1, v2, &sum);

    printf("\nNUMBERS:\n");
    printf("EXP = %d ", get_exponent(v1));
    print_bits_r(v1);
    printf("EXP = %d ", get_exponent(v2));
    print_bits_r(v2);
    printf("EXP = %d ", get_exponent(sum));
    print_bits_r(sum);
    printf("\n");

    printf("ERR : %d\n", code);
    ck_assert_int_eq(get_bit(sum, 1), 1);
}
END_TEST

START_TEST(gcc_128_bits) {
    int random1 = rand(), random2 = rand();

    __int128_t el1 = random1;
    __int128_t el2 = random2;
    __int128_t expected = el1 + el2;

    s21_decimal dec1, dec2, got;

    int test = 0;

    dec1 = s21_copy_128_bits(el1);
    s21_from_decimal_to_int(dec1, &test);

    ck_assert_int_eq(el1, test);
}

static s21_decimal s21_copy_128_bits(__int128_t src) {
    s21_decimal res;

    for (int i = 0, j = 0; i < 96; i++, j++) {
        if (j % 32 == 0) {
            j = 0;
        }
        res.bits[j] = IS_SET(src, i);
    }

    return res;
}

Suite *suite_s21_add(void) {
    Suite *s = suite_create("suite_s21_add");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_test(tc, add_test1);
    tcase_add_test(tc, gcc_128_bits);

    suite_add_tcase(s, tc);
    return s;
}
