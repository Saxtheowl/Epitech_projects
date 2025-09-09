int my_strlen(char const *str)
{
    int len = 0;
    
    if (str == 0)
        return 0;
    
    while (str[len])
        len++;
    
    return len;
}