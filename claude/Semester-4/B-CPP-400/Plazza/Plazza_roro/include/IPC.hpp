/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Inter-Process Communication wrapper
*/

#ifndef IPC_HPP_
#define IPC_HPP_

#include <string>
#include <sys/types.h>

class IPC {
public:
    IPC() = default;
    virtual ~IPC() = default;

    virtual bool create(const std::string& name) = 0;
    virtual bool connect(const std::string& name) = 0;
    virtual bool send(const std::string& data) = 0;
    virtual bool receive(std::string& data) = 0;
    virtual void close() = 0;

    IPC& operator<<(const std::string& data) {
        send(data);
        return *this;
    }

    IPC& operator>>(std::string& data) {
        receive(data);
        return *this;
    }
};

class NamedPipe : public IPC {
public:
    NamedPipe() : _fd(-1) {}
    ~NamedPipe() { close(); }

    bool create(const std::string& name) override;
    bool connect(const std::string& name) override;
    bool send(const std::string& data) override;
    bool receive(std::string& data) override;
    void close() override;

private:
    int _fd;
    std::string _pipeName;
};

#endif /* !IPC_HPP_ */