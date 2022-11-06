#include<stdio.h>
#include<stdlib.h>
#include "gamestatestack.h"

void initialize_gst_stack(stack *s)
{
    s->top = NULL;
}

node_gst* createnode(game_state g)
{
    node_gst *n = (node_gst*) malloc(sizeof(node_gst));
    initialize_node_gst(n);
    copy_gamestate(&n->data,g);
    return n;
}

void push(stack *s,game_state g)
{
    node_gst *n = createnode(g);
    if(s->top == NULL)
    {
        s->top = n;
    }
    else
    {
        n->next = s->top;
        s->top = n;
    }
}

void pop(stack *s)
{
    node_gst* temp = s->top;
    s->top = s->top->next;
    free(temp);
}
void initialize_node_gst(node_gst *n)
{
    initialize_game_state_without_bag(&n->data);
    n->next = NULL;
}
