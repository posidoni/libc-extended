#include "tests/s21_math_test.h"

int main(void) {
    run_tests();

    return 0;
}

void run_testcase(Suite *testcase) {
    static int counter_testcase = 1;

    if (counter_testcase > 1) putchar('\n');
    printf("%s%d%s", "CURRENT TEST: ", counter_testcase, "\n");
    counter_testcase++;

    SRunner *sr = srunner_create(testcase);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    srunner_free(sr);
}

void run_tests(void) {
    Suite *list_cases[] = {// suite_s21_abs(),  // suite_s21_acos(), suite_s21_asin(), suite_s21_atan(),
                           //                   suite_s21_ceil(),
                           //    suite_s21_cos(),  // suite_s21_exp(), suite_s21_fabs(),
                           //  suite_s21_floor(), suite_s21_fmod(), suite_s21_log(),  suite_s21_pow(),
                           // suite_s21_sin(),  //   suite_s21_sqrt(),
                           suite_s21_tan(), NULL};

    for (Suite **current_testcase = list_cases; *current_testcase != NULL; current_testcase++) {
        run_testcase(*current_testcase);
    }
}

double RandomReal(double low, double high) {
    double d;

    d = (double)rand() / ((double)RAND_MAX + 1);
    return (low + d * (high - low));
}

int RandomInteger(int low, int high) {
    int k;
    double d;

    d = (double)rand() / ((double)RAND_MAX + 1);
    k = (int)(d * (high - low + 1));
    return (low + k);
}