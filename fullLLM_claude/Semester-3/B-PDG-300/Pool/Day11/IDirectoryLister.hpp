#pragma once

#include <string>
#include <exception>

class IDirectoryLister {
public:
    virtual ~IDirectoryLister() = default;
    virtual bool open(const std::string& path, bool hidden) = 0;
    virtual std::string get() = 0;

    class OpenFailureException : public std::exception {
    private:
        std::string message;
    public:
        OpenFailureException(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }
    };

    class NoMoreFileException : public std::exception {
    public:
        const char* what() const noexcept override { return "End of stream"; }
    };
};