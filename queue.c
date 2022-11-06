#include<stdio.h>
#include "queue.h"
#include <stdlib.h>
#include "bag.h"
#include "score.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

void initialize_queue(queue *q)
{
    q->front = q->rear = NULL;

}

node* create_node(char data)
{

    node *n = (node*) malloc (sizeof (node));
    if(n==NULL)
    {
        return n;
    }
    n->data = data;
    n->prev = n->next = NULL;
    return n;
}

void enqueue(queue *q, char data)
{
    node *n = create_node(data);
    if(n==NULL)
    {
        printf("\nUnable to allocate memory\n");
    }
    if(q->rear == NULL)
    {
        q->front = q->rear = n;

    }
    else
    {
        q->rear->next = n;
        n->prev = q->rear;
        q->rear = n;
    }
}

char delete_node(queue *q,node *n)
{
    if(n == NULL)
    {
        printf("\nInvalid Index\n");
        return '.';
    }
    char ch;
    if(q->front == n && q->rear == n)
    {
        q->front = q->rear = NULL;
        ch = n->data;
        free(n);
        return ch;
    }
    if(q->front == n)
    {
        q->front->next->prev = NULL;
        q->front = q->front->next;
        ch = n->data;
        free(n);
        return ch;
    }
    else if(q->rear == n)
    {
        q->rear->prev->next = NULL;
        q->rear = q->rear->prev;
        ch = n->data;
        free(n);
        return ch;
    }
    else
    {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        ch = n->data;
        free(n);
        return ch;
    }

}

void clear_queue(queue *q)
{
    node *n = q->front;
    if(n == NULL)
        return;
    for(;n!=NULL;)
    {
        node *temp = n;
        n = n->next;
        push_in_bag(temp->data);
        free(temp);
    }
    q->front = q->rear = NULL;
}

void display_queue(queue q,node* selected)
{
    node *n = q.front;
    if(n == NULL)
        printf("\nQueue is empty");
    for(;n!=NULL; n=n->next)
    {
        if(n == selected)
            printf(GREEN);
        printf("%c ",n->data);
        printf(RESET);
    }
}
void copy_queue(queue *q1,queue *q2)
{
    node *n1 = q1->front;
    node *n2 = q2->front;
    if( n2 == NULL)
        printf("\nThe source Queue is empty");
    for(;n2!=NULL; n2=n2->next)
    {
        if(n1 == NULL)
        {
            enqueue(q1,n2->data);
            n1 = q1->rear;
        }
        else
            n1->data = n2->data;
        n1 = n1->next;
    }
}

