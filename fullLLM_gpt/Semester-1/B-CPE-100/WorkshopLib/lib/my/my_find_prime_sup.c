#include "my.h"

int my_find_prime_sup(int nb)
{
    if (nb <= 2)
        return 2;
    int candidate = nb;
    if (candidate % 2 == 0)
        candidate += 1;
    while (!my_is_prime(candidate))
        candidate += 2;
    return candidate;
}
