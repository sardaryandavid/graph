#include <stdio.h> 
#include <string.h>
#include <assert.h>
#include "graph.h"

const int MAX_LINE_SIZE = 15;
const int MAX_COMMAND_SIZE = 10;

void launch_command(struct Graph* graph, char* line);

int main()
{  
    struct Graph* graph = create_graph(10);
    char line[MAX_LINE_SIZE];

    scanf("%s", line);
    while (strcmp(line, "END") != 0) {
        launch_command(graph, line);
        scanf("%s", line);
    }

    delete_graph(graph);
}

void launch_command(struct Graph* graph, char* line) {   
    assert(line != nullptr);
    assert(graph != nullptr);

    if (strcmp(line, "ADD_NODE") == 0) {
        size_t vertex; 
        scanf("%zu", &vertex);
        add_node(&graph, vertex);
    }

    if (strcmp(line, "ADD_EDGE") == 0) {
        size_t vertex1;
        size_t vertex2;
        scanf("%zu %zu", &vertex1, &vertex2);
        add_edge(graph, vertex1, vertex2);
    }

    if (strcmp(line, "REMOVE_NODE") == 0) {
        size_t vertex; 
        scanf("%zu", &vertex);
        remove_node(graph, vertex);
    }

    if (strcmp(line, "REMOVE_EDGE") == 0) {
        size_t vertex1;
        size_t vertex2;
        scanf("%zu %zu", &vertex1, &vertex2);
        remove_edge(graph, vertex1, vertex2);
    }

    if (strcmp(line, "ROOT") == 0) {
        size_t root_vertex;
        scanf("%zu", &root_vertex);
        root(graph, root_vertex);
    }

    if (strcmp(line, "PRINT_RPO") == 0) {
        reverse_post_order(graph);
    }
}