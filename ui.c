#include "ui.h"

int menu(char**s,int size)
{
    char *inden1="\n\n\n\n\n\n";
    char *inden2="\t\t\t\t\t";
    int ch=1;
    while(1){
    system("cls");
    printf("\n\n\n");
    printf("%s\tSCRABBLE\n\n",inden2);
    for(int i=1;i<=size;i++)
    {
        printf("%s|                   |\n",inden2);
        if(i==ch)
        {
            printf("%s| * %d. %-11s  |\n",inden2,i,s[i]);
        }
        else
            printf("%s|   %d. %-11s  |\n",inden2,i,s[i]);
    }
    printf("%s---------------------\n",inden2);

    int keypressed=getch();
    if (keypressed == 224) { // if the first value is esc
        keypressed=getch();
    switch(keypressed) { // the real value
        case 72:
            // code for arrow up
            if(ch!=1)
            {
                ch--;
            }
            else
                printf("\a");
            break;
        case 80:
            // code for arrow down
            if(ch!=size)
            {
                ch++;
            }
            else
                printf("\a");
            break;
        default:
            printf("\a");
    }}
    else if(keypressed==13)
        return ch;
    else
        printf("\a");

}
}

int menu2(char**s,int size)
{
    char *inden1="\n";
    char *inden2="\t\t\t\t\t";
    static int ch=1;
    printf("%s",inden1);
    for(int i=1;i<=size;i++)
    {
        printf("%s                   \n",inden2);
        if(i==ch)
        {
            printf("%s > %d. %-11s  \n",inden2,i,s[i]);
        }
        else
            printf("%s   %d. %-11s  \n",inden2,i,s[i]);
    }

    int keypressed=getch();
    if (keypressed == 224) { // if the first value is esc
        keypressed=getch();
    switch(keypressed) { // the real value
        case 72:
            // code for arrow up
            if(ch!=1)
            {
                ch--;
            }
            else
                printf("\a");
            break;
        case 80:
            // code for arrow down
            if(ch!=size)
            {
                ch++;
            }
            else
                printf("\a");
            break;
        default:
            printf("\a");
    }}
    else if(keypressed==13)
        return ch;
    else
        printf("\a");
    return 0;

}


