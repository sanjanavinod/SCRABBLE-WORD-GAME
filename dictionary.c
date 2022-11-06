#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **arr;
int word_size = 0;
void insertionSort(char **a, int n);

void init_arr()
{
    arr = (char**)malloc(45*sizeof(char*));
    for(int i=0; i < 45; i++)
    {
        arr[i] = (char*)malloc(16*sizeof(char));
        strcpy(arr[i],"");
    }
    word_size = 0;
}

void free_arr()
{
    for(int i=0; i < 45; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

int load_file(char *filename)
{
    FILE *fptr;
    fptr = fopen(filename,"r");
    if(fptr == NULL)
        return -1;
    char a[16];
    while(fscanf(fptr,"%s",a) == 1)
    {
        strcpy(arr[word_size],a);
        word_size++;
    }
    fclose(fptr);
    return 0;
}

int write_to_file(char *filename,char *word)
{
    FILE *fptr;
    fptr = fopen(filename,"w");
    if(fptr == NULL)
        return -1;
    word_size++;
    strcpy(arr[word_size-1],word);
    insertionSort(arr,word_size);
    for(int i=0;i < word_size; i++)
    {
        fprintf(fptr,"%s\n",arr[i]);
    }
    fclose(fptr);
    return 0;
}

int compare_words(char *a, char *b)
{
    int i = 0;
    while(a[i] != '\0' || b[i] != '\0')
    {
       if(a[i] < b[i])
       {
           return -1;
       }
       else if(a[i] > b[i])
       {
           return 1;
       }
       i++;
    }
    if(strlen(a) > i)
        return 1;
    else if(strlen(b) > i)
        return -1;
    else
        return 0;
}

int find_in_arr(char * a)
{
    for(int i=0; i < word_size; i++)
    {
        if(strcmpi(arr[i],a) == 0)
            return 1;
    }
    return 0;
}
int binarySearch(char **a, char item[], int low, int high)
{
    if (high <= low)
        return (compare_words(item,a[low]) == 1)?  (low + 1): low;

    int mid = (low + high)/2;

    if(strcmpi(item,a[mid]) == 0)
        return mid+1;

    if(compare_words(item,a[mid]) == 1)
        return binarySearch(a, item, mid+1, high);
    return binarySearch(a, item, low, mid-1);
}

void insertionSort(char **a, int n)
{
    int i, loc, j;
    char selected[45];

    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        strcpy(selected,a[i]);

        // find location where selected should be inserted
        loc = binarySearch(a, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc)
        {
            strcpy(a[j+1],a[j]);
            j--;
        }
        strcpy(a[j+1],selected);
    }
}

int convert_to_upper(char *w)
{
    if(w == NULL)
        return 0;
    for(int i=0; w[i]!='\0'; i++)
    {
        if(!isalpha(w[i]))
            return -1;
        w[i] = toupper(w[i]);
    }
    return 1;
}
void add_word()
{
    printf("Enter the word you want to add(max length 15):");
    char s[45];
    scanf("%s",s);
    if(convert_to_upper(s) == -1)
    {
        printf("\nThe word contains characters that are not alphabets.\n");
        return;
    }
    char filename[10];
    filename[0] = toupper(s[0]);
    filename[1] = '\0';
    strcat(filename,".txt");
   init_arr();
   if(load_file(filename)== -1)
        printf("\nNo file exists of this letter. Creating a file..\n");
    else
    {

        if(word_size == 45)
        {
            printf("\n This letter already has 45 words. Cannot add more.\n");
            return;
        }
        int f = find_in_arr(s);
        if(f == 1)
        {
            printf("\nThe word already exists.");
            return;
        }
    }

    write_to_file(filename,s);
}

int find_word(char *s)
{
    char filename[10];
    filename[0] = toupper(s[0]);
    filename[1] = '\0';
    strcat(filename,".txt");
   init_arr();
   if(load_file(filename)== -1)
        return 0;
    else
    {

        if(find_in_arr(s))
        {
            return 1;
        }
       else
       {
           return 0;
       }
    }
    return 0;
}
