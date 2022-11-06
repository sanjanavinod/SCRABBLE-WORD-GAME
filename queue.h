#ifndef QUEUE_H
#define QUEUE_H

typedef struct node
{
    char data;
    struct node* prev;
    struct node* next;

}node;

typedef struct
{
    node* front;
    node* rear;
}queue;

void initialize_queue(queue *q);
node* create_node(char data);
void enqueue(queue *q, char data);
char delete_node(queue *q,node* t);
void display_queue(queue q, node* selected);
void copy_queue(queue *q1,queue *q2);
void clear_queue(queue *q);
#endif // QUEUE_H
