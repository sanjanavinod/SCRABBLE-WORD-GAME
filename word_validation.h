#ifndef WORD_VALIDATION_H
#define WORD_VALIDATION_H
#include "play_game.h"
typedef struct {
    int x;
    int y;
} indexes;

char* give_possible_words(Board b, indexes[], int index_size);
int check_valid(indexes index[],int index_size);
#endif // WORD_VALIDATION_H
