/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** IPC implementation using named pipes
*/

#include "IPC.hpp"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

bool NamedPipe::create(const std::string& name) {
    _pipeName = "/tmp/plazza_" + name;
    
    if (mkfifo(_pipeName.c_str(), 0666) == -1) {
        if (errno != EEXIST) {
            return false;
        }
    }
    
    _fd = open(_pipeName.c_str(), O_RDWR | O_NONBLOCK);
    return _fd != -1;
}

bool NamedPipe::connect(const std::string& name) {
    _pipeName = "/tmp/plazza_" + name;
    _fd = open(_pipeName.c_str(), O_WRONLY | O_NONBLOCK);
    return _fd != -1;
}

bool NamedPipe::send(const std::string& data) {
    if (_fd == -1) return false;
    
    std::string message = data + "\n";
    ssize_t written = write(_fd, message.c_str(), message.length());
    return written == static_cast<ssize_t>(message.length());
}

bool NamedPipe::receive(std::string& data) {
    if (_fd == -1) return false;
    
    char buffer[1024];
    ssize_t bytesRead = read(_fd, buffer, sizeof(buffer) - 1);
    
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        data = std::string(buffer);
        
        // Remove trailing newline if present
        if (!data.empty() && data.back() == '\n') {
            data.pop_back();
        }
        
        return true;
    }
    
    return false;
}

void NamedPipe::close() {
    if (_fd != -1) {
        ::close(_fd);
        _fd = -1;
    }
    
    if (!_pipeName.empty()) {
        unlink(_pipeName.c_str());
        _pipeName.clear();
    }
}