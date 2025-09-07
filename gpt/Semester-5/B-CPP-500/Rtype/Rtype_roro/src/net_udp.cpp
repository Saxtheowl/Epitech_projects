/*
** EPITECH PROJECT, 2025
** Rtype_roro
** File description:
**   Minimal UDP echo helpers
*/

#include "net.hpp"
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

static int set_nonblock(int fd)
{
    int fl;

    fl = fcntl(fd, F_GETFL, 0);
    if (fl < 0)
        return 84;
    if (fcntl(fd, F_SETFL, fl | O_NONBLOCK) < 0)
        return 84;
    return 0;
}

static int make_sock(void)
{
    int fd;

    fd = ::socket(AF_INET, SOCK_DGRAM, 0);
    return fd;
}

static bool addr_eq(const sockaddr_in &a, const sockaddr_in &b)
{
    return a.sin_family == b.sin_family &&
        a.sin_port == b.sin_port &&
        a.sin_addr.s_addr == b.sin_addr.s_addr;
}

struct Peer { sockaddr_in addr; int id; float x; float y; float vx; float vy; };

static int find_peer(const std::vector<Peer> &ps, const sockaddr_in &who)
{
    std::size_t i;

    for (i = 0; i < ps.size(); ++i)
        if (addr_eq(ps[i].addr, who))
            return (int)i;
    return -1;
}

static int add_peer(std::vector<Peer> &ps, const sockaddr_in &who)
{
    Peer p;

    p.addr = who;
    p.id = (int)ps.size() + 1;
    p.x = 0.f; p.y = 0.f; p.vx = 0.f; p.vy = 0.f;
    ps.push_back(p);
    return (int)ps.size() - 1;
}

static void world_tick(std::vector<Peer> &ps, float dt)
{
    std::size_t i;

    for (i = 0; i < ps.size(); ++i) {
        ps[i].x += ps[i].vx * dt;
        ps[i].y += ps[i].vy * dt;
    }
}

static int find_peer_by_id(const std::vector<Peer> &ps, int id)
{
    std::size_t i;

    for (i = 0; i < ps.size(); ++i)
        if (ps[i].id == id)
            return (int)i;
    return -1;
}

static std::string handle_text(const std::string &s)
{
    if (s.rfind("PING", 0) == 0)
        return "PONG";
    if (s.rfind("ECHO ", 0) == 0)
        return s.substr(5);
    if (s.rfind("JOIN ", 0) == 0)
        return std::string("JOINED ") + "1";
    if (s.rfind("QUIT", 0) == 0)
        return "QUIT";
    return s;
}

static void handle_msg(int fd, const std::vector<char> &in,
    const sockaddr_in &peer)
{
    std::string s(in.begin(), in.end());
    std::string out;
    socklen_t slen;

    out = handle_text(s);
    slen = sizeof peer;
    (void)sendto(fd, out.c_str(), out.size(), 0,
        (const sockaddr *)&peer, slen);
}

static int recv_once(int fd, std::vector<char> &buf, sockaddr_in &peer)
{
    socklen_t slen;
    ssize_t n;
    fd_set rfds;
    struct timeval tv;
    int ready;

    FD_ZERO(&rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    FD_SET(fd, &rfds);
    ready = select(fd + 1, &rfds, nullptr, nullptr, &tv);
    if (ready > 0 && FD_ISSET(fd, &rfds)) {
        slen = sizeof peer;
        n = recvfrom(fd, buf.data(), buf.size(), 0, (sockaddr *)&peer, &slen);
        if (n > 0)
            return (int)n;
    }
    return 0;
}

static int bind_addr(int fd, const std::string &host, int port)
{
    sockaddr_in addr;

    std::memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)port);
    addr.sin_addr.s_addr = host.empty() ? INADDR_ANY : inet_addr(host.c_str());
    if (bind(fd, (sockaddr *)&addr, sizeof addr) < 0)
        return 84;
    return 0;
}

static std::string trim(const std::string &s)
{
    std::size_t i = 0, j = s.size();
    while (i < j && std::isspace((unsigned char)s[i])) i++;
    while (j > i && std::isspace((unsigned char)s[j-1])) j--;
    return s.substr(i, j - i);
}

static bool parse_move(const std::string &s, float &dx, float &dy)
{
    char *e1; char *e2; std::string a; std::string b;
    std::size_t sp = s.find(' ');
    if (sp == std::string::npos) return false;
    a = s.substr(0, sp); b = trim(s.substr(sp + 1));
    dx = std::strtof(a.c_str(), &e1); dy = std::strtof(b.c_str(), &e2);
    return (*e1 == '\0' && *e2 == '\0');
}

static std::string handle_command(std::vector<Peer> &peers,
    const sockaddr_in &who, const std::string &s)
{
    int idx; float dx; float dy; Peer *p;
    std::string t = trim(s);

    if (t.rfind("JOIN ", 0) == 0) {
        idx = find_peer(peers, who);
        if (idx < 0) idx = add_peer(peers, who);
        return std::string("JOINED ") + std::to_string(peers[idx].id);
    }
    if (t.rfind("MOVE ", 0) == 0) {
        int id; char *e; std::string rest;
        t = trim(t.substr(5));
        std::size_t sp = t.find(' ');
        if (sp == std::string::npos) return "ERR";
        id = (int)std::strtol(t.substr(0, sp).c_str(), &e, 10);
        if (*e != '\0') return "ERR";
        rest = trim(t.substr(sp + 1));
        if (!parse_move(rest, dx, dy)) return "ERR";
        idx = find_peer_by_id(peers, id);
        if (idx < 0) return "ERR";
        p = &peers[idx]; p->vx = dx; p->vy = dy; return "OK";
    }
    if (t.rfind("STATE ", 0) == 0 && t.back() == '?') {
        int id; char *e;
        std::string idstr = trim(t.substr(6));
        idstr.pop_back();
        id = (int)std::strtol(idstr.c_str(), &e, 10);
        if (*e != '\0') return "ERR";
        idx = find_peer_by_id(peers, id);
        if (idx < 0) return "ERR";
        p = &peers[idx];
        return std::string("STATE ") + std::to_string((int)p->x) + " " +
            std::to_string((int)p->y);
    }
    return handle_text(t);
}

int udp_server_run(const std::string &host, int port)
{
    int fd;
    std::vector<char> buf(1024);
    sockaddr_in peer;
    int n;
    int tick;
    std::vector<Peer> peers;

    fd = make_sock();
    if (fd < 0)
        return 84;
    (void)set_nonblock(fd);
    if (bind_addr(fd, host, port) != 0)
        { ::close(fd); return 84; }
    tick = 0;
    while (1) {
        n = recv_once(fd, buf, peer);
        if (n > 0) {
            std::vector<char> data(buf.begin(), buf.begin() + n);
            std::string s(data.begin(), data.end());
            std::string out = handle_command(peers, peer, s);
            { socklen_t slen = sizeof peer;
              (void)sendto(fd, out.c_str(), out.size(), 0,
                (const sockaddr *)&peer, slen); }
            if (out == "QUIT")
                break;
            tick = 0;
        } else {
            tick += 1;
            if (tick >= 10) {
                world_tick(peers, 1.0f);
                std::string t = "TICK 1";
                for (auto &p : peers) {
                    socklen_t slen = sizeof p.addr;
                    (void)sendto(fd, t.c_str(), t.size(), 0,
                        (const sockaddr *)&p.addr, slen);
                }
                tick = 0;
            }
        }
    }
    ::close(fd);
    return 0;
}

int udp_client_run(const std::string &host, int port, const std::string &msg)
{
    int fd;
    sockaddr_in addr;
    std::vector<char> buf(1024);
    ssize_t n;

    fd = make_sock();
    if (fd < 0)
        return 84;
    std::memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)port);
    addr.sin_addr.s_addr = inet_addr(host.c_str());
    (void)sendto(fd, msg.c_str(), msg.size(), 0, (sockaddr *)&addr, sizeof addr);
    n = recvfrom(fd, buf.data(), buf.size() - 1, 0, nullptr, nullptr);
    if (n > 0) {
        buf[n] = '\0';
        std::cout << buf.data() << "\n";
    }
    ::close(fd);
    return 0;
}
