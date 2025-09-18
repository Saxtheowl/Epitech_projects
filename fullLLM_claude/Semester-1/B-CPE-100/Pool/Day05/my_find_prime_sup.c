int my_is_prime_helper(int nb)
{
    int i = 2;
    
    if (nb <= 1) {
        return (0);
    }
    
    if (nb == 2) {
        return (1);
    }
    
    if (nb % 2 == 0) {
        return (0);
    }
    
    while (i * i <= nb) {
        if (nb % i == 0) {
            return (0);
        }
        i++;
    }
    
    return (1);
}

int my_find_prime_sup(int nb)
{
    if (nb <= 2) {
        return (2);
    }
    
    while (!my_is_prime_helper(nb)) {
        nb++;
    }
    
    return (nb);
}