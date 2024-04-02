// The plan is to implement a graph in C
// I will do this by making a hash table of linked lists (adjacency list with a hash function)

// 1. Create a linked list 
// 2. Create a hash table with an array of linked lists (this will be the graph)
// 3. There is no step 3 (probably add functions to add and remove edges and vertices)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header_files/graph.h"

int hash(char *vertex, int size)
{
// TODO: Implement a better hash function, is not effecive for small sizes

    int hash = 0;
    for (size_t i = 0; i < strlen(vertex); i++)
    {
        hash += vertex[i];
    }
    return hash % size;
}


graph *create_graph(int size)
{
    if (size == 0)
    {
        fprintf(stderr, "Invalid size\n");
        return NULL; // Handle invalid size
    }
    
    graph *new_graph = (graph *)malloc(sizeof(graph));
    if (!new_graph)
    {
        fprintf(stderr, "Memory allocation failure for graph\n");
        return NULL;
    }
    new_graph->size = size;
    new_graph->adjacency_list = (linked_list **)calloc(size, sizeof(linked_list *)); // Allocate memory for the array of linked lists
    // and initialize all the pointers to NULL
    if (!new_graph->adjacency_list)
    {
        fprintf(stderr, "Memory allocation failure for adjacency list\n");
        free(new_graph);
        return NULL;
    }
    return new_graph;
}

void free_graph(graph *graph)
{
    for (size_t i = 0; i < graph->size; i++)
    {
        if (graph->adjacency_list[i] != NULL)
        {
            free_linked_list(graph->adjacency_list[i]);
        }
    }
    free(graph->adjacency_list);
    free(graph);
}

void add_vertex(graph *graph, char *vertex)
{
    int index = hash(vertex, graph->size);
    if (graph->adjacency_list[index] == NULL)
    {
        graph->adjacency_list[index] = create_linked_list();
    }
    append_node(graph->adjacency_list[index], vertex);
}

void add_edge(graph *graph, char *vertex1, char *vertex2)
{
    int index1 = hash(vertex1, graph->size);
    int index2 = hash(vertex2, graph->size);
    if (graph->adjacency_list[index1] == NULL || graph->adjacency_list[index2] == NULL)
    {
        fprintf(stderr, "One or both vertices do not exist\n");
        return;
    }
    append_node(graph->adjacency_list[index1], vertex2);
    append_node(graph->adjacency_list[index2], vertex1);
}

void print_graph(graph *graph)
{
    printf("\nGraph\n-----------------------------\n");
    for (size_t i = 0; i < graph->size; i++)
    {
        if (graph->adjacency_list[i] != NULL)
        {
            printf("Index: %lu\n", i);
            print_list(graph->adjacency_list[i]);
        }
    }
    printf("-----------------------------\n\n");
}
