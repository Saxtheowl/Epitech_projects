/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Dynamic library loader using dlopen/dlsym
*/

#pragma once

#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include <memory>
#include <string>
#include <vector>

namespace arcade {
    class LibraryLoader {
    public:
        LibraryLoader();
        ~LibraryLoader();

        std::unique_ptr<IDisplayModule> loadDisplayLibrary(const std::string &path);
        std::unique_ptr<IGameModule> loadGameLibrary(const std::string &path);

        void unloadLibrary(void *handle);

        std::vector<std::string> getAvailableGraphicsLibs(const std::string &libDir = "./lib/");
        std::vector<std::string> getAvailableGameLibs(const std::string &libDir = "./lib/");

        bool isValidLibrary(const std::string &path);

    private:
        void *loadLibrary(const std::string &path);
        void *getSymbol(void *handle, const std::string &symbol);

        std::vector<void*> _loadedLibraries;
    };

    typedef IDisplayModule* (*create_display_t)();
    typedef IGameModule* (*create_game_t)();
    typedef void (*destroy_module_t)(void*);
}