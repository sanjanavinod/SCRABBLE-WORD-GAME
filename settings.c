#include "settings.h"
#include "stdio.h"

int size;
int player_size;
void load_settings()
{
    FILE *fp;
    fp = fopen("settings.bin","r");
    struct setting s;
    if(fp == NULL)
    {
        s.size = 15;
        s.playerno = 4;
        fp = fopen("settings.bin","w");
        fwrite(&s,sizeof(s),1,fp);
        fclose(fp);
        size = s.size;
        player_size = s.playerno;
        return;
    }
    fread(&s,sizeof(s),1,fp);
    size = s.size;
    player_size = s.playerno;
    fclose(fp);
}

void change_settings()
{
    int exit = 0;
    struct setting s;
    s.size = size;
    int t;
    s.playerno = player_size;
    FILE *fp;
    fp = fopen("settings.bin","r+");
    do {
    printf("\n\n The current settings:\n\n1) Board Size:  %d\n2) No of players: %d\n\n3) Exit\n\n",s.size,s.playerno);
    int ch;
    printf("Enter your choice:");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1: printf("Enter new value of Board size(4 - 15):");
                scanf("%d",&t);
                if(t < 4 || t > 15)
                    printf("Invalid size");
                else
                    s.size = t;
        break;
        case 2: printf("Enter new value of Player number(2 - 4):");
                scanf("%d",&t);
                if(t < 2 || t > 4)
                    printf("Invalid size");
                else
                    s.playerno = t;
        break;
        case 3: exit = 1;
        break;
    }
    }while(exit == 0);
    fwrite(&s,sizeof(s),1,fp);
    fclose(fp);
    load_settings();
}

