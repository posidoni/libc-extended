#include "../s21_decimal_test.h"

/* static s21_decimal s21_copy_128_bits(__int128_t src); */

START_TEST(add_test1) {
    mpz_t mpz_val1;
    mpz_init(mpz_val1);
    mpz_set_ui(mpz_val1, 0);

    mpz_t mpz_val2;
    mpz_init(mpz_val2);
    mpz_set_ui(mpz_val2, 0);

    mpz_t mpz_res;
    mpz_init(mpz_res);
    mpz_set_ui(mpz_res, 0);

    s21_decimal val1 = {0};
    get_random_pair(&val1, &mpz_val1, 2);
    s21_decimal val2 = {0};
    get_random_pair(&val2, &mpz_val2, 1);
    s21_decimal res = {0};

#define DEBUG
#ifdef DEBUG
    printf("val1 = ");
    print_bits_r(val1);
    printf("val2 = ");
    print_bits_r(val2);
    printf("mpz_val1 = ");
    print_bits_r(convert_gmp_to_decimal(mpz_val1));
    printf("mpz_val2 = ");
    print_bits_r(convert_gmp_to_decimal(mpz_val2));
#endif

    /* NOTE: GMP library works incorrectly or other functioned needed */
    mpz_add(mpz_res, mpz_val1, mpz_val2);
    s21_add(val1, val2, &res);

#ifdef DEBUG
    puts("-------------RESULT----------------");
    printf("mpz_res = ");
    print_bits_r(convert_gmp_to_decimal(mpz_res));
    printf("res = ");
    print_bits_r(res);
    puts("-------------RESULT----------------");
#endif

    ck_assert_int_eq(s21_is_equal(res, convert_gmp_to_decimal(mpz_res)), TRUE);
}
END_TEST

/* START_TEST(gcc_128_bits) { */
/*     int random1 = rand(), random2 = rand(); */

/*     __int128_t el1 = random1; */
/*     __int128_t el2 = random2; */
/*     __int128_t expected = el1 + el2; */

/*     s21_decimal dec1, dec2, got; */

/*     int test = 0; */

/*     dec1 = s21_copy_128_bits(el1); */
/*     s21_from_decimal_to_int(dec1, &test); */

/*     ck_assert_int_eq(el1, test); */
/* } */

/* static s21_decimal s21_copy_128_bits(__int128_t src) { */
/*     s21_decimal res; */

/*     for (int i = 0, j = 0; i < 96; i++, j++) { */
/*         if (j % 32 == 0) { */
/*             j = 0; */
/*         } */
/*         res.bits[j] = IS_SET(src, i); */
/*     } */

/*     return res; */
/* } */

Suite *suite_s21_add(void) {
    Suite *s = suite_create("suite_s21_add");
    TCase *tc = tcase_create("s21_add_tc");

    tcase_add_loop_test(tc, add_test1, 0, 1);
    /* tcase_add_test(tc, gcc_128_bits); */

    suite_add_tcase(s, tc);
    return s;
}
