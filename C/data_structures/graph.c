// The plan is to implement a graph in C
// I will do this by making a hash table of linked lists (adjacency list with a hash function)

// 1. Create a linked list 
// 2. Create a hash table with an array of linked lists (this will be the graph)
// 3. There is no step 3 (probably add functions to add and remove edges and vertices)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 1. Linked List 

typedef struct linked_list_node {
    char* data;
    struct linked_list_node *next;
} linked_list_node;

typedef struct linked_list {
    linked_list_node *head;
    linked_list_node *tail;
    size_t size;
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

linked_list_node *create_linked_list_node(char *data) 
{
    linked_list_node *node = (linked_list_node *)malloc(sizeof(linked_list_node));
    if (node == NULL)
    {
        return NULL; // Hanldle memory allocation failure
    }
    node->data = strdup(data); // strdup allocates memory for the new string and copies the data into it
    // easier and less error prone than writing:
    // node->data = (char *)malloc(strlen(data) + 1);
    // strcpy(node->data, data);
    node->next = NULL;
    return node;
}

linked_list *create_linked_list()
{
    linked_list *list = (linked_list *)malloc(sizeof(linked_list));
    if (list == NULL)
    {
        return NULL; // Handle memory allocation failure
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void free_linked_list_node(linked_list_node *node)
{
    free(node->data);
    free(node);
}

void free_linked_list(linked_list *list)
{
    linked_list_node *current_node = list->head;
    while (current_node != NULL)
    {
        linked_list_node *next_node = current_node->next; // Ensures we don't lose the reference to the next node
        free_linked_list_node(current_node);
        current_node = next_node;
    }
    free(list);
}

void prepend_node(linked_list *list, char *data)
{
    linked_list_node *new_node = create_linked_list_node(data);
    if (new_node == NULL)
    {
        return; // Handle memory allocation failure
    }
    new_node->next = list->head;
    list->head = new_node; 

    if (list->tail == NULL)
    {
        list->tail = new_node;
    }
    list->size++;
}

void append_node(linked_list *list, char *data)
{
    linked_list_node *new_node = create_linked_list_node(data);
    if (new_node == NULL)
    {
        return; // Handle memory allocation failure
    }
    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

void insert_node(linked_list *list, char *reference, char *data)
{
    if (list->head == NULL)
    {
        prepend_node(list, data);
    } else {
        linked_list_node *current_node = list->head;
        while (current_node != NULL)
        {
            if (strcmp(current_node->data, reference) == 0)
            {
                linked_list_node *new_node = create_linked_list_node(data);
                if (new_node == NULL)
                {
                    return; // Handle memory allocation failure
                }
                new_node->next = current_node->next;
                current_node->next = new_node;
                if (list->tail == current_node)
                {
                    list->tail = new_node;
                }
                list->size++;
                return;
            }
            current_node = current_node->next;
        }
        printf("Reference node not found\n");
    }
}

void delete_node(linked_list *list, char *reference)
{
    if (list->head == NULL)
    {
        printf("Delete Error: List is empty\n");
        return;  
    } else {
        linked_list_node *current_node = list->head;
        linked_list_node *previous_node = NULL;
        while (current_node != NULL)
        {
            if (strcmp(current_node->data, reference) == 0)
            {
                if (previous_node == NULL)
                {
                    list->head = current_node->next;
                } else {
                    previous_node->next = current_node->next;
                }
                if (list->tail == current_node)
                {
                    list->tail = previous_node;

                }
                free_linked_list_node(current_node);
                list->size--;
                return;
            }
            previous_node = current_node;
            current_node = current_node->next;
        }
    }
}

void print_list(linked_list *list)
{
     printf("\nLinked List\n-------------------\n");

     linked_list_node *current_node = list->head;
     while (current_node != NULL)
     {
         printf("%s -> ", current_node->data);
         current_node = current_node->next;
     }
    printf("NULL\nSize: %lu\n", list->size);
    printf("-------------------\n\n");
}

search_result search_node(linked_list *list, char *reference)
{
    linked_list_node *current_node = list->head;
    while (current_node != NULL)
    {
        if (strcmp(current_node->data, reference) == 0)
        {
            return (search_result){ .found = true, .data = current_node->data };
        }
        current_node = current_node->next;
    }
    return (search_result){ .found = false, .data = NULL };
}


int main(int argc, char *argv[])
{
    return 0;
}
