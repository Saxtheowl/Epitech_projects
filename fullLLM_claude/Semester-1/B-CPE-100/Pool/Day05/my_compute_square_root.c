int my_compute_square_root(int nb)
{
    int i = 0;
    
    if (nb < 0) {
        return (0);
    }
    
    if (nb == 0) {
        return (0);
    }
    
    while (i * i <= nb) {
        if (i * i == nb) {
            return (i);
        }
        i++;
    }
    
    return (0);
}