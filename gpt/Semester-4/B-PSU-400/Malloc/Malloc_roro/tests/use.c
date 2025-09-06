#include <stdio.h>
#include <stdlib.h>
int main(){
    for(int i=0;i<1000;i++){ char* p=malloc(64); if(!p) return 84; p[0]='x'; free(p);} 
    puts("done");
    return 0;
}
