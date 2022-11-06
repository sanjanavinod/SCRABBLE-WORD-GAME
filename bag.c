#include "bag.h"
#include <time.h>
#include <stdlib.h>
char bag[98];
int bag_size;
void initialize_bag()
{
    bag_size = 0;
    int i;
    for(char c='A'; c <='Z'; c++)
    {
        switch(c)
        {
        case 'E':
            {
                for(i=0; i < 12; i++)
                    bag[bag_size++] = c;
            }
        break;
        case 'A':
        case 'I':
            {
                for(i=0; i < 9; i++)
                    bag[bag_size++] = c;
            }
        break;
        case 'O':
            {
                for(i=0; i < 8; i++)
                    bag[bag_size++] = c;
            }
        break;
        case 'N':
        case 'R':
        case 'T':
            {
                for(i=0; i < 6; i++)
                    bag[bag_size++] = c;
            }
        break;
        case 'D':
        case 'L':
        case 'S':
        case 'U':
            {
                for(i=0; i < 4; i++)
                    bag[bag_size++] = c;
            }
        break;
        case 'G':
            {
                for(i=0; i < 3; i++)
                    bag[bag_size++] = c;
            }
        break;
        case 'B':
        case 'C':
        case 'F':
        case 'H':
        case 'M':
        case 'P':
        case 'V':
        case 'W':
        case 'Y':
            {
                bag[bag_size++] = c;
                bag[bag_size++] = c;
            }
        break;
        case 'J':
        case 'K':
        case 'Q':
        case 'X':
        case 'Z':
            {
                bag[bag_size++] = c;
            }
        break;
        }

    }
}

char pull_out_of_bag()
{
     int rin = (rand() % (bag_size - 0 + 1)) + 0;
     if(bag_size == 0)
        return ' ';
     char a = bag[rin];
     for(int i=rin;i < bag_size-1; i++)
     {
         bag[i] = bag[i+1];
     }
     bag_size--;

     return a;
}
void push_in_bag(char c)
{
    bag[bag_size++] = c;
}

