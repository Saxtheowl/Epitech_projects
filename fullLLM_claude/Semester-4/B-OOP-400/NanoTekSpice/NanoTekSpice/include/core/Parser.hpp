/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser for .nts configuration files
*/

#pragma once

#include "nts/IComponent.hpp"
#include "core/ComponentFactory.hpp"
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace nts {
    struct ComponentInfo {
        std::string type;
        std::string name;
        std::unique_ptr<nts::IComponent> component;
    };

    struct LinkInfo {
        std::string componentName1;
        std::size_t pin1;
        std::string componentName2;
        std::size_t pin2;
    };

    class Parser {
    private:
        ComponentFactory _factory;
        std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
        std::vector<LinkInfo> _links;

    public:
        Parser();
        ~Parser() = default;

        void parseFile(const std::string &filename);
        std::map<std::string, std::unique_ptr<nts::IComponent>>& getComponents();
        const std::vector<LinkInfo>& getLinks() const;

    private:
        void parseChipsetsSection(const std::string &line);
        void parseLinksSection(const std::string &line);
        std::string removeComments(const std::string &line);
        std::string trim(const std::string &str);
        std::vector<std::string> split(const std::string &str, char delimiter);
        void createLinks();
    };
}