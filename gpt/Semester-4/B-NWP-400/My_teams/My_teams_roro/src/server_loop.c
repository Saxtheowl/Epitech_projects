/*
** EPITECH PROJECT, 2025
** My_teams_roro
** File description:
**   Server loop (select)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include "myteams.h"
#include "logging_server.h"
#include <errno.h>

#define MAXC 64
#define MAX_USERS 128
#define MAX_MSGS 1024
#define MAX_TEAMS 128
#define MAX_CHANNELS 256
#define MAX_THREADS 512
#define MAX_REPLIES 1024
#define MAX_SUBS 1024

typedef struct user_s {
    char uuid[37];
    char name[32];
    bool online;
    int fd;
} user_t;

typedef struct message_s {
    char from[37];
    char to[37];
    char body[512];
} message_t;

typedef struct client_s {
    int fd;
    char name[32];
    char inbuf[1024];
    size_t inlen;
    char cur_team[37];
    char cur_channel[37];
    char cur_thread[37];
} client_t;

static void send_line(int fd, const char *s)
{
    write(fd, s, my_strlen(s));
}

/* send_user_line declared later after users[] */

static void client_init(client_t *c)
{
    c->fd = -1; c->name[0] = '\0'; c->inlen = 0;
    c->cur_team[0] = '\0'; c->cur_channel[0] = '\0'; c->cur_thread[0] = '\0';
}

static void rand_hex(char *out, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        int v = (int)(rand() % 16);
        out[i] = (char)(v < 10 ? '0' + v : 'a' + (v - 10));
    }
}

static void make_uuid(char out[37])
{
    char b[32];
    int p = 0;
    int o = 0;

    rand_hex(b, sizeof(b));
    for (int i = 0; i < 8; ++i) {
        out[o++] = b[p++];
    }
    out[o++] = '-';
    for (int i = 0; i < 4; ++i) {
        out[o++] = b[p++];
    }
    out[o++] = '-';
    for (int i = 0; i < 4; ++i) {
        out[o++] = b[p++];
    }
    out[o++] = '-';
    for (int i = 0; i < 4; ++i) {
        out[o++] = b[p++];
    }
    out[o++] = '-';
    for (int i = 0; i < 12; ++i) {
        out[o++] = b[p++];
    }
    out[o] = '\0';
}

static int parse_quoted(const char *line, char a[], size_t acap, char b[], size_t bcap)
{
    const char *p = line;
    size_t i = 0;

    while (*p && *p != '"') {
        p++;
    }
    if (*p != '"') {
        return -1;
    }
    p++;
    while (*p && *p != '"' && i + 1 < acap) {
        a[i++] = *p++;
    }
    if (*p != '"') {
        return -1;
    }
    a[i] = '\0';
    p++;
    while (*p && *p != '"') {
        p++;
    }
    if (*p != '"') {
        b[0] = '\0';
        return 0;
    }
    p++;
    i = 0;
    while (*p && *p != '"' && i + 1 < bcap) {
        b[i++] = *p++;
    }
    if (*p != '"') {
        return -1;
    }
    b[i] = '\0';
    return 0;
}

static int parse_use_args(const char *line, char t[], size_t tcap,
    char ch[], size_t ccap, char th[], size_t thcap)
{
    const char *p = line; int argc = 0; t[0]=ch[0]=th[0]='\0';
    while (*p==' ') p++;
    if (*p=='\0') return 0;
    if (parse_quoted(p, t, tcap, ch, ccap) != 0) return -1;
    argc = (ch[0]?2:1);
    // find start/end of first and second quoted blocks
    const char *q = strchr(p,'"');
    if (!q) return argc;
    q = strchr(q+1,'"'); if (!q) return argc;
    q++; const char *s2 = strchr(q,'"'); if (!s2) return argc;
    s2 = strchr(s2+1,'"'); if (!s2) return argc;
    s2++;
    if (parse_quoted(s2, th, thcap, (char[2]){0}, 2) == 0 && th[0]) argc = 3;
    return argc;
}

static user_t users[MAX_USERS];
static message_t msgs[MAX_MSGS];
static int nb_users = 0;
static int nb_msgs = 0;
static void send_user_line(const char *user_uuid, const char *msg)
{
    for (int i = 0; i < nb_users; ++i) {
        if (strcmp(users[i].uuid, user_uuid) == 0 && users[i].online && users[i].fd > 0) {
            send_line(users[i].fd, msg);
            break;
        }
    }
}

typedef struct team_s { char uuid[37]; char name[32]; char desc[128]; } team_t;
typedef struct channel_s { char uuid[37]; char team_uuid[37]; char name[32]; char desc[128]; } channel_t;
typedef struct thread_s { char uuid[37]; char channel_uuid[37]; char title[64]; char message[256]; } thread_t;
typedef struct reply_s { char uuid[37]; char thread_uuid[37]; char author_uuid[37]; char body[256]; } reply_t;
typedef struct sub_s { char team_uuid[37]; char user_uuid[37]; } sub_t;

static team_t teams[MAX_TEAMS]; static int nb_teams = 0;
static channel_t channels[MAX_CHANNELS]; static int nb_channels = 0;
static thread_t threads_[MAX_THREADS]; static int nb_threads = 0;
static reply_t replies[MAX_REPLIES]; static int nb_replies = 0;
static sub_t subs[MAX_SUBS]; static int nb_subs = 0;

static user_t *find_user_by_name(const char *name)
{
    for (int i = 0; i < nb_users; ++i) if (my_strlen(users[i].name) && strcmp(users[i].name, name) == 0) return &users[i];
    return NULL;
}

static user_t *find_user_by_uuid(const char *uuid)
{
    for (int i = 0; i < nb_users; ++i) if (strcmp(users[i].uuid, uuid) == 0) return &users[i];
    return NULL;
}

static team_t *find_team_by_uuid(const char *uuid)
{ for (int i=0;i<nb_teams;++i) if (strcmp(teams[i].uuid, uuid)==0) return &teams[i]; return NULL; }
static channel_t *find_channel_by_uuid(const char *uuid)
{ for (int i=0;i<nb_channels;++i) if (strcmp(channels[i].uuid, uuid)==0) return &channels[i]; return NULL; }
static thread_t *find_thread_by_uuid(const char *uuid)
{ for (int i=0;i<nb_threads;++i) if (strcmp(threads_[i].uuid, uuid)==0) return &threads_[i]; return NULL; }

static user_t *ensure_user(const char *name)
{
    user_t *u = find_user_by_name(name);
    if (u) return u;
    if (nb_users >= MAX_USERS) return NULL;
    u = &users[nb_users++];
    make_uuid(u->uuid);
    my_strcpy(u->name, name, sizeof(u->name));
    u->online = false; u->fd = -1;
    server_event_user_created(u->uuid, u->name);
    return u;
}

static void list_users(int fd)
{
    char line[256];
    for (int i = 0; i < nb_users; ++i) {
        snprintf(line, sizeof(line), "201 %s %s %s\r\n", users[i].uuid, users[i].name,
            users[i].online ? "online" : "offline");
        send_line(fd, line);
    }
    send_line(fd, "214 End\r\n");
}

static void user_info(int fd, const char *uuid)
{
    char line[256]; user_t *u = find_user_by_uuid(uuid);
    if (!u) { send_line(fd, "404 User\r\n"); return; }
    snprintf(line, sizeof(line), "202 %s %s %s\r\n", u->uuid, u->name, u->online?"online":"offline");
    send_line(fd, line);
}

static void push_msg(const char *from, const char *to, const char *body)
{
    if (nb_msgs >= MAX_MSGS) return;
    my_strcpy(msgs[nb_msgs].from, from, sizeof(msgs[nb_msgs].from));
    my_strcpy(msgs[nb_msgs].to, to, sizeof(msgs[nb_msgs].to));
    my_strcpy(msgs[nb_msgs].body, body, sizeof(msgs[nb_msgs].body));
    nb_msgs++;
}

static void list_msgs(int fd, const char *self_uuid, const char *peer_uuid)
{
    char line[700];
    for (int i = 0; i < nb_msgs; ++i) {
        bool ab = (strcmp(msgs[i].from, self_uuid) == 0 && strcmp(msgs[i].to, peer_uuid) == 0);
        bool ba = (strcmp(msgs[i].from, peer_uuid) == 0 && strcmp(msgs[i].to, self_uuid) == 0);
        if (ab || ba) {
            snprintf(line, sizeof(line), "211 %s %s\r\n", msgs[i].from, msgs[i].body);
            send_line(fd, line);
        }
    }
    send_line(fd, "214 End\r\n");
}

static user_t *current_user(client_t *c)
{
    if (!c->name[0]) return NULL;
    return find_user_by_name(c->name);
}

static bool must_be_logged(client_t *c)
{
    if (!current_user(c)) { send_line(c->fd, "530 Not logged\r\n"); return false; }
    return true;
}

static void list_teams(int fd)
{
    char line[256];
    for (int i=0;i<nb_teams;++i) { snprintf(line,sizeof(line),"301 %s %s %s\r\n",teams[i].uuid,teams[i].name,teams[i].desc); send_line(fd,line);} send_line(fd,"214 End\r\n");
}
static void list_channels(int fd, const char *team_uuid)
{
    char line[256];
    for (int i=0;i<nb_channels;++i) {
        if (strcmp(channels[i].team_uuid,team_uuid)==0) {
            snprintf(line,sizeof(line),"302 %s %s %s\r\n",channels[i].uuid,channels[i].name,channels[i].desc);
            send_line(fd,line);
        }
    }
    send_line(fd,"214 End\r\n");
}
static void list_threads(int fd, const char *channel_uuid)
{
    char line[512];
    for (int i=0;i<nb_threads;++i) {
        if (strcmp(threads_[i].channel_uuid,channel_uuid)==0) {
            snprintf(line,sizeof(line),"303 %s %s %s\r\n",threads_[i].uuid,threads_[i].title,threads_[i].message);
            send_line(fd,line);
        }
    }
    send_line(fd,"214 End\r\n");
}
static void list_replies(int fd, const char *thread_uuid)
{
    char line[512];
    for (int i=0;i<nb_replies;++i) {
        if (strcmp(replies[i].thread_uuid,thread_uuid)==0) {
            snprintf(line,sizeof(line),"304 %s %s %s\r\n",replies[i].uuid,replies[i].author_uuid,replies[i].body);
            send_line(fd,line);
        }
    }
    send_line(fd,"214 End\r\n");
}

static void notify_team_subscribers(const char *team_uuid, const char *line)
{
    for (int i=0;i<nb_subs;++i) {
        if (strcmp(subs[i].team_uuid, team_uuid) == 0) {
            send_user_line(subs[i].user_uuid, line);
        }
    }
}

static bool is_subscribed(const char *team_uuid, const char *user_uuid)
{ for (int i=0;i<nb_subs;++i) if (strcmp(subs[i].team_uuid,team_uuid)==0 && strcmp(subs[i].user_uuid,user_uuid)==0) return true; return false; }
static void add_sub(const char *team_uuid, const char *user_uuid)
{ if (nb_subs<MAX_SUBS && !is_subscribed(team_uuid,user_uuid)){ my_strcpy(subs[nb_subs].team_uuid,team_uuid,sizeof(subs[nb_subs].team_uuid)); my_strcpy(subs[nb_subs].user_uuid,user_uuid,sizeof(subs[nb_subs].user_uuid)); nb_subs++; } }
static void del_sub(const char *team_uuid, const char *user_uuid)
{ for (int i=0;i<nb_subs;++i) if (strcmp(subs[i].team_uuid,team_uuid)==0 && strcmp(subs[i].user_uuid,user_uuid)==0){ subs[i]=subs[nb_subs-1]; nb_subs--; return; } }

static void handle_cmd(client_t *c, const char *line)
{
    if (strncmp(line, "/help", 5) == 0) {
        send_line(c->fd,
            "214-Commands:\r\n"
            " /help\r\n"
            " /login \"name\" /logout\r\n"
            " /users /user \"uuid\"\r\n"
            " /send \"uuid\" \"message\" /messages \"uuid\"\r\n"
            " /subscribe \"team_uuid\" /unsubscribe \"team_uuid\"\r\n"
            " /subscribed ?\"team_uuid\"\r\n"
            " /use ?\"team_uuid\" ?\"channel_uuid\" ?\"thread_uuid\"\r\n"
            " /create \"name\" [\"desc\"|\"title\"|\"message\"|\"reply\"]\r\n"
            " /list /info\r\n"
            "214 End\r\n");
        return;
    }
    if (strncmp(line, "/login ", 7) == 0) {
        char name[32], dummy[2];
        if (parse_quoted(line + 7, name, sizeof(name), dummy, sizeof(dummy)) != 0) { send_line(c->fd, "501 Syntax\r\n"); return; }
        user_t *u = ensure_user(name);
        if (!u) { send_line(c->fd, "451 Temp fail\r\n"); return; }
        my_strcpy(c->name, name, sizeof(c->name));
        u->online = true; u->fd = c->fd;
        server_event_user_logged_in(u->uuid);
        send_line(c->fd, "200 Logged in\r\n");
        return;
    }
    if (strncmp(line, "/logout", 7) == 0) {
        if (c->name[0]) { user_t *u = find_user_by_name(c->name); if (u) { u->online = false; u->fd = -1; server_event_user_logged_out(u->uuid); } }
        c->name[0] = '\0';
        send_line(c->fd, "200 Logged out\r\n");
        return;
    }
    if (strncmp(line, "/users", 6) == 0) {
        if (!must_be_logged(c)) return;
        list_users(c->fd);
        return;
    }
    if (strncmp(line, "/user ", 6) == 0) {
        if (!must_be_logged(c)) return;
        char uuid[37], dummy[2];
        if (parse_quoted(line + 6, uuid, sizeof(uuid), dummy, sizeof(dummy)) != 0) {
            send_line(c->fd, "501 Syntax\r\n");
            return;
        }
        user_info(c->fd, uuid);
        return;
    }
    if (strncmp(line, "/send ", 6) == 0) {
        if (!must_be_logged(c)) return;
        char uuid[37], body[512];
        if (parse_quoted(line + 6, uuid, sizeof(uuid), body, sizeof(body)) != 0) {
            send_line(c->fd, "501 Syntax\r\n");
            return;
        }
        user_t *to = find_user_by_uuid(uuid);
        if (!to) { send_line(c->fd, "404 User\r\n"); return; }
        user_t *from = current_user(c);
        if (!from) { send_line(c->fd, "530 Not logged\r\n"); return; }
        push_msg(from->uuid, to->uuid, body);
        server_event_private_message_sended(from->uuid, to->uuid, body);
        send_line(c->fd, "203 Sent\r\n");
        if (to->online && to->fd > 0) {
            char line2[700];
            snprintf(line2, sizeof(line2), "210 Message %s %s\r\n", from->uuid, body);
            send_line(to->fd, line2);
        }
        return;
    }
    if (strncmp(line, "/messages ", 10) == 0) {
        if (!must_be_logged(c)) return;
        char uuid[37], dummy[2];
        if (parse_quoted(line + 10, uuid, sizeof(uuid), dummy, sizeof(dummy)) != 0) {
            send_line(c->fd, "501 Syntax\r\n");
            return;
        }
        user_t *peer = find_user_by_uuid(uuid);
        if (!peer) { send_line(c->fd, "404 User\r\n"); return; }
        user_t *self = current_user(c);
        if (!self) { send_line(c->fd, "530 Not logged\r\n"); return; }
        list_msgs(c->fd, self->uuid, peer->uuid);
        return;
    }
    if (strncmp(line, "/use", 4) == 0) {
        if (!must_be_logged(c)) return;
        char t[37]={0}, ch[37]={0}, th[37]={0};
        int argc = parse_use_args(line+4, t, sizeof(t), ch, sizeof(ch), th, sizeof(th));
        if (argc < 0) { send_line(c->fd, "501 Syntax\r\n"); return; }
        if (argc == 0){ c->cur_team[0]=c->cur_channel[0]=c->cur_thread[0]='\0'; send_line(c->fd,"200 Context reset\r\n"); return; }
        if (t[0] && !ch[0] && !th[0]){
            if (!find_team_by_uuid(t)){ send_line(c->fd,"404 Team\r\n"); return; }
            user_t *u = current_user(c); if (!u){ send_line(c->fd,"530 Not logged\r\n"); return; }
            if (!is_subscribed(t, u->uuid)){ send_line(c->fd, "550 Not subscribed\r\n"); return; }
            my_strcpy(c->cur_team,t,sizeof(c->cur_team)); c->cur_channel[0]=c->cur_thread[0]='\0'; send_line(c->fd,"200 Context team\r\n"); return;
        }
        if (t[0] && ch[0] && !th[0]){
            if (!find_team_by_uuid(t)){ send_line(c->fd,"404 Team\r\n"); return; }
            if (!find_channel_by_uuid(ch)){ send_line(c->fd,"404 Channel\r\n"); return; }
            user_t *u = current_user(c); if (!u){ send_line(c->fd,"530 Not logged\r\n"); return; }
            if (!is_subscribed(t, u->uuid)){ send_line(c->fd, "550 Not subscribed\r\n"); return; }
            my_strcpy(c->cur_team,t,sizeof(c->cur_team)); my_strcpy(c->cur_channel,ch,sizeof(c->cur_channel)); c->cur_thread[0]='\0'; send_line(c->fd,"200 Context channel\r\n"); return;
        }
        if (t[0] && ch[0] && th[0]){
            if (!find_team_by_uuid(t)){ send_line(c->fd,"404 Team\r\n"); return; }
            if (!find_channel_by_uuid(ch)){ send_line(c->fd,"404 Channel\r\n"); return; }
            if (!find_thread_by_uuid(th)){ send_line(c->fd,"404 Thread\r\n"); return; }
            user_t *u = current_user(c); if (!u){ send_line(c->fd,"530 Not logged\r\n"); return; }
            if (!is_subscribed(t, u->uuid)){ send_line(c->fd, "550 Not subscribed\r\n"); return; }
            my_strcpy(c->cur_team,t,sizeof(c->cur_team)); my_strcpy(c->cur_channel,ch,sizeof(c->cur_channel)); my_strcpy(c->cur_thread,th,sizeof(c->cur_thread)); send_line(c->fd,"200 Context thread\r\n"); return;
        }
        send_line(c->fd,"501 Syntax\r\n"); return; }
    if (strncmp(line, "/create", 7) == 0) {
        if (!must_be_logged(c)) return;
        char p1[128], p2[256]; if (parse_quoted(line+7,p1,sizeof(p1),p2,sizeof(p2))!=0){ send_line(c->fd,"501 Syntax\r\n"); return; }
        if (!c->cur_team[0]){
            if (nb_teams>=MAX_TEAMS){ send_line(c->fd,"451 Temp fail\r\n"); return; }
            make_uuid(teams[nb_teams].uuid);
            my_strcpy(teams[nb_teams].name,p1,sizeof(teams[nb_teams].name));
            my_strcpy(teams[nb_teams].desc,p2,sizeof(teams[nb_teams].desc));
            // auto-subscribe creator
            user_t *u = current_user(c);
            if (u) { add_sub(teams[nb_teams].uuid, u->uuid); server_event_team_created(teams[nb_teams].uuid, teams[nb_teams].name, u->uuid); }
            {
                char ev[512]; snprintf(ev, sizeof(ev), "EV_TEAM %s %s %s\r\n", teams[nb_teams].uuid, teams[nb_teams].name, teams[nb_teams].desc);
                if (u) send_user_line(u->uuid, ev);
            }
            nb_teams++;
            send_line(c->fd,"200 Team created\r\n");
            return; }
        if (c->cur_team[0] && !c->cur_channel[0]){
            user_t *u = current_user(c); if (!u){ send_line(c->fd,"530 Not logged\r\n"); return; }
            if (!is_subscribed(c->cur_team, u->uuid)){ send_line(c->fd, "550 Not subscribed\r\n"); return; }
            if (nb_channels>=MAX_CHANNELS){ send_line(c->fd,"451 Temp fail\r\n"); return; }
            make_uuid(channels[nb_channels].uuid);
            my_strcpy(channels[nb_channels].team_uuid,c->cur_team,sizeof(channels[nb_channels].team_uuid));
            my_strcpy(channels[nb_channels].name,p1,sizeof(channels[nb_channels].name));
            my_strcpy(channels[nb_channels].desc,p2,sizeof(channels[nb_channels].desc));
            server_event_channel_created(c->cur_team, channels[nb_channels].uuid, channels[nb_channels].name);
            {
                char ev[512]; snprintf(ev, sizeof(ev), "EV_CHANNEL %s %s %s %s\r\n", c->cur_team, channels[nb_channels].uuid, channels[nb_channels].name, channels[nb_channels].desc);
                notify_team_subscribers(c->cur_team, ev);
            }
            nb_channels++;
            send_line(c->fd,"200 Channel created\r\n");
            return; }
        if (c->cur_channel[0] && !c->cur_thread[0]){
            user_t *u = current_user(c); if (!u){ send_line(c->fd,"530 Not logged\r\n"); return; }
            if (!is_subscribed(c->cur_team, u->uuid)){ send_line(c->fd, "550 Not subscribed\r\n"); return; }
            if (nb_threads>=MAX_THREADS){ send_line(c->fd,"451 Temp fail\r\n"); return; }
            make_uuid(threads_[nb_threads].uuid);
            my_strcpy(threads_[nb_threads].channel_uuid,c->cur_channel,sizeof(threads_[nb_threads].channel_uuid));
            my_strcpy(threads_[nb_threads].title,p1,sizeof(threads_[nb_threads].title));
            my_strcpy(threads_[nb_threads].message,p2,sizeof(threads_[nb_threads].message));
            user_t *u2 = current_user(c);
            if (u2) server_event_thread_created(c->cur_channel, threads_[nb_threads].uuid, u2->uuid, threads_[nb_threads].title, threads_[nb_threads].message);
            {
                const char *team_uuid = NULL;
                for (int i=0;i<nb_channels;++i) if (strcmp(channels[i].uuid, c->cur_channel)==0) { team_uuid = channels[i].team_uuid; break; }
                if (team_uuid) {
                    char ev[700]; snprintf(ev, sizeof(ev), "EV_THREAD %s %s %s %s %s\r\n", c->cur_channel, threads_[nb_threads].uuid, (u2?u2->uuid:""), threads_[nb_threads].title, threads_[nb_threads].message);
                    notify_team_subscribers(team_uuid, ev);
                }
            }
            nb_threads++;
            send_line(c->fd,"200 Thread created\r\n");
            return; }
        if (c->cur_thread[0]){
            user_t *u = current_user(c); if (!u){ send_line(c->fd,"530 Not logged\r\n"); return; }
            if (!is_subscribed(c->cur_team, u->uuid)){ send_line(c->fd, "550 Not subscribed\r\n"); return; }
            if (nb_replies>=MAX_REPLIES){ send_line(c->fd,"451 Temp fail\r\n"); return; }
            make_uuid(replies[nb_replies].uuid);
            my_strcpy(replies[nb_replies].thread_uuid,c->cur_thread,sizeof(replies[nb_replies].thread_uuid));
            my_strcpy(replies[nb_replies].author_uuid,u->uuid,sizeof(replies[nb_replies].author_uuid));
            my_strcpy(replies[nb_replies].body,p1,sizeof(replies[nb_replies].body));
            server_event_reply_created(c->cur_thread, u->uuid, p1);
            {
                const char *chan_uuid = NULL; const char *team_uuid = NULL;
                for (int i=0;i<nb_threads;++i) if (strcmp(threads_[i].uuid, c->cur_thread)==0) { chan_uuid = threads_[i].channel_uuid; break; }
                if (chan_uuid) for (int i=0;i<nb_channels;++i) if (strcmp(channels[i].uuid, chan_uuid)==0) { team_uuid = channels[i].team_uuid; break; }
                if (team_uuid) { char ev[700]; snprintf(ev, sizeof(ev), "EV_REPLY %s %s %s\r\n", c->cur_thread, u->uuid, p1); notify_team_subscribers(team_uuid, ev); }
            }
            nb_replies++;
            send_line(c->fd,"200 Reply created\r\n");
            return; }
        send_line(c->fd,"501 Syntax\r\n"); return; }
    if (strncmp(line, "/list", 5) == 0) {
        if (!must_be_logged(c)) return;
        user_t *u = current_user(c); if (!u) { send_line(c->fd, "530 Not logged\r\n"); return; }
        if (!c->cur_team[0]){ list_teams(c->fd); return; }
        if (!is_subscribed(c->cur_team, u->uuid)) { send_line(c->fd, "550 Not subscribed\r\n"); return; }
        if (c->cur_team[0] && !c->cur_channel[0]){ list_channels(c->fd,c->cur_team); return; }
        if (c->cur_channel[0] && !c->cur_thread[0]){ list_threads(c->fd,c->cur_channel); return; }
        if (c->cur_thread[0]){ list_replies(c->fd,c->cur_thread); return; }
        return; }
    if (strncmp(line, "/info", 5) == 0) {
        if (!must_be_logged(c)) return;
        char buf[512]; if (!c->cur_team[0]){ user_t *u=current_user(c); if (!u){ send_line(c->fd,"530 Not logged\r\n"); return; } snprintf(buf,sizeof(buf),"220 %s %s\r\n",u->uuid,u->name); send_line(c->fd,buf); return; }
        user_t *u=current_user(c); if (!is_subscribed(c->cur_team, u->uuid)){ send_line(c->fd, "550 Not subscribed\r\n"); return; }
        if (c->cur_team[0] && !c->cur_channel[0]){ team_t *t=find_team_by_uuid(c->cur_team); if (!t){ send_line(c->fd,"404 Team\r\n"); return; } snprintf(buf,sizeof(buf),"221 %s %s %s\r\n",t->uuid,t->name,t->desc); send_line(c->fd,buf); return; }
        if (c->cur_channel[0] && !c->cur_thread[0]){ channel_t *ch=find_channel_by_uuid(c->cur_channel); if (!ch){ send_line(c->fd,"404 Channel\r\n"); return; } snprintf(buf,sizeof(buf),"222 %s %s %s\r\n",ch->uuid,ch->name,ch->desc); send_line(c->fd,buf); return; }
        if (c->cur_thread[0]){ thread_t *th=find_thread_by_uuid(c->cur_thread); if (!th){ send_line(c->fd,"404 Thread\r\n"); return; } snprintf(buf,sizeof(buf),"223 %s %s %s\r\n",th->uuid,th->title,th->message); send_line(c->fd,buf); return; }
        return; }
    if (strncmp(line, "/subscribe ", 11) == 0) { char uuid[37], d[2]; if (parse_quoted(line+11,uuid,sizeof(uuid),d,sizeof(d))!=0){ send_line(c->fd,"501 Syntax\r\n"); return;} user_t *u=find_user_by_name(c->name); if (!u){ send_line(c->fd,"530 Not logged\r\n"); return;} if (!find_team_by_uuid(uuid)){ send_line(c->fd,"404 Team\r\n"); return;} add_sub(uuid,u->uuid); server_event_team_subscribed(uuid, u->uuid); send_line(c->fd,"200 Subscribed\r\n"); return; }
    if (strncmp(line, "/unsubscribe ", 13) == 0) { char uuid[37], d[2]; if (parse_quoted(line+13,uuid,sizeof(uuid),d,sizeof(d))!=0){ send_line(c->fd,"501 Syntax\r\n"); return;} user_t *u=find_user_by_name(c->name); if (!u){ send_line(c->fd,"530 Not logged\r\n"); return;} del_sub(uuid,u->uuid); server_event_team_unsubscribed(uuid, u->uuid); if (strcmp(c->cur_team, uuid)==0){ c->cur_team[0]=c->cur_channel[0]=c->cur_thread[0]='\0'; } send_line(c->fd,"200 Unsubscribed\r\n"); return; }
    if (strncmp(line, "/subscribed", 11) == 0) {
        const char *p=line+11; while (*p==' ') p++; if (*p=='\0'){ char line2[256]; user_t *u=find_user_by_name(c->name); if (!u){ send_line(c->fd,"530 Not logged\r\n"); return;} for (int i=0;i<nb_subs;++i) if (strcmp(subs[i].user_uuid,u->uuid)==0){ team_t *t=find_team_by_uuid(subs[i].team_uuid); if (t){ snprintf(line2,sizeof(line2),"231 %s %s\r\n",t->uuid,t->name); send_line(c->fd,line2);} } send_line(c->fd,"214 End\r\n"); return; } char uuid[37], d[2]; if (parse_quoted(p,uuid,sizeof(uuid),d,sizeof(d))!=0){ send_line(c->fd,"501 Syntax\r\n"); return;} char line3[256]; for (int i=0;i<nb_subs;++i) if (strcmp(subs[i].team_uuid,uuid)==0){ user_t *u=find_user_by_uuid(subs[i].user_uuid); if (u){ snprintf(line3,sizeof(line3),"232 %s %s\r\n",u->uuid,u->name); send_line(c->fd,line3);} } send_line(c->fd,"214 End\r\n"); return; }
    send_line(c->fd, "500 Unknown\r\n");
}

static void on_line(client_t *c, const char *line)
{
    handle_cmd(c, line);
}

static volatile sig_atomic_t g_stop = 0;

static void on_sigint(int sig)
{ (void)sig; g_stop = 1; }

/* Simple escaping: replace tabs and newlines by spaces before save */
static void clean_str(char *s)
{ for (size_t i=0;s && s[i];++i) if (s[i]=='\t' || s[i]=='\n' || s[i]=='\r') s[i]=' '; }

static void save_all(void)
{
    FILE *f = NULL;
    if ((f=fopen("users.db","w"))) {
        for (int i=0;i<nb_users;++i){ clean_str(users[i].name); fprintf(f,"%s\t%s\t%d\n",users[i].uuid,users[i].name, users[i].online?1:0);} fclose(f);
    }
    if ((f=fopen("teams.db","w"))) { for (int i=0;i<nb_teams;++i){ clean_str(teams[i].name); clean_str(teams[i].desc); fprintf(f,"%s\t%s\t%s\n",teams[i].uuid,teams[i].name,teams[i].desc);} fclose(f);}    
    if ((f=fopen("channels.db","w"))) { for (int i=0;i<nb_channels;++i){ clean_str(channels[i].name); clean_str(channels[i].desc); fprintf(f,"%s\t%s\t%s\t%s\n",channels[i].uuid,channels[i].team_uuid,channels[i].name,channels[i].desc);} fclose(f);}    
    if ((f=fopen("threads.db","w"))) { for (int i=0;i<nb_threads;++i){ clean_str(threads_[i].title); clean_str(threads_[i].message); fprintf(f,"%s\t%s\t%s\t%s\n",threads_[i].uuid,threads_[i].channel_uuid,threads_[i].title,threads_[i].message);} fclose(f);}    
    if ((f=fopen("replies.db","w"))) { for (int i=0;i<nb_replies;++i){ clean_str(replies[i].body); fprintf(f,"%s\t%s\t%s\t%s\n",replies[i].uuid,replies[i].thread_uuid,replies[i].author_uuid,replies[i].body);} fclose(f);}    
    if ((f=fopen("subs.db","w"))) { for (int i=0;i<nb_subs;++i){ fprintf(f,"%s\t%s\n",subs[i].team_uuid,subs[i].user_uuid);} fclose(f);}    
    if ((f=fopen("messages.db","w"))) { for (int i=0;i<nb_msgs;++i){ clean_str(msgs[i].body); fprintf(f,"%s\t%s\t%s\n",msgs[i].from,msgs[i].to,msgs[i].body);} fclose(f);}    
}

static void load_all(void)
{
    FILE *f = NULL; char a[1024], b[1024], c[1024], d[1024]; int n;
    if ((f=fopen("users.db","r"))) { while ((n=fscanf(f,"%1023[^\t]\t%1023[^\t]\t%1023[^\n]\n",a,b,c))==3){ if (nb_users<MAX_USERS){ my_strcpy(users[nb_users].uuid,a,sizeof(users[nb_users].uuid)); my_strcpy(users[nb_users].name,b,sizeof(users[nb_users].name)); users[nb_users].online=false; users[nb_users].fd=-1; nb_users++; } } fclose(f);}    
    if ((f=fopen("teams.db","r"))) { while ((n=fscanf(f,"%1023[^\t]\t%1023[^\t]\t%1023[^\n]\n",a,b,c))==3){ if (nb_teams<MAX_TEAMS){ my_strcpy(teams[nb_teams].uuid,a,sizeof(teams[nb_teams].uuid)); my_strcpy(teams[nb_teams].name,b,sizeof(teams[nb_teams].name)); my_strcpy(teams[nb_teams].desc,c,sizeof(teams[nb_teams].desc)); nb_teams++; } } fclose(f);}    
    if ((f=fopen("channels.db","r"))) { while ((n=fscanf(f,"%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%1023[^\n]\n",a,b,c,d))==4){ if (nb_channels<MAX_CHANNELS){ my_strcpy(channels[nb_channels].uuid,a,sizeof(channels[nb_channels].uuid)); my_strcpy(channels[nb_channels].team_uuid,b,sizeof(channels[nb_channels].team_uuid)); my_strcpy(channels[nb_channels].name,c,sizeof(channels[nb_channels].name)); my_strcpy(channels[nb_channels].desc,d,sizeof(channels[nb_channels].desc)); nb_channels++; } } fclose(f);}    
    if ((f=fopen("threads.db","r"))) { while ((n=fscanf(f,"%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%1023[^\n]\n",a,b,c,d))==4){ if (nb_threads<MAX_THREADS){ my_strcpy(threads_[nb_threads].uuid,a,sizeof(threads_[nb_threads].uuid)); my_strcpy(threads_[nb_threads].channel_uuid,b,sizeof(threads_[nb_threads].channel_uuid)); my_strcpy(threads_[nb_threads].title,c,sizeof(threads_[nb_threads].title)); my_strcpy(threads_[nb_threads].message,d,sizeof(threads_[nb_threads].message)); nb_threads++; } } fclose(f);}    
    if ((f=fopen("replies.db","r"))) { while ((n=fscanf(f,"%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%1023[^\n]\n",a,b,c,d))==4){ if (nb_replies<MAX_REPLIES){ my_strcpy(replies[nb_replies].uuid,a,sizeof(replies[nb_replies].uuid)); my_strcpy(replies[nb_replies].thread_uuid,b,sizeof(replies[nb_replies].thread_uuid)); my_strcpy(replies[nb_replies].author_uuid,c,sizeof(replies[nb_replies].author_uuid)); my_strcpy(replies[nb_replies].body,d,sizeof(replies[nb_replies].body)); nb_replies++; } } fclose(f);}    
    if ((f=fopen("subs.db","r"))) { while ((n=fscanf(f,"%1023[^\t]\t%1023[^\n]\n",a,b))==2){ if (nb_subs<MAX_SUBS){ my_strcpy(subs[nb_subs].team_uuid,a,sizeof(subs[nb_subs].team_uuid)); my_strcpy(subs[nb_subs].user_uuid,b,sizeof(subs[nb_subs].user_uuid)); nb_subs++; } } fclose(f);}    
    if ((f=fopen("messages.db","r"))) { while ((n=fscanf(f,"%1023[^\t]\t%1023[^\t]\t%1023[^\n]\n",a,b,c))==3){ if (nb_msgs<MAX_MSGS){ my_strcpy(msgs[nb_msgs].from,a,sizeof(msgs[nb_msgs].from)); my_strcpy(msgs[nb_msgs].to,b,sizeof(msgs[nb_msgs].to)); my_strcpy(msgs[nb_msgs].body,c,sizeof(msgs[nb_msgs].body)); nb_msgs++; } } fclose(f);}    
}

int run_server(int port)
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1; struct sockaddr_in a;
    client_t cs[MAXC];
    if (lfd < 0) return -1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    memset(&a, 0, sizeof(a)); a.sin_family = AF_INET; a.sin_addr.s_addr = INADDR_ANY; a.sin_port = htons((uint16_t)port);
    if (bind(lfd, (struct sockaddr *)&a, sizeof(a)) < 0) return -1;
    if (listen(lfd, 16) < 0) return -1;
    signal(SIGINT, on_sigint);
    srand((unsigned int)getpid());
    load_all();
    for (int i = 0; i < MAXC; ++i) client_init(&cs[i]);
    while (!g_stop) {
        fd_set rfds; FD_ZERO(&rfds); FD_SET(lfd, &rfds); int maxfd = lfd;
        for (int i = 0; i < MAXC; ++i) if (cs[i].fd > 0) { FD_SET(cs[i].fd, &rfds); if (cs[i].fd > maxfd) maxfd = cs[i].fd; }
        struct timeval tv; tv.tv_sec = 0; tv.tv_usec = 500000;
        int sr = select(maxfd + 1, &rfds, NULL, NULL, &tv);
        if (sr < 0) {
            if (errno == EINTR) continue;
            break;
        }
        if (FD_ISSET(lfd, &rfds)) {
            int cfd = accept(lfd, NULL, NULL);
            if (cfd > 0) {
                for (int i = 0; i < MAXC; ++i) if (cs[i].fd <= 0) { client_init(&cs[i]); cs[i].fd = cfd; send_line(cfd, "220 Welcome\r\n"); break; }
            }
        }
        for (int i = 0; i < MAXC; ++i) {
            client_t *c = &cs[i]; if (c->fd <= 0) continue;
            if (!FD_ISSET(c->fd, &rfds)) continue;
            ssize_t r = read(c->fd, c->inbuf + c->inlen, sizeof(c->inbuf) - c->inlen - 1);
            if (r <= 0) { close(c->fd); client_init(c); continue; }
            c->inlen += (size_t)r; c->inbuf[c->inlen] = '\0';
            char *nl = NULL;
            while ((nl = strchr(c->inbuf, '\n')) != NULL) {
                *nl = '\0'; if (nl > c->inbuf && *(nl-1) == '\r') *(nl-1) = '\0';
                on_line(c, c->inbuf);
                size_t rem = c->inlen - ((nl - c->inbuf) + 1);
                memmove(c->inbuf, nl + 1, rem); c->inlen = rem; c->inbuf[rem] = '\0';
            }
        }
    }
    save_all();
    close(lfd);
    return 0;
}
