/*
** Test program to debug command functions
*/

#include "include/organized.h"
#include "include/shell.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    workshop_t *workshop = workshop_create();
    char *test_args[] = {"add", "WIRE", "usb", NULL};
    
    printf("Testing add function directly...\n");
    int result = add(workshop, test_args);
    printf("Add result: %d\n", result);
    
    printf("Testing disp function...\n");
    char *disp_args[] = {"disp", NULL};
    result = disp(workshop, disp_args);
    printf("Disp result: %d\n", result);
    
    workshop_free(workshop);
    return 0;
}