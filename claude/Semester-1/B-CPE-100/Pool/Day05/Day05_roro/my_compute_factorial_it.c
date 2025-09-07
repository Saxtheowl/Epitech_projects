int my_compute_factorial_it(int nb)
{
    int result = 1;
    int i = 1;

    if (nb < 0)
        return 0;
    
    if (nb == 0)
        return 1;

    while (i <= nb) {
        result *= i;
        i++;
    }
    
    return result;
}