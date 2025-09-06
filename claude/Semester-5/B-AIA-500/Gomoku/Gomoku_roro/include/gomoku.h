/*
** EPITECH PROJECT, 2025
** Gomoku
** File description:
** Main header file for Gomoku AI
*/

#ifndef GOMOKU_H_
    #define GOMOKU_H_

    #include <iostream>
    #include <string>
    #include <vector>
    #include <sstream>
    #include <algorithm>
    #include <climits>
    #include <chrono>

    #define BOARD_SIZE 20
    #define WIN_CONDITION 5
    #define MAX_DEPTH 6
    #define TIME_LIMIT 4500

    enum CellState {
        EMPTY = 0,
        PLAYER = 1,
        OPPONENT = 2
    };

    struct Position {
        int x;
        int y;
        Position(int x = 0, int y = 0) : x(x), y(y) {}
    };

    class Gomoku {
    private:
        std::vector<std::vector<CellState>> board_;
        CellState current_player_;
        std::chrono::steady_clock::time_point start_time_;
        
        bool is_valid_position(int x, int y) const;
        bool is_timeout() const;
        int evaluate_position(const Position &pos, CellState player) const;
        int count_direction(int x, int y, int dx, int dy, CellState player) const;
        int evaluate_board() const;
        std::vector<Position> get_candidate_moves() const;
        int minimax(int depth, int alpha, int beta, bool maximizing_player);
        Position find_best_move();
        bool check_win(CellState player) const;
        bool check_line(int x, int y, int dx, int dy, CellState player) const;

    public:
        Gomoku();
        ~Gomoku();
        
        void start_game(int size);
        void make_move(int x, int y);
        void opponent_move(int x, int y);
        Position get_next_move();
        void reset_board();
        bool is_game_over() const;
        void print_board() const;
    };

#endif /* !GOMOKU_H_ */