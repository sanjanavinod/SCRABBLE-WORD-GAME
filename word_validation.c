#include "word_validation.h"
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* word;

int ifreplaceable(char *dest,char *w)
{
    if(!find_word(w))
        return 0;
    else if(strlen(w) < strlen(dest))
        return 0;
    else
        return 1;
}

void word_initialize(word *w)
{
    *w = NULL;
}

void word_pushfront(word *w, char a)
{
    if(*w == NULL)
    {
       *w = (char*)malloc(2*sizeof(char));
       (*w)[0] = a;
       (*w)[1] = '\0';
       return;
    }
    word temp = (char*)malloc((strlen((*w)) + 1)*sizeof(char));
    temp[0] = a;
    for(int i=0; i <strlen((*w)); i++)
        temp[i+1] = (*w)[i];
    temp[strlen(*w) + 1] = '\0';
    free((*w));
    *w = temp;
}
void word_pushback(word *w, char a)
{
    if(*w == NULL)
    {
       *w = (char*)malloc(2*sizeof(char));
       (*w)[0] = a;
       (*w)[1] = '\0';
       return;
    }
    word temp = (char*)malloc((strlen((*w)) + 1)*sizeof(char));

    for(int i=0; i <strlen((*w)); i++)
        temp[i] = (*w)[i];
    temp[strlen(*w)] = a;
    temp[strlen(*w) + 1] = '\0';
    free((*w));
    *w = temp;
}
void word_popback(word *w)
{
    if(*w == NULL)
    {
        printf("\n Underflow");
        return;
    }
    else if(strlen(*w) == 1)
    {
        free(*w);
        *w = NULL;
    }
    else
    {
        (*w)[strlen(*w)-1] = '\0';
    }
}
void word_clear(word *w)
{
    free(*w);
    *w = NULL;
}

int check_valid(indexes index[],int index_size)
{
    if(index_size == 0)
        return 0;
    else if(index_size == 1)
        return 1;
    else
    {
        int i, j;
        for(i=0; i < index_size; i++)
        {
            if(index[i].x != index[0].x )
                break;
        }
        for(j=0; j < index_size; j++)
        {
            if(index[j].y != index[0].y )
                break;
        }
        if(j == index_size)
            return 2;
        else if(i == index_size)
            return 3;
        return 0;
    }
}

char* give_possible_words(Board b, indexes index[], int index_size)
{
    system("pause");
    if(index_size == 0 )
        return " ";
    word w;
    char vertical_largest_word[20] = "";
    char horizontal_largest_word[20] = "";
    word_initialize(&w);
     int k= 0;
    for(int i=0; i < index_size;i++)
    {
        for(int j = 0; index[i].x - j >=0; j++ )
        {
            if(b[index[i].y][index[i].x - j]=='-')
                break;
            word_pushfront(&w,b[index[i].y][index[i].x - j]);
            printf("\nWord: %s",w);
            if(ifreplaceable(horizontal_largest_word,w))
                strcpy(horizontal_largest_word,w);
            for(k = 1; index[i].x + k >=0 && index[i].x + k < size; k++ )
            {
                if(b[index[i].y][index[i].x + k]=='-')
                    break;
                word_pushback(&w,b[index[i].y][index[i].x + k]);
               printf("\nWord: %s",w);
                if(ifreplaceable(horizontal_largest_word,w))
                    strcpy(horizontal_largest_word,w);
            }
            for(int m = 1; m <k; m++)
                word_popback(&w);
        }
        word_clear(&w);
        for(int j = 0; (index[i].y - j) >=0; j++ )
        {
            if(b[index[i].y - j][index[i].x]=='-')
                break;
            word_pushfront(&w,b[index[i].y - j][index[i].x]);
            printf("\nWord: %s",w);
            if(ifreplaceable(vertical_largest_word,w))
                strcpy(vertical_largest_word,w);
            for(k = 1; index[i].y + k >=0 && index[i].y + k < size; k++ )
            {
                if(b[index[i].y + k][index[i].x]=='-')
                    break;
                word_pushback(&w,b[index[i].y + k][index[i].x]);
                printf("\nWord: %s",w);
                if(ifreplaceable(vertical_largest_word,w))
                    strcpy(vertical_largest_word,w);
            }
            for(int m = 1; m <k; m++)
                word_popback(&w);
        }
        word_clear(&w);
    }
    char* str = (char*)malloc(16*sizeof(char));
    strcpy(str," ");
    printf("\nThe horizontal largest word:%s",horizontal_largest_word);
    printf("\nThe vertical largest word:%s",vertical_largest_word);
    int d = check_valid(index,index_size);
    if(d == 2)
        strcpy(str,horizontal_largest_word);
    else if(d == 3)
        strcpy(str,vertical_largest_word);
    else if(d == 1)
    {
        if(strlen(horizontal_largest_word) >=strlen(vertical_largest_word))
            strcpy(str,horizontal_largest_word);
        else
            strcpy(str,vertical_largest_word);
    }
    return str;
}

