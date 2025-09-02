/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Component factory for creating components dynamically
*/

#ifndef COMPONENTFACTORY_HPP_
#define COMPONENTFACTORY_HPP_

#include "IComponent.hpp"
#include <memory>
#include <string>
#include <functional>
#include <map>

namespace nts {
    class ComponentFactory {
    private:
        std::map<std::string, std::function<std::unique_ptr<IComponent>(const std::string&)>> _creators;

    public:
        ComponentFactory();
        ~ComponentFactory() = default;

        std::unique_ptr<IComponent> createComponent(const std::string &type, const std::string &name = "");

    private:
        void registerComponents();
        
        // Factory methods
        std::unique_ptr<IComponent> createInput(const std::string &name) const;
        std::unique_ptr<IComponent> createOutput(const std::string &name) const;
        std::unique_ptr<IComponent> createTrue(const std::string &name) const;
        std::unique_ptr<IComponent> createFalse(const std::string &name) const;
        std::unique_ptr<IComponent> createClock(const std::string &name) const;
        std::unique_ptr<IComponent> createAnd(const std::string &name) const;
        std::unique_ptr<IComponent> createOr(const std::string &name) const;
        std::unique_ptr<IComponent> createXor(const std::string &name) const;
        std::unique_ptr<IComponent> createNot(const std::string &name) const;
        std::unique_ptr<IComponent> create4081(const std::string &name) const;
        std::unique_ptr<IComponent> create4071(const std::string &name) const;
    };
}

#endif /* !COMPONENTFACTORY_HPP_ */