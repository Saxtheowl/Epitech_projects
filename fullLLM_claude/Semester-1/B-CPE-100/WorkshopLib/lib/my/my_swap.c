#include "my.h"

void my_swap(int *a, int *b)
{
    int temp;
    
    if (a == 0 || b == 0)
        return;
    
    temp = *a;
    *a = *b;
    *b = temp;
}