#include "my.h"

int main(void)
{
    char str2[50] = "World";
    char str3[50] = "test";
    
    my_putstr("=== EXTENDED LIBMY TEST ===\n");
    
    // Test my_getnbr
    my_putstr("my_getnbr(\"-123\"): ");
    my_put_nbr(my_getnbr("-123"));
    my_putstr("\n");
    
    // Test my_strcat
    my_strcpy(str2, "Hello");
    my_strcat(str2, " World");
    my_putstr("After strcat: ");
    my_putstr(str2);
    my_putstr("\n");
    
    // Test my_revstr
    my_strcpy(str3, "abcdef");
    my_putstr("Before revstr: ");
    my_putstr(str3);
    my_putstr("\n");
    my_revstr(str3);
    my_putstr("After revstr: ");
    my_putstr(str3);
    my_putstr("\n");
    
    // Test my_compute_power_rec
    my_putstr("Power 2^5: ");
    my_put_nbr(my_compute_power_rec(2, 5));
    my_putstr("\n");
    
    // Test my_is_prime
    my_putstr("Is 17 prime? ");
    my_put_nbr(my_is_prime(17));
    my_putstr("\n");
    
    my_putstr("Is 18 prime? ");
    my_put_nbr(my_is_prime(18));
    my_putstr("\n");
    
    my_putstr("=== ALL TESTS COMPLETE ===\n");
    
    return 0;
}