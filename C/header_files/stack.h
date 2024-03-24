#ifndef STACK_H
#define STACK_H

typedef struct stack_node {
    char *data;
    struct stack_node *next;
} stack_node;

typedef struct {
    stack_node *head;
    int size;
} stack;

stack_node *create_stack_node(char *data);
stack *create_stack();
void free_stack_node(stack_node *node);
void free_stack(stack *stack);
void stack_push(stack *stack, char *data);
char *stack_pop(stack *stack);
void print_stack(stack *stack);

#endif
