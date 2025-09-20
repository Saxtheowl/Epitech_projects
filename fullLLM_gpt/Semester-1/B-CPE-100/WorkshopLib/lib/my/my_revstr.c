static void swap_char(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

char *my_revstr(char *str)
{
    int len = 0;

    if (str == 0)
        return str;
    while (str[len] != '\0')
        ++len;
    for (int i = 0; i < len / 2; ++i)
        swap_char(&str[i], &str[len - 1 - i]);
    return str;
}
