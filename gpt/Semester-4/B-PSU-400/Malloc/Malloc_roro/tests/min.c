#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    char *p = malloc(16);
    if(!p){puts("malloc failed");return 1;}
    strcpy(p, "ok");
    puts(p);
    free(p);
    return 0;
}
