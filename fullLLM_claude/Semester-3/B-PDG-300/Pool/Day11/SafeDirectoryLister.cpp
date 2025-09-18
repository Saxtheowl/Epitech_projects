#include "SafeDirectoryLister.hpp"
#include <cstring>
#include <cerrno>

SafeDirectoryLister::SafeDirectoryLister() : dir(nullptr), showHidden(false) {}

SafeDirectoryLister::SafeDirectoryLister(const std::string& path, bool hidden) : dir(nullptr), showHidden(false) {
    open(path, hidden);
}

SafeDirectoryLister::~SafeDirectoryLister() {
    if (dir) {
        closedir(dir);
    }
}

bool SafeDirectoryLister::open(const std::string& path, bool hidden) {
    if (dir) {
        closedir(dir);
        dir = nullptr;
    }

    dir = opendir(path.c_str());
    if (!dir) {
        throw OpenFailureException(strerror(errno));
    }

    showHidden = hidden;
    return true;
}

std::string SafeDirectoryLister::get() {
    if (!dir) {
        throw NoMoreFileException();
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;

        if (!showHidden && filename[0] == '.') {
            continue;
        }

        return filename;
    }

    throw NoMoreFileException();
}