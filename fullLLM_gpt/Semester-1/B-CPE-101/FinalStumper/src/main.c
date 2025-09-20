#include <unistd.h>
#include <stdlib.h>
#include "../include/rush3.h"

#define BUFF_SIZE 4096

int main(void)
{
    char buffer[BUFF_SIZE + 1];
    int offset = 0;
    ssize_t len = 0;

    while ((len = read(0, buffer + offset, BUFF_SIZE - offset)) > 0) {
        offset += (int)len;
        if (offset >= BUFF_SIZE)
            break;
    }
    buffer[offset] = '\0';
    if (len < 0)
        return 84;
    rush3(buffer);
    return 0;
}
