#ifndef PLAY_GAME_H
#define PLAY_GAME_H
#include "queue.h"

typedef char** Board;

typedef struct
{
    queue rack;
    int player_score;
}player;

typedef struct
{
    Board current_board;
    player player_of_current_state[4];
    int current_player;
}game_state;

typedef struct
{
    char c;
    int x;
    int y;
} letters_in_b;


void play_game();
void initialize_board(Board *b);

void initialize_player(player *p);
void initialize_game_state(game_state *g);
void copy_gamestate(game_state *g1, game_state g2);
void initialize_game_state_without_bag(game_state *g);

extern int size;

#endif // PLAY_GAME_H
