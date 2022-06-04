#include "../s21_decimal_test.h"

START_TEST(convert_test) {
    s21_decimal expected;
    init_zero(&expected);

    mpz_t mpz_val;
    mpz_init(mpz_val);
    mpz_set_ui(mpz_val, 0);

    expected = get_random_int_decimal();

    convert_decimal_to_gmp(&mpz_val, &expected);

#define DEBUG
#ifdef DEBUG
    static int test = 0;
    unsigned int num = 0;

    printf("MY DECIMAL: \n");
    print_bits(expected);
    printf("BINARY MPZ: \n");
    mpz_out_str(stdout, 2, mpz_val);
    printf("\t DEC MPZ: ");
    mpz_out_str(stdout, 10, mpz_val);
    s21_decimal aboba = convert_gmp_to_decimal(mpz_val);
    printf("\n");
    print_bits(aboba);
    test++;
#endif

    mpz_clear(mpz_val);
}
END_TEST

Suite *suite_convert_decimal_to_gmp(void) {
    Suite *s = suite_create(PRETTY_PRINT("convert_decimal_to_gmp"));
    TCase *tc = tcase_create("s21_convert_decimal_to_gmp");

    tcase_add_loop_test(tc, convert_test, 0, 5);

    suite_add_tcase(s, tc);
    return s;
}
