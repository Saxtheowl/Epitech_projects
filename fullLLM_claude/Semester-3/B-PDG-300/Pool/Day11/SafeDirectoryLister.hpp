#pragma once

#include "IDirectoryLister.hpp"
#include <dirent.h>

class SafeDirectoryLister : public IDirectoryLister {
private:
    DIR* dir;
    bool showHidden;

public:
    SafeDirectoryLister();
    SafeDirectoryLister(const std::string& path, bool hidden);
    ~SafeDirectoryLister();

    SafeDirectoryLister(const SafeDirectoryLister&) = delete;
    SafeDirectoryLister& operator=(const SafeDirectoryLister&) = delete;
    SafeDirectoryLister(SafeDirectoryLister&&) = delete;
    SafeDirectoryLister& operator=(SafeDirectoryLister&&) = delete;

    bool open(const std::string& path, bool hidden) override;
    std::string get() override;
};