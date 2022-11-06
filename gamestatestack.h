#ifndef GAMESTATESTACK_H
#define GAMESTATESTACK_H
#include "play_game.h"

typedef struct node_gst
{
    game_state data;
    struct node_gst* next;
}node_gst;

typedef struct
{
    node_gst* top;

}stack;

void initialize_gst_stack(stack *s);
void initialize_node_gst(node_gst *n);
node_gst* createnode(game_state g);
void push(stack *s,game_state g);
void pop(stack *s);










#endif // GAMESTATESTACK_H
