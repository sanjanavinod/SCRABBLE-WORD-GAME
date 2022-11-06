#include <stdio.h>
#include <stdlib.h>
#include "play_game.h"
#include "gamestatestack.h"
#include "word_validation.h"
#include <time.h>
#include "score.h"
#include "settings.h"
#include "dictionary.h"
#include "bag.h"
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* YELLOW*/
char rackfunc(game_state *g1, int *x, int *y, stack *gst_s,node **selected, int *phase, int* lselected,indexes index[],int *index_size);
void boardfunc(game_state *g1, int *x, int *y, stack *gst_s,node **selected, int *phase, int* lselected, char c, indexes index[],int *index_size);
void display(game_state G, node* letter, int x_in_board,int y_in_board,char l, indexes index[],int index_size);
void free_gamestate(game_state *g1);

void game_over(player* p)
{
    int flag = 0;
    system("cls");
    printf("\n\n\n\t\t\tGAME OVER\n\t\t\t");
    printf("The winner  is ");
    int highest_score = 0;
    for(int i=0; i < player_size; i++)
    {
        if(p[i].player_score >=highest_score)
            highest_score = p[i].player_score;

    }
    for(int i=0; i < player_size; i++)
    {
        if(p[i].player_score == highest_score)
        {
            if(flag == 1)
                printf(" and ");
            printf("Player %d", i+ 1);
            flag = 1;
        }
    }
    printf("\n");
    printf("\t\t\tHigh score : %d\n\n", highest_score);
    system("pause");

}
void play_game()
{
    initialize_bag();
    initialize_letter_score();
    srand(time(0));
    game_state g1;
    stack gst_s;
    initialize_gst_stack(&gst_s);
    initialize_game_state(&g1);
    push(&gst_s,g1);
    node * selected = g1.player_of_current_state[g1.current_player].rack.front;
    int x = -1;
    int y = -1;
    int phase = 0;
    char c='.';
    int lselected = 0;
    int index_size=0;
    indexes index[15];
    for(int i=0; i < 15; i++)
        index[i].x = -1;

    while(1){
    display(g1,selected,x,y,c,index,index_size);
    if(phase == 0){
        c = rackfunc(&g1, &x, &y, &gst_s,&selected, &phase, &lselected,index,&index_size);
        if(c == '-')
         {
            free_gamestate(&g1);
            while(gst_s.top !=NULL)
                pop(&gst_s);
            return;
         }
    }
    else
    {
        if(gst_s.top->next == NULL && index_size == 0)
        {
            x = size/2-1;
            y = size/2-1;
        }
      boardfunc(&g1, &x, &y, &gst_s,&selected, &phase,&lselected,c,index,&index_size);
    }
    }

}

void initialize_game_state(game_state *g)
{
    initialize_board(&g->current_board);
    for(int i=0; i < player_size; i++)
    {
        initialize_player(&g->player_of_current_state[i]);
    }
    g->current_player = 0;
}

void initialize_game_state_without_bag(game_state *g)
{
    initialize_board(&g->current_board);

    for(int i=0; i < player_size; i++)
    {
        player *p = &g->player_of_current_state[i];
        initialize_queue(&p->rack);
        p->player_score = 0;
        char a;
        for(int i=0; i < 7; i++)
        {
            a = ' ';
            enqueue(&p->rack,a);
    }
    }
    g->current_player = 0;
}

void initialize_player(player *p)
{
    initialize_queue(&p->rack);
    p->player_score = 0;
    char a;
    for(int i=0; i < 7; i++)
    {
        a = pull_out_of_bag();
        enqueue(&p->rack,a);
    }
}



void initialize_board(Board *b)
{

    *b = (Board)malloc(size*sizeof(char*));
    for(int i=0 ; i<size ; i++)
    {
        (*b)[i]=(char*)malloc(size*sizeof(char));
        for(int j=0 ; j<size ; j++)
        {
                (*b)[i][j] = '-';
        }
    }
}



void display(game_state G, node* letter, int x_in_board,int y_in_board,char l,indexes index[],int index_size)
{
    system("cls");
    printf("\n\t\t\tSCRABBLE\n\n");

    for(int i=0 ; i<size ;i++)
    {
        printf("\t\t");
        for(int j=0 ; j<size ; j++)
        {
            int index_in_board = 0;
            for(int k=0 ; k<index_size ; k++)
            {
                if(index[k].x == j && index[k].y == i)
                {
                        index_in_board = 1;
                        break;
                }
            }
            if(i == y_in_board && j == x_in_board)
            {
                if(G.current_board[i][j] == '-')
                   printf(GREEN);
                else
                    printf(RED);
                printf("%c ",l);
                printf(RESET);
                continue;
            }
            else if(index_in_board == 1)
            {

                printf(YELLOW);
            }
            printf("%c ",G.current_board[i][j]);
            printf(RESET);
        }
        if(i < player_size)
            printf("\t\t\tPlayer %d : %d",i+1,G.player_of_current_state[i].player_score);
        printf("\n");
    }

    printf("\n\n\t\tPlayer %d",G.current_player + 1);
    printf("\n\n\t\t");
    display_queue(G.player_of_current_state[G.current_player].rack,letter);

}



void copy_gamestate(game_state *g1, game_state g2)
{

    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            g1->current_board[i][j] = g2.current_board[i][j];

        }
    }

    for(int i=0;i<player_size;i++)
    {
        copy_queue(&g1->player_of_current_state[i].rack,&g2.player_of_current_state[i].rack);
        g1->player_of_current_state[i].player_score = g2.player_of_current_state[i].player_score;
    }

    g1->current_player = g2.current_player;

}

char rackfunc(game_state *g1, int *x, int *y, stack *gst_s,node **selected, int *phase,int* lselected, indexes index[],int *index_size)
{
    if(g1->player_of_current_state[g1->current_player].rack.front == NULL)
    {
        printf("\n No tiles left. Press 'R' to reset or spacebar to finish turn");
    }
    int keypressed=getch();
    if (keypressed == 224) { // if the first value is esc
        keypressed=getch();
    switch(keypressed) { // the real value
        case 75:
            // code for arrow left
            if((*selected)->prev != NULL)
            {
                (*selected) = (*selected)->prev;
            }
            else
                printf("\a");
            break;
        case 77:
            // code for arrow right
            if((*selected)->next!= NULL)
            {
                (*selected) = (*selected)->next;
            }
            else
                printf("\a");
            break;
        default:
            printf("\a");
    }}
    else if(keypressed==13)//enter key
    {
         char c = delete_node(&g1->player_of_current_state[g1->current_player].rack,(*selected));
         lselected++;
         (*selected) = NULL;
         (*x) = 0;
        (*y) = 0;
         (*phase) = 1;
         return c;
    }
    else if(keypressed == 32)//space bar
    {
        if(!check_valid(index,*index_size))
        {
            printf("\nSorry invalid move.\n");
            system("pause");
            goto reset;
        }
        int flag = 1;
        for(int i=0; i < size; i++)
            for(int j = 0; j < size; j++)
                if(g1->current_board[i][j] == '-')
                {
                    flag = 0;
                    break;
                }
        if(flag == 1)
        {
            game_over(g1->player_of_current_state);
            return '-';
        }

        char a;
        for(int i=0; i < (*index_size); i++)
        {
            a = pull_out_of_bag();
            if(a == ' ')
                return ' ';
            enqueue(&g1->player_of_current_state[g1->current_player].rack,a);
        }
        char *s;
        init_arr();
        s = give_possible_words(g1->current_board,index, *index_size);
        printf("\nThe word: %s",s);
        int sc = scoreword(s);
        if(sc == 0)
        {
            printf("\nIt is not a valid word.");
            free(s);
            free_arr();
            goto reset;
        }
        g1->player_of_current_state[g1->current_player].player_score += sc;
        free(s);
        free_arr();
        system("pause");
        index[0].x = -1;
        (*index_size) = 0;
        (*lselected) = 0;
        (*x) = -1;
        (*y) = -1;
        if(g1->current_player!=player_size-1)
        {
            g1->current_player++;
        }
        else
            g1->current_player = 0;

        push(gst_s,*g1);

        (*selected) = g1->player_of_current_state[g1->current_player].rack.front;
        for(node_gst *n = gst_s->top; n!=NULL; n=n->next)
        {
            printf("\n");
            for(int i=0; i < size; i++)
            {
                for(int j=0; j < size; j++)
                    printf("%c ",n->data.current_board[i][j]);
                printf("\n");
            }
        }
        system("pause");

    }
    else if(keypressed == 'r')//reset
    {
        reset:
        copy_gamestate(g1,gst_s->top->data);
       (*selected) = g1->player_of_current_state[g1->current_player].rack.front;
        (*x) = -1;
        (*y) = -1;
        index[0].x = -1;
        (*lselected) = 0;
        *phase = 0;
        (*index_size) = 0;
    }
    else if(keypressed == 'c')// it will change the elements in rack
    {
        if(*index_size == 0)
        {
            char a;
            clear_queue(&g1->player_of_current_state[g1->current_player].rack);
            for(int i=0; i < 7; i++)
            {
                a = pull_out_of_bag();
                enqueue(&g1->player_of_current_state[g1->current_player].rack,a);
            }
            (*selected) = g1->player_of_current_state[g1->current_player].rack.front;
        }
        else
            printf("\a");
    }
    else if(keypressed == 'q')//quit
    {
       game_over(g1->player_of_current_state);
       printf("\n\n");
        return '-';
    }
    else
        printf("\a");
    return ' ';
}

void boardfunc(game_state *g1, int *x, int *y, stack *gst_s,node **selected, int *phase,int *lselected, char c,indexes index[],int *index_size)
{
    if(gst_s->top->next == NULL && *index_size == 0)
        goto enterch;
    int keypressed=getch();
    if (keypressed == 224) { // if the first value is esc
        keypressed=getch();
    switch(keypressed) { // the real value
        case 72:
            // code for arrow up
            if((*y)-1!= -1)
            {
                (*y) = (*y)-1;
            }
            else
                printf("\a");
            break;
        case 80:
            // code for arrow down
            if((*y)+1!= size)
            {
                (*y) = (*y)+1;
            }
            else
                printf("\a");
            break;
        case 75:
            //code for left
            if((*x)-1!=-1)
            {
                (*x) = (*x)-1;
            }
            else
                printf("\a");
            break;
        case 77:
            //code for right
            if((*x)+1!=size)
            {
                (*x) = (*x) + 1;
            }
            else
                printf("\a");
            break;
        default:
            printf("\a");
    }}
    else if(keypressed==13)
    {
        enterch:
         if(g1->current_board[(*y)][(*x)]!='-')
         {
             printf("\a");
             return ;
         }
         else
         {
             g1->current_board[(*y)][(*x)] = c;
         }
         index[*index_size].x = *x;
         index[*index_size].y = *y;
         (*index_size) = (*index_size) + 1;
         *selected = g1->player_of_current_state[g1->current_player].rack.front;
         *x = -1;
         (*y) = -1;
         (*phase) = 0;
    }
    else if(keypressed == 'r')
    {
        copy_gamestate(g1,gst_s->top->data);
       *selected = g1->player_of_current_state[g1->current_player].rack.front;
        *x = -1;
        (*y) = -1;
        index[0].x = -1;
        *phase = 0;
        (*index_size) = 0;
    }
    else
        printf("\a");
}

void free_gamestate(game_state *g1)
{
    for(int i=0;i<size;i++)
    {
        free(g1->current_board[i]);
    }

    for(int i=0;i<player_size;i++)
    {
        clear_queue(&g1->player_of_current_state[i].rack);
    }
}
