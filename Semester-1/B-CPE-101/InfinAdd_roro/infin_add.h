#ifndef INFIN_ADD_H
#define INFIN_ADD_H

void my_putstr(char const *str);
void my_putchar(char c);
int my_strlen(char const *str);
char *my_strdup(char const *str);
char *my_strcpy(char *dest, char const *src);

int is_negative(char const *str);
char *remove_leading_zeros(char *str);
char *add_positive(char const *nb1, char const *nb2);
char *sub_positive(char const *nb1, char const *nb2);
int compare_abs(char const *nb1, char const *nb2);
char *infin_add(char const *nb1, char const *nb2);

#endif