/*
** EPITECH PROJECT, 2025
** Plazza_roro
** File description:
**   IPC channel + Pizza (pack/unpack with << >>)
*/

#ifndef IPC_HPP
#define IPC_HPP

#include <string>
#include "kitchen.hpp"

class IpcChannel {
public:
    explicit IpcChannel(int fd): m_fd(fd) {}
    bool sendLine(const std::string &s);
    bool recvLine(std::string &out);
    int fd() const { return m_fd; }
private:
    int m_fd;
};

IpcChannel &operator<<(IpcChannel &ch, const Pizza &p);
IpcChannel &operator>>(IpcChannel &ch, Pizza &p);

#endif /* IPC_HPP */

