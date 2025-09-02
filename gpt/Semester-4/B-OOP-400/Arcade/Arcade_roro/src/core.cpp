/*
** EPITECH PROJECT, 2025
** Arcade_roro
** File description:
**   Core runtime (dlopen skeleton)
*/

#include <dlfcn.h>
#include <iostream>
#include "core.hpp"

int Core::run(const std::string &graphPath, const std::string &gamePath)
{
    void *gso = dlopen(graphPath.c_str(), RTLD_LAZY);
    if (!gso) { std::cerr << "Cannot open graph lib: " << dlerror() << "\n"; return 84; }
    void *gmo = dlopen(gamePath.c_str(), RTLD_LAZY);
    if (!gmo) { std::cerr << "Cannot open game lib: " << dlerror() << "\n"; dlclose(gso); return 84; }
    using create_graph_t = IGraph* (*)();
    using create_game_t = IGame* (*)();
    create_graph_t mkGraph = (create_graph_t)dlsym(gso, "create_graph");
    create_game_t mkGame = (create_game_t)dlsym(gmo, "create_game");
    if (!mkGraph || !mkGame) {
        std::cerr << "Missing factory symbols\n";
        dlclose(gmo); dlclose(gso); return 84;
    }
    IGraph *gfx = mkGraph();
    IGame *game = mkGame();
    if (!gfx || !game) { dlclose(gmo); dlclose(gso); return 84; }
    gfx->draw_text(std::string("Arcade core loaded: ") + gfx->name() + ", game=" + game->name());
    // Minimal loop: tick once
    game->tick();
    // No ownership model; assume libs manage or we just exit
    dlclose(gmo);
    dlclose(gso);
    return 0;
}
