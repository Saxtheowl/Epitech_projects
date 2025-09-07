char *my_evil_str(char *str)
{
    int length = 0;
    int i = 0;
    char temp;

    while (str[length] != '\0') {
        length++;
    }

    length--;
    while (i < length) {
        temp = str[i];
        str[i] = str[length];
        str[length] = temp;
        i++;
        length--;
    }
    return str;
}