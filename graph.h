#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

const int RESIZE_COEFFICIENT = 2; 

struct Node {
    size_t vertex_;
    struct Node* next_;  
    size_t colour;
};

enum COLOUR {
    white = 0, 
    grey, 
    black
};

struct Graph {
    struct Node** lists_; 
    size_t size_;   
    size_t capacity_;
    size_t root_vertice_;
};

struct Node* create_node(const size_t vertex); 
struct Graph* create_graph(const size_t capacity);
void delete_graph(struct Graph* graph);
void delete_node(struct Node* node);
void print_node_not_exist(const struct Graph* graph, const size_t vertex);
bool node_exist(const struct Graph* graph, const size_t vertex_num);
bool edge_exist(const struct Graph* graph, const size_t vertex1, const size_t vertex2);
size_t find_position(const struct Graph* graph, const size_t vertex_num);
void add_node(struct Graph** graph, const size_t vertex_num);
void add_edge(struct Graph* graph, const size_t vertex1, const size_t vertex2);
void remove_node(struct Graph* graph, const size_t vertex_num);
void remove_edge(struct Graph* graph, const size_t vertex1, const size_t vertex2);
void root(struct Graph* graph, const size_t vertex_num);
void print_graph(const struct Graph* graph);
struct Stack* reverse_post_order(const struct Graph* graph);
void dfs_walk(const struct Graph* graph, struct Stack* stack, struct Node* node, const size_t node_pos);

#endif 