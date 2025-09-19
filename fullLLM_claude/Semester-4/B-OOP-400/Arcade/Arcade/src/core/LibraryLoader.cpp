/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Dynamic library loader implementation
*/

#include "core/LibraryLoader.hpp"
#include <dlfcn.h>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace arcade {
    LibraryLoader::LibraryLoader() {}

    LibraryLoader::~LibraryLoader() {
        for (auto handle : _loadedLibraries) {
            if (handle) {
                dlclose(handle);
            }
        }
    }

    void* LibraryLoader::loadLibrary(const std::string &path) {
        void *handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Error loading library " << path << ": " << dlerror() << std::endl;
            return nullptr;
        }
        _loadedLibraries.push_back(handle);
        return handle;
    }

    void* LibraryLoader::getSymbol(void *handle, const std::string &symbol) {
        if (!handle) return nullptr;

        dlerror(); // Clear any existing error
        void *sym = dlsym(handle, symbol.c_str());
        char *error = dlerror();
        if (error) {
            std::cerr << "Error loading symbol " << symbol << ": " << error << std::endl;
            return nullptr;
        }
        return sym;
    }

    std::unique_ptr<IDisplayModule> LibraryLoader::loadDisplayLibrary(const std::string &path) {
        void *handle = loadLibrary(path);
        if (!handle) return nullptr;

        create_display_t create_display = (create_display_t) getSymbol(handle, "createDisplay");
        if (!create_display) {
            dlclose(handle);
            return nullptr;
        }

        IDisplayModule *module = create_display();
        if (!module) {
            dlclose(handle);
            return nullptr;
        }

        return std::unique_ptr<IDisplayModule>(module);
    }

    std::unique_ptr<IGameModule> LibraryLoader::loadGameLibrary(const std::string &path) {
        void *handle = loadLibrary(path);
        if (!handle) return nullptr;

        create_game_t create_game = (create_game_t) getSymbol(handle, "createGame");
        if (!create_game) {
            dlclose(handle);
            return nullptr;
        }

        IGameModule *module = create_game();
        if (!module) {
            dlclose(handle);
            return nullptr;
        }

        return std::unique_ptr<IGameModule>(module);
    }

    void LibraryLoader::unloadLibrary(void *handle) {
        if (handle) {
            auto it = std::find(_loadedLibraries.begin(), _loadedLibraries.end(), handle);
            if (it != _loadedLibraries.end()) {
                dlclose(handle);
                _loadedLibraries.erase(it);
            }
        }
    }

    std::vector<std::string> LibraryLoader::getAvailableGraphicsLibs(const std::string &libDir) {
        std::vector<std::string> libs;

        if (!std::filesystem::exists(libDir)) {
            return libs;
        }

        for (const auto &entry : std::filesystem::directory_iterator(libDir)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (filename.find("arcade_") == 0 &&
                    filename.find(".so") != std::string::npos &&
                    (filename.find("ncurses") != std::string::npos ||
                     filename.find("sdl2") != std::string::npos ||
                     filename.find("sfml") != std::string::npos ||
                     filename.find("gtk") != std::string::npos ||
                     filename.find("allegro") != std::string::npos)) {
                    libs.push_back(entry.path().string());
                }
            }
        }
        return libs;
    }

    std::vector<std::string> LibraryLoader::getAvailableGameLibs(const std::string &libDir) {
        std::vector<std::string> libs;

        if (!std::filesystem::exists(libDir)) {
            return libs;
        }

        for (const auto &entry : std::filesystem::directory_iterator(libDir)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (filename.find("arcade_") == 0 &&
                    filename.find(".so") != std::string::npos &&
                    (filename.find("nibbler") != std::string::npos ||
                     filename.find("pacman") != std::string::npos ||
                     filename.find("centipede") != std::string::npos ||
                     filename.find("qix") != std::string::npos ||
                     filename.find("solarfox") != std::string::npos)) {
                    libs.push_back(entry.path().string());
                }
            }
        }
        return libs;
    }

    bool LibraryLoader::isValidLibrary(const std::string &path) {
        void *handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!handle) {
            return false;
        }

        bool hasCreateDisplay = dlsym(handle, "createDisplay") != nullptr;
        bool hasCreateGame = dlsym(handle, "createGame") != nullptr;

        dlclose(handle);
        return hasCreateDisplay || hasCreateGame;
    }
}