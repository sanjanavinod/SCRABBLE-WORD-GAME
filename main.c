
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "play_game.h"
#include "dictionary.h"
#include "settings.h"

int main()
{
    FILE *fptr;
    fptr = fopen("screen.txt","r");
    char ch[100];
    printf("\n\n");
    while(fgets(ch,100,fptr)!=NULL)
    {
        printf("\t\t\t\t\t%s",ch);

    }
    fclose(fptr);
    printf("\n\n");
    getch();
    load_settings();
    int exit = 0;
    do{
        char *s[] = {"Menu", "Play Game", "How to play", "Settings","Add word", "Exit"};
        int i = menu(s,5);
        switch(i)
        {
            case 1: play_game();
            break;
            case 2: printf("\n\tHow to Play");
            FILE *fptr;
            fptr = fopen("HowToPLay.txt","r");
            char ch[100];
            printf("\n\n");
            while(fgets(ch,100,fptr)!=NULL)
            {
                printf("\t\t\t%s",ch);

            }
            fclose(fptr);
            break;
            case 3: change_settings();
            break;
            case 4: add_word();
            break;
            case 5: printf("\nExited");
                exit = 1;
            break;
        }
        printf("\n");
        system("pause");
    }while(exit == 0);
    return 0;
}
