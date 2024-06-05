#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("the progrem should get 2 arguments");
        return 1;
    }

    double lamda = atof(argv[1]); // Convert input to double
    int k = atoi(argv[2]); // Convert input to int

    if (lamda < 0 || k < 0) {
        printf("Error: lamda and k must be non-negative.\n");
        return 1;
    }

    long double poisson_prob = (powl(lamda, k) * expl(-lamda)) / tgammal(k + 1); // expf(-lambda) = e^(-lamda), tgammal(k + 1)=k!

    printf("Poisson probability: %Lf\n", poisson_prob); // Print the result as long double

    return 0;
}
