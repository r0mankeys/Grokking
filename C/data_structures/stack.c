// Implemeting a stack
// similar to a queue, but LIFO instead of FIFO
// I will use a linked list same as the queue
// The only difference is that we will be adding elements to the head of the list and removing elements from the head of the list

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header_files/stack.h"

stack_node *create_stack_node(char *data)
{
    stack_node *node = (stack_node *)malloc(sizeof(stack_node));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failure for stack node\n");
        return NULL;
    }
    node->data = strdup(data);
    if (!node->data)
    {
        fprintf(stderr, "Memory allocation failure for stack node data\n");
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

stack *create_stack()
{
    stack *new_stack = (stack *)malloc(sizeof(stack));
    if (!new_stack)
    {
        fprintf(stderr, "Memory allocation failure for stack\n");
        return NULL;
    }
    new_stack->head = NULL;
    new_stack->size = 0;
    return new_stack;
}

void free_stack_node(stack_node *node)
{
    free(node->data);
    free(node);
}

void free_stack(stack *stack)
{
    stack_node *current_node = stack->head;
    while (current_node)
    {
        stack_node *next_node = current_node->next;
        free_stack_node(current_node);
        current_node = next_node;
    }
    free(stack);
}

void stack_push(stack *stack, char *data)
{
    stack_node *new_node = create_stack_node(data);
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failure for stack node (stack push)\n");
        return;
    }
    if (stack->head)
    {
        new_node->next = stack->head;
    }
    stack->head = new_node;
    stack->size++;
}

char *stack_pop(stack *stack)
{
    if (!stack->head)
    {
        fprintf(stderr, "Stack is empty\n");
        return NULL;
    }

    stack_node *node_to_pop = stack->head;
    char* data = stack->head->data;
    stack->head = stack->head->next;

    free(node_to_pop); // free the node that was popped (not the data it contains)
    stack->size--;
    return data;
}

void print_stack(stack *stack)
{
    printf("\nStack\n-------------------\n");
    stack_node *current_node = stack->head;
    while (current_node)
    {
        printf(" %s ", current_node->data);
        printf("\n");
        current_node = current_node->next;
    }
    printf("-------------------\n");
    printf("Size: %lu\n", stack->size);
}
