/*
** EPITECH PROJECT, 2024
** My_ls
** File description:
** File printing functionality
*/

#include "../include/my_ls.h"

static void print_permissions(mode_t mode)
{
    char perms[11] = "----------";

    if (S_ISDIR(mode))
        perms[0] = 'd';
    else if (S_ISLNK(mode))
        perms[0] = 'l';
    else if (S_ISCHR(mode))
        perms[0] = 'c';
    else if (S_ISBLK(mode))
        perms[0] = 'b';
    else if (S_ISFIFO(mode))
        perms[0] = 'p';
    else if (S_ISSOCK(mode))
        perms[0] = 's';
    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';
    my_putstr(perms);
}

static void print_size_and_time(struct stat *st)
{
    char *time_str = ctime(&st->st_mtime);
    int i = 4;

    my_putchar(' ');
    my_putnbr(st->st_size);
    my_putchar(' ');
    while (i < 16 && time_str[i]) {
        my_putchar(time_str[i]);
        i++;
    }
    my_putchar(' ');
}

void print_long_format(file_info_t *file, options_t *opts)
{
    struct passwd *pw = getpwuid(file->stat_info.st_uid);
    struct group *gr = getgrgid(file->stat_info.st_gid);

    (void)opts;
    print_permissions(file->stat_info.st_mode);
    my_putchar(' ');
    my_putnbr(file->stat_info.st_nlink);
    my_putchar(' ');
    if (pw)
        my_putstr(pw->pw_name);
    else
        my_putnbr(file->stat_info.st_uid);
    my_putchar(' ');
    if (gr)
        my_putstr(gr->gr_name);
    else
        my_putnbr(file->stat_info.st_gid);
    print_size_and_time(&file->stat_info);
    my_putstr(file->name);
    my_putchar('\n');
}

static void print_total(file_info_t *files)
{
    int total = 0;
    file_info_t *current = files;

    while (current) {
        total += current->stat_info.st_blocks;
        current = current->next;
    }
    my_putstr("total ");
    my_putnbr(total / 2);
    my_putchar('\n');
}

void print_files(file_info_t *files, options_t *opts, char *dir_path)
{
    file_info_t *current = files;

    (void)dir_path;
    if (opts->l_flag)
        print_total(files);
    while (current) {
        if (opts->l_flag)
            print_long_format(current, opts);
        else {
            my_putstr(current->name);
            my_putchar('\n');
        }
        current = current->next;
    }
}