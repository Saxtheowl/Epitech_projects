#ifndef MY_H_
#define MY_H_

// Basic I/O
void my_putchar(char c);
int my_putstr(char const *str);

// Number functions
int my_isneg(int nb);
int my_put_nbr(int nb);
int my_getnbr(char const *str);

// Math functions  
void my_swap(int *a, int *b);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);

// String basic functions
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);

// String comparison
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);

// String case functions
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);

// String validation functions
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);

// Array functions
void my_sort_int_array(int *tab, int size);

// Display functions
int my_showstr(char const *str);
int my_showmem(char const *str, int size);

#endif /* !MY_H_ */