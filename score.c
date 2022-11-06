#include "score.h"
#include<stdio.h>
#include<string.h>
int score_letter[26];
void initialize_letter_score()
{
    for(int i = 0; i<26;i++)
    {
        int l=65 + i;
        printf("%c %d %d ",l,l,i);
        switch(l)
        {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
        case 'L':
        case 'N':
        case 'S':
        case 'T':
        case 'R':
            score_letter[i]=1;
            break;
        case 'D':
        case 'G':
            score_letter[i]=2;
            break;
        case 'B':
        case 'C':
        case 'M':
        case 'P':
            score_letter[i]=3;
            break;
        case 'F':
        case 'H':
        case 'V':
        case 'W':
        case 'Y':
            score_letter[i]=4;
            break;
        case 'K':
            score_letter[i]=5;
            break;
        case 'J':
        case 'X':
            score_letter[i]=8;
            break;
        case 'Q':
        case 'Z':
            score_letter[i]=10;
            break;


        }
        printf("- %d\n",score_letter[i]);

    }
}

int scoreword(char *word)
{
    int score = 0;
    printf("\n");
    for(int i=0;i<strlen(word);i++)
    {
        printf("%c - ",word[i]);
        int l = word[i] - 65;
        printf("%d\n",score_letter[l]);
        score += score_letter[l];
    }
    return score;
}


