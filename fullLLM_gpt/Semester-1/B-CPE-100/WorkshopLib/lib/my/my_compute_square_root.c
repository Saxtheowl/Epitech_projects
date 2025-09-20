int my_compute_square_root(int nb)
{
    if (nb <= 0)
        return 0;
    for (int i = 1; i * i <= nb && i <= 46340; ++i) {
        if (i * i == nb)
            return i;
    }
    return 0;
}
