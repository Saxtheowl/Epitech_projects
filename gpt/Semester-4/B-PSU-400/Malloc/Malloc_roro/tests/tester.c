#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *p = malloc(10);
    strcpy(p, "abc");
    p = realloc(p, 100);
    strcat(p, "def");
    printf("%s\n", p);
    free(p);
    return 0;
}

