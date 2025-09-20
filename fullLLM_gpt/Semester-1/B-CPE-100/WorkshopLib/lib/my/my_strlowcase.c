char *my_strlowcase(char *str)
{
    if (str == 0)
        return str;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = (char)(str[i] - 'A' + 'a');
    }
    return str;
}
