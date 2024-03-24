#ifndef GRAPH_H
#define GRAPH_H

#include "linked_list.h"

typedef struct graph {
    linked_list **adjacency_list;
    int size;
} graph;

int hash(char *vertex, int size);
graph *create_graph(int size);
void free_graph(graph *graph);
void add_vertex(graph *graph, char *vertex);
void add_edge(graph *graph, char *vertex1, char *vertex2);
void print_graph(graph *graph);

#endif
