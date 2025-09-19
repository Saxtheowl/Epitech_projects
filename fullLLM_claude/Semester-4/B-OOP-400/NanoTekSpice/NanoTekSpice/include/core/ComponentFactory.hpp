/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Factory for creating components
*/

#pragma once

#include "nts/IComponent.hpp"
#include <string>
#include <memory>
#include <map>
#include <functional>

namespace nts {
    class ComponentFactory {
    private:
        std::map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> _creators;

    public:
        ComponentFactory();
        ~ComponentFactory() = default;

        std::unique_ptr<nts::IComponent> createComponent(const std::string &type);

    private:
        std::unique_ptr<nts::IComponent> createInput() const;
        std::unique_ptr<nts::IComponent> createOutput() const;
        std::unique_ptr<nts::IComponent> createTrue() const;
        std::unique_ptr<nts::IComponent> createFalse() const;
        std::unique_ptr<nts::IComponent> createClock() const;
        std::unique_ptr<nts::IComponent> createAnd() const;
        std::unique_ptr<nts::IComponent> createOr() const;
        std::unique_ptr<nts::IComponent> createXor() const;
        std::unique_ptr<nts::IComponent> createNot() const;
        std::unique_ptr<nts::IComponent> create4001() const;
        std::unique_ptr<nts::IComponent> create4011() const;
        std::unique_ptr<nts::IComponent> create4030() const;
        std::unique_ptr<nts::IComponent> create4069() const;
        std::unique_ptr<nts::IComponent> create4071() const;
        std::unique_ptr<nts::IComponent> create4081() const;
    };
}