/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Main entry point for Arcade platform
*/

#include "core/Core.hpp"
#include <iostream>
#include <filesystem>

void printUsage(const std::string &programName) {
    std::cerr << "USAGE: " << programName << " ./lib/[graphics_library].so" << std::endl;
    std::cerr << "\tgraphics_library: the graphics library to use initially" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Available graphics libraries should be in ./lib/ directory:" << std::endl;
    std::cerr << "\tarcade_ncurses.so" << std::endl;
    std::cerr << "\tarcade_sdl2.so" << std::endl;
    std::cerr << "\tarcade_sfml.so" << std::endl;
}

bool validateLibraryPath(const std::string &path) {
    if (!std::filesystem::exists(path)) {
        std::cerr << "Error: Library file '" << path << "' does not exist." << std::endl;
        return false;
    }

    if (!std::filesystem::is_regular_file(path)) {
        std::cerr << "Error: '" << path << "' is not a valid file." << std::endl;
        return false;
    }

    if (path.find(".so") == std::string::npos) {
        std::cerr << "Error: '" << path << "' is not a shared library (.so)." << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char **argv) {
    if (argc == 2 && (std::string(argv[1]) == "help" || std::string(argv[1]) == "--help")) {
        printUsage(argv[0]);
        return 0;
    }

    if (argc != 2) {
        std::cerr << "Error: Invalid number of arguments." << std::endl;
        printUsage(argv[0]);
        return 84;
    }

    std::string graphicsLibPath = argv[1];

    if (!validateLibraryPath(graphicsLibPath)) {
        return 84;
    }

    try {
        arcade::Core core;

        if (!core.init(graphicsLibPath)) {
            std::cerr << "Error: Failed to initialize Arcade core with library: "
                      << graphicsLibPath << std::endl;
            return 84;
        }

        core.run();
        core.shutdown();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Error: Unknown exception occurred." << std::endl;
        return 84;
    }

    return 0;
}