/*
** Debug test program
*/

#include "include/organized.h"
#include "include/shell.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    workshop_t *workshop = workshop_create();
    
    printf("Testing shell integration...\n");
    int result = workshop_shell(workshop);
    printf("Shell result: %d\n", result);
    
    workshop_free(workshop);
    return 0;
}