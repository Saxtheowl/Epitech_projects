char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if (dest == 0 || src == 0)
        return dest;
    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return dest;
}
