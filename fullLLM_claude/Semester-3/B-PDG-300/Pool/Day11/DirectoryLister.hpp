#pragma once

#include "IDirectoryLister.hpp"
#include <dirent.h>

class DirectoryLister : public IDirectoryLister {
private:
    DIR* dir;
    bool showHidden;

public:
    DirectoryLister();
    DirectoryLister(const std::string& path, bool hidden);
    ~DirectoryLister();

    DirectoryLister(const DirectoryLister&) = delete;
    DirectoryLister& operator=(const DirectoryLister&) = delete;
    DirectoryLister(DirectoryLister&&) = delete;
    DirectoryLister& operator=(DirectoryLister&&) = delete;

    bool open(const std::string& path, bool hidden) override;
    std::string get() override;
};