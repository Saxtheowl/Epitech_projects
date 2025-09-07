int my_compute_power_it(int nb, int p)
{
    int result = 1;
    int i = 0;

    if (p < 0)
        return 0;
    
    if (p == 0)
        return 1;

    while (i < p) {
        result *= nb;
        i++;
    }
    
    return result;
}