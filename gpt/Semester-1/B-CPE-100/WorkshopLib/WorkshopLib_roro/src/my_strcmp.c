/*
** EPITECH PROJECT, 2025
** WorkshopLib_roro
** File description:
** my_strcmp
*/

int my_strcmp(const char *a, const char *b)
{
    const unsigned char *pa;
    const unsigned char *pb;

    pa = (const unsigned char *)a;
    pb = (const unsigned char *)b;
    while (*pa && *pa == *pb) {
        pa += 1;
        pb += 1;
    }
    return (int)(*pa - *pb);
}
