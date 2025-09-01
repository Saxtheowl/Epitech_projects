/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
**   Data channel (PASV/LIST)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ftp.h"

static int open_pasv(client_t *c)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;
    struct sockaddr_in a;
    socklen_t sl = sizeof(a);

    if (fd < 0)
        return -1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = htonl(INADDR_ANY);
    a.sin_port = 0;
    if (bind(fd, (struct sockaddr *)&a, sizeof(a)) < 0)
        return -1;
    if (listen(fd, 1) < 0)
        return -1;
    getsockname(fd, (struct sockaddr *)&a, &sl);
    c->pasv_fd = fd;
    c->pasv_addr = a;
    return 0;
}

void cmd_pasv(client_t *c)
{
    if (c->pasv_fd > 0) {
        close(c->pasv_fd);
        c->pasv_fd = -1;
    }
    if (open_pasv(c) < 0) {
        client_write(c->fd, "425 Can't open data connection.\r\n");
        return;
    }
    unsigned int ip;
    struct sockaddr_in loc;
    socklen_t sl = sizeof(loc);
    if (getsockname(c->fd, (struct sockaddr *)&loc, &sl) == 0)
        ip = ntohl(loc.sin_addr.s_addr);
    else
        ip = 0x7F000001; /* 127.0.0.1 fallback */
    unsigned short port = ntohs(c->pasv_addr.sin_port);
    unsigned int h1 = (ip >> 24) & 0xFF;
    unsigned int h2 = (ip >> 16) & 0xFF;
    unsigned int h3 = (ip >> 8) & 0xFF;
    unsigned int h4 = ip & 0xFF;
    unsigned int p1 = (port >> 8) & 0xFF;
    unsigned int p2 = port & 0xFF;
    char buf[256];
    snprintf(buf, sizeof(buf),
        "227 Entering Passive Mode (%u,%u,%u,%u,%u,%u).\r\n",
        h1,h2,h3,h4,p1,p2);
    client_write(c->fd, buf);
}

static void send_list_over(int data_fd, const char *cwd)
{
    char cmd[1024];
    FILE *fp = NULL;
    char line[1024];

    snprintf(cmd, sizeof(cmd), "ls -l %s", cwd);
    fp = popen(cmd, "r");
    if (!fp)
        return;
    while (fgets(line, sizeof(line), fp))
        write(data_fd, line, strlen(line));
    pclose(fp);
}

void cmd_list(client_t *c, const char *home, const char *arg)
{
    char list_path[512];
    if (arg && *arg) {
        if (path_resolve(list_path, sizeof(list_path), home, c->cwd, arg) != 0) {
            client_write(c->fd, "550 Action not taken.\\r\\n");
            return;
        }
    } else {
        my_strcpy(list_path, c->cwd, sizeof(list_path));
    }
    if (c->pasv_fd <= 0 && !c->data_active) {
        client_write(c->fd, "425 Use PASV first.\r\n");
        return;
    }
    client_write(c->fd, "150 File status okay; about to open data connection.\r\n");
    int data_fd = 0;
    int open_data_after_pasv(client_t *);
    data_fd = open_data_after_pasv(c);
    if (data_fd < 0) {
        client_write(c->fd, "425 Can't open data connection.\r\n");
        if (c->pasv_fd > 0) { close(c->pasv_fd); c->pasv_fd = -1; }
        c->data_active = false;
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        send_list_over(data_fd, list_path);
        close(data_fd);
        _exit(0);
    } else if (pid > 0) {
        int st = 0;
        close(data_fd);
        waitpid(pid, &st, 0);
        client_write(c->fd, "226 Closing data connection.\r\n");
    } else {
        client_write(c->fd, "451 Requested action aborted.\r\n");
    }
    if (c->pasv_fd > 0) { close(c->pasv_fd); c->pasv_fd = -1; }
    c->data_active = false;
}

void cmd_type(client_t *c, const char *arg)
{
    if (arg && (arg[0] == 'I' || arg[0] == 'i'))
        client_write(c->fd, "200 Switching to Binary mode.\r\n");
    else if (arg && (arg[0] == 'A' || arg[0] == 'a'))
        client_write(c->fd, "200 Switching to ASCII mode.\r\n");
    else
        client_write(c->fd, "504 Command not implemented for that parameter.\r\n");
}

int open_data_after_pasv(client_t *c)
{
    int data_fd = -1;
    if (c->pasv_fd > 0) {
        data_fd = accept(c->pasv_fd, NULL, NULL);
        if (data_fd < 0)
            return -1;
        return data_fd;
    }
    if (c->data_active) {
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if (fd < 0)
            return -1;
        if (connect(fd, (struct sockaddr *)&c->active_addr,
            sizeof(c->active_addr)) < 0) {
            close(fd);
            return -1;
        }
        return fd;
    }
    return -1;
}

void cmd_retr(client_t *c, const char *home, const char *arg)
{
    char path[512];
    int fd = -1;
    int data_fd = -1;
    pid_t pid;

    if (!arg || !*arg) {
        client_write(c->fd, "501 Syntax error in parameters.\r\n");
        return;
    }
    if (c->pasv_fd <= 0) {
        client_write(c->fd, "425 Use PASV first.\r\n");
        return;
    }
    if (path_resolve(path, sizeof(path), home, c->cwd, arg) != 0) {
        client_write(c->fd, "550 Failed to open file.\r\n");
        return;
    }
    fd = open(path, O_RDONLY);
    if (fd < 0) {
        client_write(c->fd, "550 Failed to open file.\r\n");
        return;
    }
    client_write(c->fd, "150 Opening data connection.\r\n");
    data_fd = open_data_after_pasv(c);
    if (data_fd < 0) {
        client_write(c->fd, "425 Can't open data connection.\r\n");
        close(fd);
        close(c->pasv_fd);
        c->pasv_fd = -1;
        return;
    }
    pid = fork();
    if (pid == 0) {
        char buf[8192];
        ssize_t r;
        while ((r = read(fd, buf, sizeof(buf))) > 0)
            write(data_fd, buf, (size_t)r);
        close(fd);
        close(data_fd);
        _exit(0);
    } else if (pid > 0) {
        int st = 0;
        close(fd);
        close(data_fd);
        waitpid(pid, &st, 0);
        client_write(c->fd, "226 Transfer complete.\r\n");
    } else {
        client_write(c->fd, "451 Requested action aborted.\r\n");
    }
    if (c->pasv_fd > 0) { close(c->pasv_fd); c->pasv_fd = -1; }
    c->data_active = false;
}

void cmd_stor(client_t *c, const char *home, const char *arg)
{
    char path[512];
    int fd = -1;
    int data_fd = -1;
    pid_t pid;

    if (!arg || !*arg) {
        client_write(c->fd, "501 Syntax error in parameters.\r\n");
        return;
    }
    if (c->pasv_fd <= 0) {
        client_write(c->fd, "425 Use PASV first.\r\n");
        return;
    }
    if (path_resolve(path, sizeof(path), home, c->cwd, arg) != 0) {
        client_write(c->fd, "550 Failed to open file.\r\n");
        return;
    }
    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        client_write(c->fd, "550 Failed to open file.\r\n");
        return;
    }
    client_write(c->fd, "150 Opening data connection.\r\n");
    data_fd = open_data_after_pasv(c);
    if (data_fd < 0) {
        client_write(c->fd, "425 Can't open data connection.\r\n");
        close(fd);
        close(c->pasv_fd);
        c->pasv_fd = -1;
        return;
    }
    pid = fork();
    if (pid == 0) {
        char buf[8192];
        ssize_t r;
        while ((r = read(data_fd, buf, sizeof(buf))) > 0)
            write(fd, buf, (size_t)r);
        close(fd);
        close(data_fd);
        _exit(0);
    } else if (pid > 0) {
        int st = 0;
        close(fd);
        close(data_fd);
        waitpid(pid, &st, 0);
        client_write(c->fd, "226 Transfer complete.\r\n");
    } else {
        client_write(c->fd, "451 Requested action aborted.\r\n");
    }
    if (c->pasv_fd > 0) { close(c->pasv_fd); c->pasv_fd = -1; }
    c->data_active = false;
}

void cmd_help(client_t *c)
{
    client_write(c->fd,
        "214-Available commands:\r\n"
        " USER PASS QUIT PWD CWD CDUP PASV PORT LIST TYPE NOOP SYST RETR STOR DELE MKD RMD RNFR RNTO\r\n"
        "214 End of HELP.\r\n");
}

void cmd_port(client_t *c, const char *arg)
{
    unsigned int h1,h2,h3,h4,p1,p2;
    char ch;
    if (!arg || sscanf(arg, "%u,%u,%u,%u,%u,%u%c", &h1,&h2,&h3,&h4,&p1,&p2,&ch) < 6) {
        client_write(c->fd, "501 Syntax error in parameters.\r\n");
        return;
    }
    memset(&c->active_addr, 0, sizeof(c->active_addr));
    c->active_addr.sin_family = AF_INET;
    c->active_addr.sin_addr.s_addr = htonl((h1<<24)|(h2<<16)|(h3<<8)|h4);
    c->active_addr.sin_port = htons((unsigned short)((p1<<8)|p2));
    c->data_active = true;
    if (c->pasv_fd > 0) { close(c->pasv_fd); c->pasv_fd = -1; }
    client_write(c->fd, "200 PORT command successful.\r\n");
}

void cmd_dele(client_t *c, const char *home, const char *arg)
{
    char path[512];
    if (!arg || !*arg) { client_write(c->fd, "501 Syntax error.\r\n"); return; }
    if (path_resolve(path, sizeof(path), home, c->cwd, arg) != 0) {
        client_write(c->fd, "550 File not available.\r\n");
        return;
    }
    if (unlink(path) == 0)
        client_write(c->fd, "250 Requested file action okay, completed.\r\n");
    else
        client_write(c->fd, "550 File not available.\r\n");
}

void cmd_mkd(client_t *c, const char *home, const char *arg)
{
    char path[512];
    if (!arg || !*arg) { client_write(c->fd, "501 Syntax error.\r\n"); return; }
    if (path_resolve(path, sizeof(path), home, c->cwd, arg) != 0) {
        client_write(c->fd, "550 Action not taken.\r\n");
        return;
    }
    if (mkdir(path, 0755) == 0)
        client_write(c->fd, "257 Directory created.\r\n");
    else
        client_write(c->fd, "550 Action not taken.\r\n");
}

void cmd_rmd(client_t *c, const char *home, const char *arg)
{
    char path[512];
    if (!arg || !*arg) { client_write(c->fd, "501 Syntax error.\r\n"); return; }
    if (path_resolve(path, sizeof(path), home, c->cwd, arg) != 0) {
        client_write(c->fd, "550 Action not taken.\r\n");
        return;
    }
    if (rmdir(path) == 0)
        client_write(c->fd, "250 Requested file action okay, completed.\r\n");
    else
        client_write(c->fd, "550 Action not taken.\r\n");
}

void cmd_rnfr(client_t *c, const char *home, const char *arg)
{
    if (!arg || !*arg) { client_write(c->fd, "501 Syntax error.\\r\\n"); return; }
    if (path_resolve(c->rnfr_path, sizeof(c->rnfr_path), home, c->cwd, arg) != 0) {
        client_write(c->fd, "550 File not available.\r\n");
        return;
    }
    c->rnfr_pending = true;
    client_write(c->fd, "350 Requested file action pending further information.\\r\\n");
}

void cmd_rnto(client_t *c, const char *home, const char *arg)
{
    char dest[512];
    if (!arg || !*arg) { client_write(c->fd, "501 Syntax error.\\r\\n"); return; }
    if (!c->rnfr_pending || c->rnfr_path[0] == '\0') { client_write(c->fd, "503 Bad sequence of commands.\\r\\n"); return; }
    if (path_resolve(dest, sizeof(dest), home, c->cwd, arg) != 0) {
        client_write(c->fd, "550 Action not taken.\\r\\n");
        c->rnfr_path[0] = '\0';
        c->rnfr_pending = false;
        return;
    }
    if (rename(c->rnfr_path, dest) == 0)
        client_write(c->fd, "250 Requested file action okay, completed.\r\n");
    else
        client_write(c->fd, "550 Action not taken.\r\n");
    c->rnfr_path[0] = '\0';
    c->rnfr_pending = false;
}
