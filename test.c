#include <math.h>
#include <stdio.h>

int main(void) {
    for (int i = 0; expl(i) < 1e11; i++)
        printf("I: %d EXP : %Lf\n", i, expl(i));
    return 0;
}