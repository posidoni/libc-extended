#include "s21_math.h"

long double s21_sqrt(double n) {
    // Assuming the sqrt of n as n only
    long double x = n;
    // The closed guess will be stored in the root
    long double root;

    if (n > 0) {
        // To count the number of iterations
        int count = 0;

        while (1) {
            count++;

            // Calculate more closed x
            root = 0.5 * (x + (n / x));

            // Check for closeness
            if (fabs(root - x) < 1e-6)
                break;

            // Update root
            x = root;
        }
    }

    return (n > 0) ? root : NAN;
}
