#include "my_ls.h"

char get_file_type(mode_t mode)
{
    if (S_ISDIR(mode))
        return 'd';
    if (S_ISLNK(mode))
        return 'l';
    if (S_ISBLK(mode))
        return 'b';
    if (S_ISCHR(mode))
        return 'c';
    if (S_ISFIFO(mode))
        return 'p';
    if (S_ISSOCK(mode))
        return 's';
    return '-';
}

void print_permissions(mode_t mode)
{
    my_putchar(get_file_type(mode));
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

void print_number(long n)
{
    if (n < 0) {
        my_putchar('-');
        n = -n;
    }
    if (n >= 10)
        print_number(n / 10);
    my_putchar('0' + (n % 10));
}

void print_long_format(file_info_t *file)
{
    struct passwd *pwd;
    struct group *grp;
    char *time_str;
    int i;
    
    print_permissions(file->st.st_mode);
    my_putchar(' ');
    
    print_number(file->st.st_nlink);
    my_putchar(' ');
    
    pwd = getpwuid(file->st.st_uid);
    if (pwd)
        my_putstr(pwd->pw_name);
    else
        print_number(file->st.st_uid);
    my_putchar(' ');
    
    grp = getgrgid(file->st.st_gid);
    if (grp)
        my_putstr(grp->gr_name);
    else
        print_number(file->st.st_gid);
    my_putchar(' ');
    
    print_number(file->st.st_size);
    my_putchar(' ');
    
    time_str = ctime(&file->st.st_mtime);
    if (time_str) {
        for (i = 4; i < 16; i++)
            my_putchar(time_str[i]);
    }
    my_putchar(' ');
    
    my_putstr(file->name);
    my_putchar('\n');
}

void print_simple_format(file_info_t *list, options_t *opts)
{
    file_info_t *current = list;
    
    (void)opts;
    while (current) {
        my_putstr(current->name);
        if (current->next)
            my_putchar('\n');
        current = current->next;
    }
    if (list)
        my_putchar('\n');
}