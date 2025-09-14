#include <unistd.h>

int write_all(int fd, const char *buf, int len)
{
    int off = 0;
    while (off < len) {
        int w = (int)write(fd, buf + off, (size_t)(len - off));
        if (w <= 0) return -1;
        off += w;
    }
    return 0;
}

