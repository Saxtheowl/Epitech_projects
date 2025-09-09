#include "my_ls.h"

void print_permissions(mode_t mode)
{
    my_putchar(S_ISDIR(mode) ? 'd' : S_ISLNK(mode) ? 'l' : '-');
    my_putchar((mode & S_IRUSR) ? 'r' : '-');
    my_putchar((mode & S_IWUSR) ? 'w' : '-');
    my_putchar((mode & S_IXUSR) ? 'x' : '-');
    my_putchar((mode & S_IRGRP) ? 'r' : '-');
    my_putchar((mode & S_IWGRP) ? 'w' : '-');
    my_putchar((mode & S_IXGRP) ? 'x' : '-');
    my_putchar((mode & S_IROTH) ? 'r' : '-');
    my_putchar((mode & S_IWOTH) ? 'w' : '-');
    my_putchar((mode & S_IXOTH) ? 'x' : '-');
}

void print_long_format(file_info_t *file)
{
    struct passwd *pwd;
    struct group *grp;
    char *time_str;
    
    print_permissions(file->stat.st_mode);
    my_putchar(' ');
    
    my_put_nbr(file->stat.st_nlink);
    my_putchar(' ');
    
    pwd = getpwuid(file->stat.st_uid);
    if (pwd)
        my_putstr(pwd->pw_name);
    else
        my_put_nbr(file->stat.st_uid);
    my_putchar(' ');
    
    grp = getgrgid(file->stat.st_gid);
    if (grp)
        my_putstr(grp->gr_name);
    else
        my_put_nbr(file->stat.st_gid);
    my_putchar(' ');
    
    my_put_nbr(file->stat.st_size);
    my_putchar(' ');
    
    time_str = ctime(&file->stat.st_mtime);
    if (time_str) {
        time_str[my_strlen(time_str) - 1] = '\0';
        my_putstr(time_str + 4);
        time_str[my_strlen(time_str)] = '\n';
    }
    my_putchar(' ');
    
    my_putstr(file->name);
    my_putchar('\n');
}

int compare_files(file_info_t *a, file_info_t *b, options_t options)
{
    int result = 0;
    
    if (options.sort_time) {
        if (a->stat.st_mtime < b->stat.st_mtime)
            result = 1;
        else if (a->stat.st_mtime > b->stat.st_mtime)
            result = -1;
        else
            result = my_strcmp(a->name, b->name);
    } else {
        result = my_strcmp(a->name, b->name);
    }
    
    return options.reverse ? -result : result;
}

void sort_files(file_info_t *files, int count, options_t options)
{
    int i, j;
    file_info_t temp;
    
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (compare_files(&files[j], &files[j + 1], options) > 0) {
                temp = files[j];
                files[j] = files[j + 1];
                files[j + 1] = temp;
            }
        }
    }
}

void free_file_info(file_info_t *files, int count)
{
    int i;
    
    if (!files)
        return;
    
    for (i = 0; i < count; i++) {
        if (files[i].name)
            free(files[i].name);
        if (files[i].path)
            free(files[i].path);
    }
    free(files);
}