#ifndef NAVY_H
#define NAVY_H

typedef struct {
    int w, h;
    char cells[10][10];
} board_t;

typedef struct {
    board_t my;
    board_t enemy; // marks: 'x' hit, 'o' miss, '.' unknown
    int opponent_pid;
    int is_first; // 1 for player1 (starts), 0 for player2
    int enemy_hits; // how many successful hits we made on enemy (win at 14)
} game_t;

int write_all(int fd, const char *buf, int len);
int load_map(const char *path, board_t *b);
void print_board(const board_t *b);
void print_two_boards(const board_t *mine, const board_t *enemy);

// Signals / game communication
void setup_signal_handlers(void);
void set_opponent_pid(int pid);
int get_my_pid(void);

// Handshake
int wait_for_connection(void);           // player 1: waits, returns opponent pid
int connect_to_first(int first_pid);     // player 2: connects, returns 0 on success

// Coordinate protocol (A..J -> 1..10, 1..10)
int send_coord(int pid, int x1based, int y1based);
int recv_coord_blocking(int *x1based, int *y1based);

// Shot result: receiver sends result back (hit=1, miss=0)
int send_shot_result(int pid, int hit);
int recv_shot_result_blocking(void);
// Turn token
void send_turn_done(int pid);
void wait_turn_done_blocking(void);

// Game helpers
int parse_coord(const char *s, int *x1b, int *y1b); // A1..J10
int board_shot(board_t *b, int x0, int y0); // returns hit(1)/miss(0); updates with 'x'/'o'
int my_remaining(board_t *b); // number of ship cells not hit
void init_enemy(board_t *b);

#endif
