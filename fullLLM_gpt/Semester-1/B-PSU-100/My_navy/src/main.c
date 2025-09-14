#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/navy.h"
#include <signal.h>
#include <ctype.h>

static void usage(const char *p)
{
    printf("USAGE\n    %s [first_player_pid] navy_positions\n\nDESCRIPTION\n    first_player_pid: only for the 2nd player. pid of the first player.\n    navy_positions: file representing the positions of the ships.\n", p);
}

int main(int ac, char **av)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    if (ac == 2 && strcmp(av[1], "-h") == 0) { usage(av[0]); return 0; }
    if (ac != 2 && ac != 3) { fprintf(stderr, "Invalid arguments. Use -h.\n"); return 84; }
    const char *mapfile = (ac == 2) ? av[1] : av[2];
    game_t g; memset(&g, 0, sizeof g); if (load_map(mapfile, &g.my) != 0) { fprintf(stderr, "Invalid map.\n"); return 84; }
    init_enemy(&g.enemy);
    setup_signal_handlers();
    int mypid = get_my_pid();
    printf("my_pid: %d\n", mypid);
    int opponent = 0;
    if (ac == 2) {
        printf("waiting for enemy connection...\n\n");
        opponent = wait_for_connection();
        printf("enemy connected\n\n");
        g.is_first = 1;
    } else {
        int first = atoi(av[1]);
        if (connect_to_first(first) != 0) { fprintf(stderr, "Connection failed\n"); return 84; }
        opponent = first;
        printf("successfully connected\n\n");
        g.is_first = 0;
    }
    set_opponent_pid(opponent);
    // MOVES mode: space or newline separated coords used when it's our turn
    const char *moves = getenv("MOVES");
    const char *mp = moves && *moves ? moves : NULL;

    // Simple loop: alternate turns for a limited number of iterations
    int turns = 0; int max_turns = 50;
    while (turns < max_turns) {
        // Check if I lost
        if (my_remaining(&g.my) == 0) { printf("I lose\n"); break; }
        if (g.enemy_hits >= 14) { printf("I win\n"); break; }
        if ((g.is_first && (turns % 2 == 0)) || (!g.is_first && (turns % 2 == 1))) {
            // My turn to attack
            int x1=0,y1=0;
            char buf[32]={0};
            if (mp) {
                while (*mp && isspace((unsigned char)*mp)) mp++;
                int bi=0; while (*mp && !isspace((unsigned char)*mp) && bi< (int)sizeof(buf)-1) buf[bi++]=*mp++;
                buf[bi]='\0';
            } else {
                printf("attack: "); fflush(stdout);
                if (!fgets(buf, sizeof buf, stdin)) break;
                buf[strcspn(buf,"\r\n")]='\0';
            }
            if (buf[0] == '\0') { printf("no move\n"); break; }
            if (parse_coord(buf, &x1, &y1) != 0) { printf("wrong position\n"); turns++; continue; }
            send_coord(opponent, x1, y1);
            int hit = recv_shot_result_blocking();
            int x0 = x1-1, y0=y1-1;
            g.enemy.cells[y0][x0] = hit ? 'x' : 'o';
            if (hit) g.enemy_hits++;
            printf("result: %s\n", hit?"hit":"miss");
            if (g.enemy_hits >= 14) { printf("I win\n"); break; }
            // Wait for defender to signal end-of-turn
            wait_turn_done_blocking();
        } else {
            // Opponent turn: receive shot, answer
            int rx, ry; recv_coord_blocking(&rx,&ry);
            int hx = board_shot(&g.my, rx-1, ry-1);
            send_shot_result(opponent, hx);
            // Signal end-of-turn to attacker
            send_turn_done(opponent);
            if (my_remaining(&g.my) == 0) { printf("I lose\n"); break; }
        }
        turns++;
    }
    // Print final boards
    print_two_boards(&g.my, &g.enemy);
    return 0;
}
