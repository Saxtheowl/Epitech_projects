#include "my.h"

int main(void)
{
    char str[6];
    my_strcpy(str, "world");
    mini_printf("Hello %s\n", str);
    
    int nb = 21;
    mini_printf("If you multiple %d by %d, the result is %i.\n", nb, 2, nb * 2);
    
    char str2[8];
    my_strcpy(str2, "Epitech");
    mini_printf("The word %%%s%% has %i characters.\n", str2, my_strlen(str2));
    
    mini_printf("Character: %c\n", 'A');
    mini_printf("Percent: %%\n");
    
    return 0;
}