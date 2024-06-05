#include <math.h>
#include "poisson.h"

long double poisson(long double lamda, int k) {
    return (powl(lamda, k) * expl(-lamda)) / tgammal(k + 1);
}