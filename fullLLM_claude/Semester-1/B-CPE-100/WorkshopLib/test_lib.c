#include "my.h"

int main(void)
{
    char str1[50] = "Hello";
    char str2[50] = "World";
    int a = 42;
    int b = 24;
    
    my_putstr("=== LIBMY TEST ===\n");
    
    // Test my_putstr and my_strlen
    my_putstr("String: ");
    my_putstr(str1);
    my_putstr(" (length: ");
    my_put_nbr(my_strlen(str1));
    my_putstr(")\n");
    
    // Test my_strcpy
    my_strcpy(str2, "Test");
    my_putstr("After strcpy: ");
    my_putstr(str2);
    my_putstr("\n");
    
    // Test my_strcmp
    my_putstr("Comparing strings: ");
    my_put_nbr(my_strcmp("abc", "abc"));
    my_putstr("\n");
    
    // Test my_swap
    my_putstr("Before swap: a=");
    my_put_nbr(a);
    my_putstr(", b=");
    my_put_nbr(b);
    my_putstr("\n");
    
    my_swap(&a, &b);
    
    my_putstr("After swap: a=");
    my_put_nbr(a);
    my_putstr(", b=");
    my_put_nbr(b);
    my_putstr("\n");
    
    // Test my_isneg
    my_putstr("Is -5 negative? ");
    my_isneg(-5);
    my_putstr("\n");
    
    my_putstr("Is 10 negative? ");
    my_isneg(10);
    my_putstr("\n");
    
    my_putstr("=== TEST COMPLETE ===\n");
    
    return 0;
}