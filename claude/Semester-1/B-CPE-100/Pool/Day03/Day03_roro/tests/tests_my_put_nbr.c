int my_put_nbr(int nb);

int main(void)
{
    my_put_nbr(0);
    my_put_nbr(42);
    my_put_nbr(-42);
    my_put_nbr(2147483647);
    my_put_nbr(-2147483648);
    my_put_nbr(123456789);
    my_put_nbr(-987654321);
    return 0;
}