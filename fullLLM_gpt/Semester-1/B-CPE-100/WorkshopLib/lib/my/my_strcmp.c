int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    if (s1 == s2)
        return 0;
    if (s1 == 0)
        return -1;
    if (s2 == 0)
        return 1;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        ++i;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}
