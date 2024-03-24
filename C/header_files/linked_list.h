#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct linked_list_node {
    char* data;
    struct linked_list_node *next;
} linked_list_node;

typedef struct linked_list {
    linked_list_node *head;
    linked_list_node *tail;
    int size;
} linked_list;

typedef struct search_result {
    bool found;
    char *data;
} search_result;

linked_list_node *create_linked_list_node(char *data);
linked_list *create_linked_list();
void free_linked_list_node(linked_list_node *node);
void free_linked_list(linked_list *list);
void prepend_node(linked_list *list, char *data);
void append_node(linked_list *list, char *data);
void insert_node(linked_list *list, char *reference, char *data);
void delete_node(linked_list *list, char *reference);
void print_list(linked_list *list);
search_result search_node(linked_list *list, char *reference);

#endif
