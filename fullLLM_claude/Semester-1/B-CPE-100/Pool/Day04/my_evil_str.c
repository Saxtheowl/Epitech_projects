char *my_evil_str(char *str)
{
    int length = 0;
    int i = 0;
    char temp;
    
    while (str[length] != '\0') {
        length++;
    }
    
    while (i < length / 2) {
        temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
        i++;
    }
    
    return (str);
}