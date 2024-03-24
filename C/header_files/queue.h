#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_node {
    char *data;
    struct queue_node *next;
} queue_node;

typedef struct queue {
    queue_node *tail;
    queue_node *head;
    int size;
} queue;

queue_node *create_queue_node(char *data);
queue *create_queue();
void free_queue_node(queue_node *node);
void free_queue(queue *queue);
void enqueue(queue *queue, char *data);
char *dequeue(queue *queue);
void print_queue(queue *queue);

#endif
