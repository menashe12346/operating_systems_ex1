#include <stdio.h>
#include "poisson.h"

int main() {
    long double lamda[] = {2, 2, 2, 3, 100};
    int k[] = {1, 10, 2, 3, 3};

    for (int i = 0; i < 5; i++) {
        printf("P(%Lf, %d) = %Lf\n", lamda[i], k[i], poisson(lamda[i], k[i])); //%.2Lf= two digits after the decimal point
    }

    return 0;
}
