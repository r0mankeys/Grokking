// Implementing a queue for depth-first search

// A queue is a FIFO data structure
// Since the size of the queue is not known beforehand, we will use a linked list to implement it
// There are only two funcionalities that we need to implement for the queue: enqueue and dequeue
// The only way this really differs from a traditional linked list
// is that we will be adding elements to the tail of the list and removing elements from the head of the list

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header_files/queue.h"

queue_node *create_queue_node(char *data)
{
    queue_node *node = (queue_node *)malloc(sizeof(queue_node));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failure for queue node\n");
        return NULL;
    }
    node->data = strdup(data);
    if (!node->data)
    {
        fprintf(stderr, "Memory allocation failure for queue node data\n");
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

queue *create_queue()
{
    queue *new_queue = (queue *)malloc(sizeof(queue));
    if (!new_queue)
    {
        fprintf(stderr, "Memory allocation failure for queue\n");
        return NULL;
    }
    new_queue->tail = NULL;
    new_queue->head = NULL;
    new_queue->size = 0;

    return new_queue;
}

void free_queue_node(queue_node *node)
{
    free(node->data);
    free(node);
}

void free_queue(queue *queue)
{
    queue_node *current_node = queue->head;
    while (current_node)
    {
        queue_node *next_node = current_node->next; // Ensures we don't lose the reference to the next node
        free_queue_node(current_node);
        current_node = next_node;
    }
    free(queue);
}

void enqueue(queue *queue, char *data)
{
    queue_node *new_node = create_queue_node(data);
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failure for queue node (enqueue)\n");
        return;
    }
    if (queue->tail)
    {
        queue->tail->next = new_node;
    } else {
        queue->head = new_node;
    }
    queue->tail = new_node;
    queue->size++;
}

char *dequeue(queue *queue)
{
    if (!queue->head)
    {
        fprintf(stderr, "Queue is empty\n");
        return NULL;
    }

    queue_node *node_to_free = queue->head;
    char *data = node_to_free->data;
    queue->head = queue->head->next;

    if (!queue->head)
    {
        queue->tail = NULL; // If there was only one node in the queue, then the tail should be NULL
    }

    free(node_to_free); // Free the node that was dequeued
    queue->size--;
    return data;
}

void print_queue(queue *queue)
{
    printf("\nQueue\n--------------------\n");
    queue_node *current_node = queue->head;
    while (current_node)
    {
        printf(" %s  ", current_node->data);
        current_node = current_node->next;
    }
    printf("\n--------------------\n");
    printf("Size: %zu\n", queue->size);
}
