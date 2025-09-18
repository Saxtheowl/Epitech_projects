/*
** EPITECH PROJECT, 2024
** Day09 - B-CPE-100
** File description:
** my.h - TASK 02 - All libmy function prototypes
*/

#ifndef MY_H_
#define MY_H_

void my_putchar(char c);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_putnbr(int nb);
int my_getnbr(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
int my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
int my_putnbr_base(int nbr, char const *base);
int my_getnbr_base(char const *str, char const *base);
void my_put_nbr(int nb);
int my_compute_power_rec(int nb, int power);
int my_compute_factorial_rec(int nb);
int my_compute_square_root(int nb);
int my_is_prime(int nb);

char *my_strdup(char const *src);
char *concat_params(int argc, char **argv);
int my_show_word_array(char * const *tab);
char **my_str_to_word_array(char const *str);
char *convert_base(char const *nbr, char const *base_from, char const *base_to);

#endif