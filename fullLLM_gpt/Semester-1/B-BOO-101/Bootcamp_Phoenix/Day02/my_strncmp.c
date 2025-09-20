#include "phoenix.h"

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (n <= 0) {
        return 0;
    }
    if (!s1 || !s2) {
        if (s1 == s2) {
            return 0;
        }
        return s1 ? 1 : -1;
    }
    while (i < n) {
        unsigned char c1 = (unsigned char)s1[i];
        unsigned char c2 = (unsigned char)s2[i];

        if (c1 != c2 || c1 == '\0' || c2 == '\0') {
            return (int)(c1 - c2);
        }
        ++i;
    }
    return 0;
}
