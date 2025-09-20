#ifndef PHOENIX_H
#define PHOENIX_H

#include <stddef.h>

void my_putchar(char c);
int show_alphabet(void);
int show_combinations(void);
int show_number(int nb);
int show_string(char const *str);
char *reverse_string(char *str);
int to_number(char const *str);

int iterative_factorial(int nb);
int recursive_power(int nb, int p);
int is_prime_number(int nb);
char *my_strcpy(char *dest, char const *src);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strstr(char *str, char const *to_find);
char *my_strupcase(char *str);
char *my_strcapitalize(char *str);

char *concat_strings(char *dest, char const *src);

char *duplicate_string(char const *src);
char **split_string(char const *str);
int show_string_array(char *const *array);

struct info_param {
    int length;
    char *str;
    char *copy;
    char **word_array;
};

struct info_param *parameters_to_array(int ac, char **av);
int show_parameters_array(struct info_param const *par);
char *concat_parameters(int ac, char **av);

#endif /* PHOENIX_H */
