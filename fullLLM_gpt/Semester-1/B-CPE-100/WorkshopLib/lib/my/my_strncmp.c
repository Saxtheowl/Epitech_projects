int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (n <= 0)
        return 0;
    if (s1 == s2)
        return 0;
    if (s1 == 0)
        return -1;
    if (s2 == 0)
        return 1;
    while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        ++i;
    if (i == n)
        return 0;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}
