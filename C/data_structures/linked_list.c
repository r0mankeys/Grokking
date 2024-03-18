#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    char *data;
    struct node *next;
} node;

typedef struct linked_list {
    node *head;
    node *tail;
    size_t size;
} linked_list;

node *create_node(char *data);
linked_list *create_linked_list();
void prepend_node(linked_list *list, char *data);   
void append_node(linked_list *list, char *data);
void insert_node(linked_list *list, char *reference, char *data);
void remove_node(linked_list *list, char *reference);
void print_list(linked_list *list);  
void free_node(node *node);
void free_list(linked_list *list);

node *create_node(char *data) 
{
    // 1. Allocate memeory for the node struct and it's fields
    node *new_node = (node *)malloc(sizeof(node)); // Allocate memory for the node struct
    new_node->data = (char *)malloc(strlen(data) + 1); // +1 for the null terminator character
    new_node->next = NULL;
    // 2. Copy data into the new node
    strcpy(new_node->data, data); // Copy the data into the new node (including the null terminator character
    // 3. Return the new node
    return new_node;
}

linked_list *create_linked_list()
{
    // 1. Allocate memory for the linked_list struct and it's fields
    linked_list *list = (linked_list *)malloc(sizeof(linked_list)); // Allocate memory for the linked_list struct   
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    // 2. Return the new linked_list
    return list;
}

void free_node(node *node) 
{
    free(node->data);
    free(node);
}

void free_list(linked_list *list)
{
    node *current_node = list->head;
    while (current_node != NULL)
    {
        node *next_node = current_node->next; // Ensures we don't lose the reference to the next node
        free_node(current_node);
        current_node = next_node;
    }
    free(list);
}

void prepend_node(linked_list *list, char* data) 
{
    node *new_node = create_node(data); // needs to be created regardless of the list being empty or not
    // There are two scenarios to consider:
    // 1. The list is empty
        // If the list is empty then the head will be NULL
        // In this case we need to create a new node and set it as the head and tail of the list
    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
        list->size++;
    }
    // 2. The list is not empty
        // If so then we need to set the current head's next node to the new node
    else 
    {
        new_node->next = list->head; // Set the new node's next node to the current head
        list->head = new_node; // Update the list to reflect the new head
        list->size++;
    }
}

void append_node(linked_list *list, char *data)
{
    node *new_node = create_node(data); // needs to be created regardless of the list being empty or not
    // Again, there are two scenarios to consider:
    // 1. The list is empty
        // If the list is empty then we can simply prepend the node with the prepend_node function
    if (list->head == NULL)
    {
        prepend_node(list, data);
    }
    // 2. The list is not empty
        // If so then we need to set the current tail's next node to the new node
    else 
    {
        list->tail->next = new_node; // Set the current tail's next node to the new node
        list->tail = new_node; // Update the list to reflect the new tail
        list->size++;
    }
}

void insert_node(linked_list *list, char *reference, char *data)
{
    if (list->head == NULL) 
    {
        // Handle the case where the list is empty
         append_node(list, data);
    }

    node *new_node = create_node(data);
    node *current_node = list->head;
    // We have to traverse the list to find the correct position to insert the new node
    while (current_node != NULL)
    {
        if (strcmp(current_node->data, reference) == 0)
        {
            new_node->next = current_node->next;
            current_node->next = new_node;
            if (new_node->next == NULL) 
            {
                // If the new node is the last node in the list, update list->tail
                list->tail = new_node;
            }
            list->size++;
            return;
        }
        current_node = current_node->next;
    }
    // If we reach the end of the list and haven't found the reference node then we can assume the reference node doesn't exist and simply append the new node
    append_node(list, data);
}

void remove_node(linked_list *list, char* reference)
{
    // There are two core scenarios to consider:
    // 1. The list is empty
        // If the list is empty then ther is nothing to remove and we simply return the list
    if (list->head == NULL)
    {
        return; 
    }
    // 2. The list is not empty
    // We need to keep track of the current and previous nodes since the next node can always be accessed with the current node
    node *current_node = list->head;
    node *previous_node = NULL;
        // If this is the case we need to traverse the list until we meet the reference, and the reference can be in one of two major places:
    while (current_node != NULL)
    {
        if (strcmp(current_node->data, reference) == 0)
        {
            // Now that I have the refernce to be deleted I need to check if it's the head, tail or somewhere in the middle
            if (current_node == list->head)
            {
                list->head = current_node->next;
                free_node(current_node);
            } else if (current_node == list->tail) {
                list->tail = previous_node;
                previous_node->next = NULL;
                free_node(current_node);
            } else {
                previous_node->next = current_node->next;
                free_node(current_node);
            }
            list->size--;
            return;
        }
        previous_node = current_node;
        current_node = current_node->next;
    }
}

void print_list(linked_list *list)
{
     printf("\nLinked List\n-------------------\n");

     node *current_node = list->head;
     while (current_node != NULL)
     {
         printf("%s -> ", current_node->data);
         current_node = current_node->next;
     }
    printf("NULL\nSize: %lu\n", list->size);
    printf("-------------------\n\n");
}

int main(int argc, char **argv)
{
    linked_list *list = create_linked_list();

    append_node(list, "Hello");
    insert_node(list, "Hello", "World");
    insert_node(list, "World", "!");

    print_list(list);

    remove_node(list, "World");

    print_list(list);

    free_list(list);
    return 0;
}
