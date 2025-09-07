static int is_alphanum(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}

char *my_strcapitalize(char *str)
{
    int i = 0;
    int first_letter = 1;

    while (str[i] != '\0') {
        if (is_alphanum(str[i])) {
            if (first_letter && str[i] >= 'a' && str[i] <= 'z') {
                str[i] = str[i] - 32;
                first_letter = 0;
            } else if (!first_letter && str[i] >= 'A' && str[i] <= 'Z') {
                str[i] = str[i] + 32;
            } else if (!first_letter) {
                /* Keep the character as is */
            } else {
                first_letter = 0;
            }
        } else {
            first_letter = 1;
        }
        i++;
    }
    return str;
}