/*
** EPITECH PROJECT, 2025
** Plazza_roro
** File description:
**   IPC channel + Pizza (pack/unpack with << >>)
*/

#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <sstream>
#include "ipc.hpp"

static void write_all(int fd, const char *buf, std::size_t len)
{
    std::size_t off = 0;
    while (off < len) {
        ssize_t w = ::write(fd, buf + off, len - off);
        if (w <= 0) return;
        off += (std::size_t)w;
    }
}

bool IpcChannel::sendLine(const std::string &s)
{
    std::string line = s + "\n";
    write_all(m_fd, line.c_str(), line.size());
    return true;
}

bool IpcChannel::recvLine(std::string &out)
{
    out.clear();
    char c;
    while (1) {
        ssize_t r = ::recv(m_fd, &c, 1, MSG_DONTWAIT);
        if (r <= 0) return false;
        if (c == '\n') break;
        out.push_back(c);
    }
    return true;
}

static const char *type_name(PizzaType t)
{
    switch (t) {
        case PizzaType::Margarita: return "margarita";
        case PizzaType::Regina: return "regina";
        case PizzaType::Americana: return "americana";
        case PizzaType::Fantasia: return "fantasia";
    }
    return "unknown";
}

static const char *size_name(PizzaSize s)
{
    switch (s) {
        case PizzaSize::S: return "S";
        case PizzaSize::M: return "M";
        case PizzaSize::L: return "L";
        case PizzaSize::XL: return "XL";
        case PizzaSize::XXL: return "XXL";
    }
    return "?";
}

IpcChannel &operator<<(IpcChannel &ch, const Pizza &p)
{
    std::ostringstream os;
    os << "ORDER " << type_name(p.type) << ' ' << size_name(p.size);
    ch.sendLine(os.str());
    return ch;
}

IpcChannel &operator>>(IpcChannel &ch, Pizza &p)
{
    std::string line;
    if (!ch.recvLine(line)) return ch;
    if (line.rfind("DONE ", 0) == 0) {
        std::istringstream is(line.substr(5));
        std::string t, s; is >> t >> s;
        PizzaType pt; PizzaSize sz;
        if (parse_type(t, pt) && parse_size(s, sz)) {
            p.type = pt; p.size = sz;
        }
    }
    return ch;
}

