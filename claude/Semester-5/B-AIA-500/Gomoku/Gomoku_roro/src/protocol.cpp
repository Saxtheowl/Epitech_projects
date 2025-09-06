/*
** EPITECH PROJECT, 2025
** Gomoku
** File description:
** Piskvork communication protocol implementation
*/

#include "protocol.h"

Protocol::Protocol() : running_(false)
{
}

Protocol::~Protocol()
{
}

void Protocol::run()
{
    running_ = true;
    std::string line;
    
    while (running_ && std::getline(std::cin, line)) {
        process_command(line);
    }
}

void Protocol::process_command(const std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "START") {
        std::string params;
        std::getline(iss, params);
        handle_start(params);
    } else if (cmd == "TURN") {
        std::string params;
        std::getline(iss, params);
        handle_turn(params);
    } else if (cmd == "BEGIN") {
        handle_begin();
    } else if (cmd == "BOARD") {
        std::string params;
        std::getline(iss, params);
        handle_board(params);
    } else if (cmd == "INFO") {
        std::string params;
        std::getline(iss, params);
        handle_info(params);
    } else if (cmd == "END") {
        handle_end();
    } else if (cmd == "ABOUT") {
        std::cout << "name=\"Gomoku_roro\", version=\"1.0\", "
                  << "author=\"Claude AI\", country=\"France\"" << std::endl;
    }
}

void Protocol::handle_start(const std::string &params)
{
    std::istringstream iss(params);
    int size;
    iss >> size;
    
    if (size == BOARD_SIZE) {
        game_.start_game(size);
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "ERROR message=\"Board size not supported\"" << std::endl;
    }
}

void Protocol::handle_turn(const std::string &params)
{
    std::istringstream iss(params);
    int x, y;
    iss >> x >> y;
    
    game_.opponent_move(x, y);
    
    Position next_move = game_.get_next_move();
    game_.make_move(next_move.x, next_move.y);
    
    std::cout << next_move.x << "," << next_move.y << std::endl;
}

void Protocol::handle_begin()
{
    game_.reset_board();
    
    Position next_move = game_.get_next_move();
    game_.make_move(next_move.x, next_move.y);
    
    std::cout << next_move.x << "," << next_move.y << std::endl;
}

void Protocol::handle_board(const std::string &params)
{
    game_.reset_board();
    std::string line;
    
    while (std::getline(std::cin, line) && line != "DONE") {
        std::istringstream iss(line);
        int x, y, player;
        char comma;
        
        if (iss >> x >> comma >> y >> comma >> player) {
            if (player == 1) {
                game_.make_move(x, y);
            } else if (player == 2) {
                game_.opponent_move(x, y);
            }
        }
    }
    
    Position next_move = game_.get_next_move();
    game_.make_move(next_move.x, next_move.y);
    
    std::cout << next_move.x << "," << next_move.y << std::endl;
}

void Protocol::handle_info(const std::string &params)
{
    std::istringstream iss(params);
    std::string key, value;
    
    if (iss >> key >> value) {
        if (key == "timeout_turn") {
            // Acknowledge timeout setting but use internal timing
        } else if (key == "timeout_match") {
            // Acknowledge match timeout
        } else if (key == "max_memory") {
            // Acknowledge memory limit
        } else if (key == "game_type") {
            // Acknowledge game type
        }
    }
}

void Protocol::handle_end()
{
    running_ = false;
}