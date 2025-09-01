/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   IPC channel (socketpair)
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>
#include <fcntl.h>
#include "ipc.hpp"

Channel::Channel(): fd(-1) {}
Channel::Channel(int f): fd(f) {}
Channel::~Channel() { if (fd >= 0) ::close(fd); }
bool Channel::send(const Packet &p) { return ::write(fd, &p, sizeof(p)) == (ssize_t)sizeof(p); }
bool Channel::recv(Packet &p) { ssize_t r = ::read(fd, &p, sizeof(p)); return r == (ssize_t)sizeof(p); }

std::pair<Channel,Channel> make_channel()
{
    int sv[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0)
        throw std::runtime_error("socketpair failed");
    int f0 = fcntl(sv[0], F_GETFL, 0); if (f0 >= 0) fcntl(sv[0], F_SETFL, f0 | O_NONBLOCK);
    int f1 = fcntl(sv[1], F_GETFL, 0); if (f1 >= 0) fcntl(sv[1], F_SETFL, f1 | O_NONBLOCK);
    return {Channel(sv[0]), Channel(sv[1])};
}

Channel &operator<<(Channel &ch, const Packet &p)
{
    ch.send(p);
    return ch;
}

Channel &operator>>(Channel &ch, Packet &p)
{
    ch.recv(p);
    return ch;
}
