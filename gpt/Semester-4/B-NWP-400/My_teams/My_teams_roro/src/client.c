/*
** EPITECH PROJECT, 2025
** My_teams_roro
** File description:
**   Client entry
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "myteams.h"
#include "logging_client.h"

static void handle_server_line(const char *s)
{
    int code = 0; char a[1024], b[1024], c[1024];
    if (sscanf(s, "%d %1023s %1023[^\n]", &code, a, b) < 1) return;
    switch (code) {
    case 201: { // users: uuid name status
        int status = (sscanf(s, "201 %1023s %1023s %1023s", a, b, c)==3 && strcmp(c,"online")==0);
        client_print_users(a, b, status); break; }
    case 202: { int status = (sscanf(s, "202 %1023s %1023s %1023s", a, b, c)==3 && strcmp(c,"online")==0);
        client_print_user(a, b, status); break; }
    case 210: { // Message from_uuid body
        if (sscanf(s, "210 Message %1023s %1023[^\n]", a, b)==2) client_print_message(a, b); break; }
    case 211: { // messages list
        if (sscanf(s, "211 %1023s %1023[^\n]", a, b)==2) client_print_message(a, b); break; }
    case 301: { // teams list
        if (sscanf(s, "301 %1023s %1023s %1023[^\n]", a, b, c)==3) client_print_teams(a, b, c); break; }
    case 302: { if (sscanf(s, "302 %1023s %1023s %1023[^\n]", a, b, c)==3) client_print_channels(a, b, c); break; }
    case 303: { if (sscanf(s, "303 %1023s %1023s %1023[^\n]", a, b, c)==3) client_print_threads(a, b, c); break; }
    case 304: { if (sscanf(s, "304 %1023s %1023s %1023[^\n]", a, b, c)==3) client_print_reply(a, b, c); break; }
    case 220: { if (sscanf(s, "220 %1023s %1023s", a, b)==2) client_print_user(a, b, 1); break; }
    case 221: { if (sscanf(s, "221 %1023s %1023s %1023[^\n]", a, b, c)==3) client_print_team(a,b,c); break; }
    case 222: { if (sscanf(s, "222 %1023s %1023s %1023[^\n]", a, b, c)==3) client_print_channel(a,b,c); break; }
    case 223: { if (sscanf(s, "223 %1023s %1023s %1023[^\n]", a, b, c)==3) client_print_thread(a,b,c); break; }
    case 231: { if (sscanf(s, "231 %1023s %1023s", a, b)==2) client_print_subscribed_team(a, b); break; }
    case 232: { if (sscanf(s, "232 %1023s %1023s", a, b)==2) client_print_subscribed_user(a, b); break; }
    default:
        if (strncmp(s, "EV_TEAM ", 8)==0) {
            // EV_TEAM team_uuid name desc
            if (sscanf(s+8, "%1023s %1023s %1023[^\n]", a, b, c)==3) client_print_teams(a,b,c);
        } else if (strncmp(s, "EV_CHANNEL ", 11)==0) {
            // EV_CHANNEL team_uuid chan_uuid name desc
            char d[1024]; if (sscanf(s+11, "%1023s %1023s %1023s %1023[^\n]", a, b, c, d)==4) client_print_channels(b,c,d);
        } else if (strncmp(s, "EV_THREAD ", 10)==0) {
            // EV_THREAD chan_uuid thread_uuid user_uuid title body
            char d[1024], e[1024]; if (sscanf(s+10, "%1023s %1023s %1023s %1023s %1023[^\n]", a, b, c, d, e)>=5) client_print_threads(b,d,e);
        } else if (strncmp(s, "EV_REPLY ", 9)==0) {
            // EV_REPLY thread_uuid user_uuid body
            if (sscanf(s+9, "%1023s %1023s %1023[^\n]", a, b, c)==3) client_print_reply(a,b,c);
        } else {
            fprintf(stdout, "%s\n", s);
        }
        break;
    }
}

static int run_client_loop(int fd)
{
    char line[1024]; char buf[2048];
    ssize_t r = read(fd, buf, sizeof(buf)-1);
    if (r > 0) { buf[r] = '\0'; /* greeting ignored */ }
    while (fgets(line, sizeof(line), stdin)) {
        size_t n = my_strlen(line);
        if (n == 0) continue;
        if (line[n-1] != '\n') { line[n++]='\n'; line[n]='\0'; }
        if (write(fd, line, n) < 0) break;
        r = read(fd, buf, sizeof(buf)-1);
        if (r <= 0) break;
        buf[r] = '\0';
        // handle potential multi-line listings (ending with 214 End)
        char *p = buf; char *nl;
        while ((nl = strchr(p, '\n')) != NULL) {
            *nl = '\0';
            if (strcmp(p, "214 End\r") != 0 && strcmp(p, "214 End") != 0)
                handle_server_line(p);
            p = nl + 1;
        }
    }
    return 0;
}

int main(int ac, char **av)
{
    int port = 0; struct sockaddr_in a; int fd;
    if (ac == 2 && strcmp(av[1], "--help") == 0) {
        printf("USAGE: ./myteams_cli ip port\n\n");
        printf("ip is the server ip address on which the server socket listens\n");
        printf("port is the port number on which the server socket listens\n");
        return 0;
    }
    if (ac != 3 || parse_int(av[2], &port) != 0)
        return 84;
    fd = socket(AF_INET, SOCK_STREAM, 0); if (fd < 0) return 84;
    memset(&a, 0, sizeof(a)); a.sin_family = AF_INET; a.sin_port = htons((uint16_t)port);
    if (inet_pton(AF_INET, av[1], &a.sin_addr) != 1) return 84;
    if (connect(fd, (struct sockaddr *)&a, sizeof(a)) < 0) return 84;
    run_client_loop(fd);
    close(fd);
    return 0;
}
