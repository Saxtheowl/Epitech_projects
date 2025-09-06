/*
** EPITECH PROJECT, 2025
** Gomoku
** File description:
** Gomoku AI implementation
*/

#include "gomoku.h"

Gomoku::Gomoku() : board_(BOARD_SIZE, std::vector<CellState>(BOARD_SIZE, EMPTY)),
                   current_player_(PLAYER)
{
}

Gomoku::~Gomoku()
{
}

void Gomoku::start_game(int size)
{
    reset_board();
    current_player_ = PLAYER;
}

void Gomoku::reset_board()
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board_[i][j] = EMPTY;
        }
    }
}

bool Gomoku::is_valid_position(int x, int y) const
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE &&
           board_[y][x] == EMPTY;
}

void Gomoku::make_move(int x, int y)
{
    if (is_valid_position(x, y)) {
        board_[y][x] = PLAYER;
    }
}

void Gomoku::opponent_move(int x, int y)
{
    if (is_valid_position(x, y)) {
        board_[y][x] = OPPONENT;
    }
}

bool Gomoku::is_timeout() const
{
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        current_time - start_time_).count();
    return elapsed > TIME_LIMIT;
}

int Gomoku::count_direction(int x, int y, int dx, int dy, CellState player) const
{
    int count = 0;
    int nx = x + dx;
    int ny = y + dy;

    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE &&
           board_[ny][nx] == player) {
        count++;
        nx += dx;
        ny += dy;
    }
    return count;
}

int Gomoku::evaluate_position(const Position &pos, CellState player) const
{
    if (!is_valid_position(pos.x, pos.y))
        return -10000;

    int score = 0;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (int i = 0; i < 4; i++) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        
        int count1 = count_direction(pos.x, pos.y, dx, dy, player);
        int count2 = count_direction(pos.x, pos.y, -dx, -dy, player);
        int total = count1 + count2 + 1;

        if (total >= WIN_CONDITION) {
            score += 100000;
        } else if (total == 4) {
            score += 10000;
        } else if (total == 3) {
            score += 1000;
        } else if (total == 2) {
            score += 100;
        }
    }

    int center_distance = abs(pos.x - BOARD_SIZE/2) + abs(pos.y - BOARD_SIZE/2);
    score += (BOARD_SIZE - center_distance) * 2;

    return score;
}

bool Gomoku::check_line(int x, int y, int dx, int dy, CellState player) const
{
    int count = 1;
    int nx, ny;

    nx = x + dx;
    ny = y + dy;
    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE &&
           board_[ny][nx] == player) {
        count++;
        nx += dx;
        ny += dy;
    }

    nx = x - dx;
    ny = y - dy;
    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE &&
           board_[ny][nx] == player) {
        count++;
        nx -= dx;
        ny -= dy;
    }

    return count >= WIN_CONDITION;
}

bool Gomoku::check_win(CellState player) const
{
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board_[y][x] == player) {
                for (int i = 0; i < 4; i++) {
                    if (check_line(x, y, directions[i][0], directions[i][1], player)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int Gomoku::evaluate_board() const
{
    if (check_win(PLAYER))
        return 1000000;
    if (check_win(OPPONENT))
        return -1000000;

    int score = 0;
    
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board_[y][x] != EMPTY) {
                Position pos(x, y);
                int pos_score = evaluate_position(pos, board_[y][x]);
                if (board_[y][x] == PLAYER) {
                    score += pos_score;
                } else {
                    score -= pos_score;
                }
            }
        }
    }
    
    return score;
}

std::vector<Position> Gomoku::get_candidate_moves() const
{
    std::vector<Position> candidates;
    
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board_[y][x] == EMPTY) {
                bool has_neighbor = false;
                
                for (int dy = -2; dy <= 2 && !has_neighbor; dy++) {
                    for (int dx = -2; dx <= 2 && !has_neighbor; dx++) {
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE) {
                            if (board_[ny][nx] != EMPTY) {
                                has_neighbor = true;
                            }
                        }
                    }
                }
                
                if (has_neighbor || candidates.empty()) {
                    candidates.push_back(Position(x, y));
                }
            }
        }
    }
    
    if (candidates.empty()) {
        candidates.push_back(Position(BOARD_SIZE/2, BOARD_SIZE/2));
    }
    
    return candidates;
}

int Gomoku::minimax(int depth, int alpha, int beta, bool maximizing_player)
{
    if (depth == 0 || is_timeout()) {
        return evaluate_board();
    }

    if (check_win(PLAYER)) {
        return 1000000 - (MAX_DEPTH - depth);
    }
    if (check_win(OPPONENT)) {
        return -1000000 + (MAX_DEPTH - depth);
    }

    std::vector<Position> moves = get_candidate_moves();
    
    if (maximizing_player) {
        int max_eval = INT_MIN;
        
        for (const Position &move : moves) {
            if (is_timeout()) break;
            
            board_[move.y][move.x] = PLAYER;
            int eval = minimax(depth - 1, alpha, beta, false);
            board_[move.y][move.x] = EMPTY;
            
            max_eval = std::max(max_eval, eval);
            alpha = std::max(alpha, eval);
            
            if (beta <= alpha) {
                break;
            }
        }
        return max_eval;
    } else {
        int min_eval = INT_MAX;
        
        for (const Position &move : moves) {
            if (is_timeout()) break;
            
            board_[move.y][move.x] = OPPONENT;
            int eval = minimax(depth - 1, alpha, beta, true);
            board_[move.y][move.x] = EMPTY;
            
            min_eval = std::min(min_eval, eval);
            beta = std::min(beta, eval);
            
            if (beta <= alpha) {
                break;
            }
        }
        return min_eval;
    }
}

Position Gomoku::find_best_move()
{
    start_time_ = std::chrono::steady_clock::now();
    
    std::vector<Position> moves = get_candidate_moves();
    Position best_move = moves[0];
    int best_score = INT_MIN;

    for (const Position &move : moves) {
        if (is_timeout()) break;
        
        board_[move.y][move.x] = PLAYER;
        
        if (check_win(PLAYER)) {
            board_[move.y][move.x] = EMPTY;
            return move;
        }
        
        int score = minimax(MAX_DEPTH - 1, INT_MIN, INT_MAX, false);
        board_[move.y][move.x] = EMPTY;
        
        if (score > best_score) {
            best_score = score;
            best_move = move;
        }
    }

    return best_move;
}

Position Gomoku::get_next_move()
{
    return find_best_move();
}

bool Gomoku::is_game_over() const
{
    return check_win(PLAYER) || check_win(OPPONENT);
}

void Gomoku::print_board() const
{
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board_[y][x] == EMPTY) {
                std::cout << ".";
            } else if (board_[y][x] == PLAYER) {
                std::cout << "X";
            } else {
                std::cout << "O";
            }
        }
        std::cout << std::endl;
    }
}