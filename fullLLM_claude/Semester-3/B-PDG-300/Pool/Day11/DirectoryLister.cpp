#include "DirectoryLister.hpp"
#include <iostream>
#include <cstring>

DirectoryLister::DirectoryLister() : dir(nullptr), showHidden(false) {}

DirectoryLister::DirectoryLister(const std::string& path, bool hidden) : dir(nullptr), showHidden(false) {
    open(path, hidden);
}

DirectoryLister::~DirectoryLister() {
    if (dir) {
        closedir(dir);
    }
}

bool DirectoryLister::open(const std::string& path, bool hidden) {
    if (dir) {
        closedir(dir);
        dir = nullptr;
    }

    dir = opendir(path.c_str());
    if (!dir) {
        perror(path.c_str());
        return false;
    }

    showHidden = hidden;
    return true;
}

std::string DirectoryLister::get() {
    if (!dir) {
        return "";
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;

        if (!showHidden && filename[0] == '.') {
            continue;
        }

        return filename;
    }

    return "";
}