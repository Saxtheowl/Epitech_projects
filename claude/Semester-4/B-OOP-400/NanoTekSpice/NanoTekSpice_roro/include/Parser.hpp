/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser for .nts configuration files
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "IComponent.hpp"
#include "ComponentFactory.hpp"
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <iostream>

namespace nts {
    struct Link {
        std::string componentName;
        std::size_t pin;
    };

    class Parser {
    private:
        ComponentFactory _factory;
        std::map<std::string, std::unique_ptr<IComponent>> _components;
        std::vector<std::pair<Link, Link>> _links;

    public:
        Parser() = default;
        ~Parser() = default;

        void parseFile(const std::string &filename);
        void parseStream(std::istream &stream);
        
        const std::map<std::string, std::unique_ptr<IComponent>>& getComponents() const;
        std::map<std::string, std::unique_ptr<IComponent>>& getComponents();
        
        void buildCircuit();

    private:
        enum class Section {
            NONE,
            CHIPSETS,
            LINKS
        };

        void parseLine(const std::string &line, Section &currentSection);
        void parseChipsetLine(const std::string &line);
        void parseLinkLine(const std::string &line);
        
        std::string trim(const std::string &str);
        std::vector<std::string> split(const std::string &str, char delimiter);
        Link parseLink(const std::string &linkStr);
        
        bool isComment(const std::string &line);
        bool isEmpty(const std::string &line);
    };

    class ParseError : public std::exception {
    private:
        std::string _message;
    public:
        ParseError(const std::string &message) : _message(message) {}
        const char* what() const noexcept override { return _message.c_str(); }
    };
}

#endif /* !PARSER_HPP_ */