/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Dynamic library loader implementation
*/

#include "DLLoader.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

namespace arcade {
    // Specialization for IDisplayModule
    template<>
    std::string DLLoader<IDisplayModule>::getCreateSymbolName() const {
        return "createDisplayModule";
    }

    template<>
    std::string DLLoader<IDisplayModule>::getDestroySymbolName() const {
        return "destroyDisplayModule";
    }

    // Specialization for IGameModule
    template<>
    std::string DLLoader<IGameModule>::getCreateSymbolName() const {
        return "createGameModule";
    }

    template<>
    std::string DLLoader<IGameModule>::getDestroySymbolName() const {
        return "destroyGameModule";
    }

    // Explicit template instantiation
    template class DLLoader<IDisplayModule>;
    template class DLLoader<IGameModule>;
}