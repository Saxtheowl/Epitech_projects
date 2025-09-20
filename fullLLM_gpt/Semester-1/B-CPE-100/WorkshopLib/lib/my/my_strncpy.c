char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (dest == 0 || src == 0 || n <= 0)
        return dest;
    for (; i < n && src[i] != '\0'; ++i)
        dest[i] = src[i];
    for (; i < n; ++i)
        dest[i] = '\0';
    return dest;
}
