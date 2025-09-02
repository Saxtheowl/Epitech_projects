/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser implementation for .nts files
*/

#include "Parser.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace nts {
    void Parser::parseFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw ParseError("Cannot open file: " + filename);
        }
        parseStream(file);
    }

    void Parser::parseStream(std::istream &stream) {
        std::string line;
        Section currentSection = Section::NONE;
        
        while (std::getline(stream, line)) {
            try {
                parseLine(line, currentSection);
            } catch (const std::exception &e) {
                throw ParseError("Parse error: " + std::string(e.what()));
            }
        }
        
        if (_components.empty()) {
            throw ParseError("No chipsets defined in circuit");
        }
        
        buildCircuit();
    }

    void Parser::parseLine(const std::string &line, Section &currentSection) {
        std::string trimmedLine = trim(line);
        
        if (isEmpty(trimmedLine) || isComment(trimmedLine)) {
            return;
        }
        
        if (trimmedLine == ".chipsets:") {
            currentSection = Section::CHIPSETS;
            return;
        }
        
        if (trimmedLine == ".links:") {
            currentSection = Section::LINKS;
            return;
        }
        
        switch (currentSection) {
            case Section::CHIPSETS:
                parseChipsetLine(trimmedLine);
                break;
            case Section::LINKS:
                parseLinkLine(trimmedLine);
                break;
            case Section::NONE:
                throw ParseError("Line outside of section: " + trimmedLine);
        }
    }

    void Parser::parseChipsetLine(const std::string &line) {
        auto tokens = split(line, ' ');
        if (tokens.size() != 2) {
            throw ParseError("Invalid chipset line format: " + line);
        }
        
        std::string type = tokens[0];
        std::string name = tokens[1];
        
        if (_components.find(name) != _components.end()) {
            throw ParseError("Component name already exists: " + name);
        }
        
        try {
            auto component = _factory.createComponent(type, name);
            _components[name] = std::move(component);
        } catch (const std::exception &e) {
            throw ParseError("Unknown component type: " + type);
        }
    }

    void Parser::parseLinkLine(const std::string &line) {
        auto tokens = split(line, ' ');
        if (tokens.size() != 2) {
            throw ParseError("Invalid link line format: " + line);
        }
        
        Link link1 = parseLink(tokens[0]);
        Link link2 = parseLink(tokens[1]);
        
        _links.push_back({link1, link2});
    }

    Link Parser::parseLink(const std::string &linkStr) {
        auto colonPos = linkStr.find(':');
        if (colonPos == std::string::npos) {
            throw ParseError("Invalid link format: " + linkStr);
        }
        
        Link link;
        link.componentName = linkStr.substr(0, colonPos);
        
        try {
            link.pin = std::stoul(linkStr.substr(colonPos + 1));
        } catch (const std::exception &) {
            throw ParseError("Invalid pin number in: " + linkStr);
        }
        
        return link;
    }

    void Parser::buildCircuit() {
        for (const auto &linkPair : _links) {
            const Link &link1 = linkPair.first;
            const Link &link2 = linkPair.second;
            
            auto comp1It = _components.find(link1.componentName);
            auto comp2It = _components.find(link2.componentName);
            
            if (comp1It == _components.end()) {
                throw ParseError("Unknown component name: " + link1.componentName);
            }
            if (comp2It == _components.end()) {
                throw ParseError("Unknown component name: " + link2.componentName);
            }
            
            try {
                comp1It->second->setLink(link1.pin, *comp2It->second, link2.pin);
                comp2It->second->setLink(link2.pin, *comp1It->second, link1.pin);
            } catch (const std::exception &e) {
                throw ParseError("Error linking components: " + std::string(e.what()));
            }
        }
    }

    std::string Parser::trim(const std::string &str) {
        auto start = str.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        
        auto end = str.find_last_not_of(" \t\r\n");
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

    bool Parser::isComment(const std::string &line) {
        return !line.empty() && line[0] == '#';
    }

    bool Parser::isEmpty(const std::string &line) {
        return line.empty();
    }

    const std::map<std::string, std::unique_ptr<IComponent>>& Parser::getComponents() const {
        return _components;
    }

    std::map<std::string, std::unique_ptr<IComponent>>& Parser::getComponents() {
        return _components;
    }
}