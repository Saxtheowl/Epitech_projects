/*
** EPITECH PROJECT, 2025
** Gomoku
** File description:
** Piskvork communication protocol handler
*/

#ifndef PROTOCOL_H_
    #define PROTOCOL_H_

    #include <iostream>
    #include <string>
    #include <sstream>
    #include "gomoku.h"

    class Protocol {
    private:
        Gomoku game_;
        bool running_;
        
        void handle_start(const std::string &params);
        void handle_turn(const std::string &params);
        void handle_begin();
        void handle_board(const std::string &params);
        void handle_info(const std::string &params);
        void handle_end();

    public:
        Protocol();
        ~Protocol();
        
        void run();
        void process_command(const std::string &command);
    };

#endif /* !PROTOCOL_H_ */