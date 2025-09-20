#include "phoenix.h"

int iterative_factorial(int nb)
{
    int result = 1;

    if (nb < 0 || nb > 12) {
        return 0;
    }
    for (int i = 2; i <= nb; ++i) {
        result *= i;
    }
    return result;
}
