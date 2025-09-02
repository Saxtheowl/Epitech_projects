/*
** EPITECH PROJECT, 2025
** My_teams_roro
** File description:
**   Public interfaces
*/

#ifndef MYTEAMS_H
#define MYTEAMS_H

#include <stddef.h>
#include <stdbool.h>

/* server */
int run_server(int port);

/* client */
int run_client(const char *ip, int port);

/* util */
int parse_int(const char *s, int *out);
size_t my_strlen(const char *s);
void my_strcpy(char *dst, const char *src, size_t cap);

#endif /* MYTEAMS_H */

