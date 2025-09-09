int mini_printf(const char *format, ...);

int my_strlen(char const *str)
{
    int len = 0;
    while (str[len])
        len++;
    return len;
}

void my_strcpy(char *dest, char const *src)
{
    int i = 0;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int main(void)
{
    char str[6];
    int nb = 21;
    char str2[8];
    
    my_strcpy(str, "world");
    mini_printf("Hello %s\n", str);
    
    mini_printf("If you multiple %d by %d, the result is %i.\n", nb, 2, nb * 2);
    
    my_strcpy(str2, "Epitech");
    mini_printf("The word %%%s%% has %i characters.\n", str2, my_strlen(str2));
    
    mini_printf("Character test: %c\n", 'A');
    
    return 0;
}