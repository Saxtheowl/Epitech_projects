/*
** EPITECH PROJECT, 2025
** MY_LS
** File description:
** Epitech-style source file for my_ls project
*/
#include "my_ls.h"
#include <sys/stat.h>

void build_perm_string(mode_t mode, char out[11])
{
    out[0] = S_ISDIR(mode) ? 'd' :
             S_ISLNK(mode) ? 'l' :
             S_ISCHR(mode) ? 'c' :
             S_ISBLK(mode) ? 'b' :
             S_ISSOCK(mode) ? 's' :
             S_ISFIFO(mode) ? 'p' : '-';

    out[1] = (mode & S_IRUSR) ? 'r' : '-';
    out[2] = (mode & S_IWUSR) ? 'w' : '-';
    out[3] = (mode & S_IXUSR) ? 'x' : '-';
    out[4] = (mode & S_IRGRP) ? 'r' : '-';
    out[5] = (mode & S_IWGRP) ? 'w' : '-';
    out[6] = (mode & S_IXGRP) ? 'x' : '-';
    out[7] = (mode & S_IROTH) ? 'r' : '-';
    out[8] = (mode & S_IWOTH) ? 'w' : '-';
    out[9] = (mode & S_IXOTH) ? 'x' : '-';
    out[10] = '\0';

    if (mode & S_ISUID)
        out[3] = (out[3] == 'x') ? 's' : 'S';
    if (mode & S_ISGID)
        out[6] = (out[6] == 'x') ? 's' : 'S';
    if (mode & S_ISVTX)
        out[9] = (out[9] == 'x') ? 't' : 'T';
}
