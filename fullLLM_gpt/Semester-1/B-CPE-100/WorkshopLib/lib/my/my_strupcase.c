char *my_strupcase(char *str)
{
    if (str == 0)
        return str;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = (char)(str[i] - 'a' + 'A');
    }
    return str;
}
