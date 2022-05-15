
#include <math.h>
#include <stdio.h>
#define ll long long int
#define MAX 16

ll nCr[MAX][MAX] = {0};

// This function use to calculate the
// binomial coefficient upto 15
void binomial() {
    // use simple DP to find coefficient
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i)
                nCr[i][j] = 1;
            else
                nCr[i][j] = nCr[i - 1][j] + nCr[i - 1][j - 1];
        }
    }
}

// Function to find the value of
double findTanNTheta(double tanTheta, ll n) {
    // store required answer
    double ans = 0, numerator = 0, denominator = 0;

    // use to toggle sign in sequence.
    ll toggle = 1;

    // calculate numerator
    for (int i = 1; i <= n; i += 2) {
        numerator = numerator + nCr[n][i] * pow(tanTheta, i) * toggle;
        toggle = toggle * -1;
    }

    // calculate denominator
    denominator = 1;
    toggle = -1;

    for (int i = 2; i <= n; i += 2) {
        numerator = numerator + nCr[n][i] * pow(tanTheta, i) * toggle;
        toggle = toggle * -1;
    }

    ans = numerator / denominator;

    return ans;
}

// Driver code.
int main() {
    binomial();
    double tanTheta = 0.3;

    ll n = 10;

    printf("%lf\n", findTanNTheta(tanTheta, n));
    return 0;
}