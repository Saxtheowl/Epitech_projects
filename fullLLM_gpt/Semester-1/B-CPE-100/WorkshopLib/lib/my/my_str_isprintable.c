int my_str_isprintable(char const *str)
{
    if (str == 0)
        return 1;
    for (int i = 0; str[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)str[i];
        if (ch < 32 || ch == 127)
            return 0;
    }
    return 1;
}
