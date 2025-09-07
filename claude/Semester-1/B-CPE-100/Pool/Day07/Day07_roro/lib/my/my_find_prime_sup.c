int my_is_prime(int nb);

int my_find_prime_sup(int nb)
{
    int i = nb;

    if (nb <= 1)
        return 2;

    while (1) {
        if (my_is_prime(i))
            return i;
        i++;
    }
}

int my_is_prime(int nb)
{
    int i = 2;

    if (nb <= 1)
        return 0;
    
    if (nb == 2)
        return 1;

    while (i * i <= nb) {
        if (nb % i == 0)
            return 0;
        i++;
    }
    
    return 1;
}