/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser for .nts configuration files implementation
*/

#include "core/Parser.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace nts {
    Parser::Parser() {}

    void Parser::parseFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            exit(84);
        }

        std::string line;
        enum class Section { NONE, CHIPSETS, LINKS };
        Section currentSection = Section::NONE;

        while (std::getline(file, line)) {
            line = removeComments(line);
            line = trim(line);

            if (line.empty()) {
                continue;
            }

            if (line == ".chipsets:") {
                currentSection = Section::CHIPSETS;
                continue;
            }
            if (line == ".links:") {
                currentSection = Section::LINKS;
                continue;
            }

            switch (currentSection) {
                case Section::CHIPSETS:
                    parseChipsetsSection(line);
                    break;
                case Section::LINKS:
                    parseLinksSection(line);
                    break;
                default:
                    break;
            }
        }

        file.close();
        createLinks();
    }

    void Parser::parseChipsetsSection(const std::string &line) {
        std::vector<std::string> tokens = split(line, ' ');
        if (tokens.size() != 2) {
            throw std::runtime_error("Invalid chipset line: " + line);
        }

        std::string type = tokens[0];
        std::string name = tokens[1];

        if (_components.find(name) != _components.end()) {
            throw std::runtime_error("Component name already exists: " + name);
        }

        auto component = _factory.createComponent(type);
        if (!component) {
            throw std::runtime_error("Unknown component type: " + type);
        }

        _components[name] = std::move(component);
    }

    void Parser::parseLinksSection(const std::string &line) {
        std::vector<std::string> tokens = split(line, ' ');
        if (tokens.size() != 2) {
            throw std::runtime_error("Invalid link line: " + line);
        }

        // Parse first component:pin
        std::vector<std::string> comp1 = split(tokens[0], ':');
        if (comp1.size() != 2) {
            throw std::runtime_error("Invalid component:pin format: " + tokens[0]);
        }

        // Parse second component:pin
        std::vector<std::string> comp2 = split(tokens[1], ':');
        if (comp2.size() != 2) {
            throw std::runtime_error("Invalid component:pin format: " + tokens[1]);
        }

        LinkInfo link;
        link.componentName1 = comp1[0];
        link.pin1 = std::stoul(comp1[1]);
        link.componentName2 = comp2[0];
        link.pin2 = std::stoul(comp2[1]);

        _links.push_back(link);
    }

    void Parser::createLinks() {
        for (const auto &link : _links) {
            auto comp1 = _components.find(link.componentName1);
            auto comp2 = _components.find(link.componentName2);

            if (comp1 == _components.end()) {
                std::cerr << "Unknown component name `" << link.componentName1 << "'." << std::endl;
                exit(84);
            }
            if (comp2 == _components.end()) {
                std::cerr << "Unknown component name `" << link.componentName2 << "'." << std::endl;
                exit(84);
            }

            comp1->second->setLink(link.pin1, *comp2->second, link.pin2);
            comp2->second->setLink(link.pin2, *comp1->second, link.pin1);
        }
    }

    std::string Parser::removeComments(const std::string &line) {
        size_t pos = line.find('#');
        if (pos != std::string::npos) {
            return line.substr(0, pos);
        }
        return line;
    }

    std::string Parser::trim(const std::string &str) {
        size_t start = str.find_first_not_of(" \t");
        if (start == std::string::npos) {
            return "";
        }
        size_t end = str.find_last_not_of(" \t");
        return str.substr(start, end - start + 1);
    }

    std::vector<std::string> Parser::split(const std::string &str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter)) {
            token = trim(token);
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }

        return tokens;
    }

    std::map<std::string, std::unique_ptr<nts::IComponent>>& Parser::getComponents() {
        return _components;
    }

    const std::vector<LinkInfo>& Parser::getLinks() const {
        return _links;
    }
}