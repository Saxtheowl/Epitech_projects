/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   IPC declarations
*/

#ifndef PLAZZA_IPC_HPP
#define PLAZZA_IPC_HPP

#include <utility>

struct Packet {
    int type; // 1 assign pizza, 2 status req, 3 status rep (c=ing_count), 4 done, 5 close, 6 stock item, 7 deny
    int a, b, c;
};

class Channel {
public:
    int fd;
    Channel();
    explicit Channel(int f);
    ~Channel();
    bool send(const Packet &p);
    bool recv(Packet &p);
};

std::pair<Channel,Channel> make_channel();

// Operator overloads to serialize/deserialize packets on the IPC
Channel &operator<<(Channel &ch, const Packet &p);
Channel &operator>>(Channel &ch, Packet &p);

#endif
