#include "graph.h"
#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static void resize_graph(struct Graph** graph);

struct Node* create_node(const size_t vertex) {
    // sizeof(*node) - the size of type *node
    struct Node* node = (struct Node* ) calloc(1, sizeof(*node));
    assert(node);
    node->next_ = nullptr;
    node->vertex_ = vertex;
    node->colour = white;
    return node;
}

struct Graph* create_graph(const size_t capacity) {
    struct Graph* graph = (struct Graph* ) calloc(1, sizeof(*graph));
    assert(graph);
    graph->size_ = 0;
    graph->root_vertice_ = 0;
    graph->capacity_ = capacity;
    graph->lists_ = (struct Node** ) calloc(capacity, sizeof(*graph->lists_));
    assert(graph->lists_);
    return graph;
}

void delete_graph(struct Graph* graph) {
    assert(graph);
    assert(graph->lists_);

    for (size_t i = 0; i < graph->capacity_; ++i) {
        if (graph->lists_[i] != nullptr) {
            delete_node(graph->lists_[i]);
        }
    }

    free(graph->lists_);
    free(graph);
}

void delete_node(struct Node* node) {
    assert(node);

    if (node->next_ != nullptr) {
        delete_node(node->next_);
    }

    free(node);
}

bool node_exist(const struct Graph* graph, const size_t vertex_num) {
    assert(graph);
    assert(graph->lists_);

    for (size_t i = 0; i < graph->capacity_; ++i) {
        if (graph->lists_[i] != nullptr && graph->lists_[i]->vertex_ == vertex_num) {
            return true;
        }
    }

    return false;
}

bool edge_exist(const struct Graph* graph, const size_t vertex1, const size_t vertex2) {
    assert(graph);
    assert(graph->lists_);

    if (!node_exist(graph, vertex1) ||
        !node_exist(graph, vertex1)) {
        return false;
    }

    size_t vertex1_pos = find_position(graph, vertex1);
    struct Node* node = graph->lists_[vertex1_pos];
    node = node->next_;
    while (node != nullptr) {
        if (node->vertex_ == vertex2)
            return true;
        node = node->next_;
    }

    return false;
}

void add_node(struct Graph** graph, const size_t vertex_num) {
    assert(graph);
    assert((*graph)->lists_);

    if (node_exist(*graph, vertex_num)) {
        printf("Node with num %ld is already exist.\n", vertex_num); 
        return;
    }

    if ((*graph)->size_ >= (*graph)->capacity_) {
        resize_graph(graph);
    }

    (*graph)->size_++;

    struct Node* node = create_node(vertex_num);
    for (size_t i = 0; i < (*graph)->capacity_; ++i)
        if ((*graph)->lists_[i] == nullptr) {
            (*graph)->lists_[i] = node;
            break;
        }
}

static void resize_graph(struct Graph** graph) {
    assert(graph);
    assert((*graph)->lists_); 

    struct Node** new_graph_lists = (struct Node** ) calloc(RESIZE_COEFFICIENT * (*graph)->capacity_,
                                                            sizeof(struct Node*));
    assert(new_graph_lists);

    for (size_t i = 0; i < (*graph)->size_; ++i) {
        new_graph_lists[i] = (*graph)->lists_[i];
    }
    
    (*graph)->capacity_ = RESIZE_COEFFICIENT * (*graph)->capacity_;
    free((*graph)->lists_);
    (*graph)->lists_ = new_graph_lists;
}

void add_edge(struct Graph* graph, const size_t vertex1, const size_t vertex2) {
    assert(graph); 
    assert(graph->lists_);

    if (edge_exist(graph, vertex1, vertex2)) {
        printf("Edge between nodes %ld and %ld is already exist.\n", vertex1, vertex2);
        return; 
    }

    if (!node_exist(graph, vertex1)) {
        printf("Node with num %ld is not exist\n", vertex1);
        return; 
    }
    
    if (!node_exist(graph, vertex2)) {
        printf("Node with num %ld is not exist\n", vertex2);
        return;
    }
    
    struct Node* newNode = create_node(vertex2);
    size_t vertex1_pos = find_position(graph, vertex1);
    newNode->next_ = graph->lists_[vertex1_pos]->next_;
    graph->lists_[vertex1_pos]->next_ = newNode;
}

size_t find_position(const struct Graph* graph, const size_t vertex_num) {
    assert(graph);
    assert(graph->lists_);

    for (size_t i = 0; i < graph->capacity_; ++i) {
        if (graph->lists_[i] != nullptr && graph->lists_[i]->vertex_ == vertex_num) {
            return i;
        }
    }

    return graph->capacity_; // garbage
}

void remove_node(struct Graph* graph, const size_t vertex_num) {
    assert(graph);
    assert(graph->lists_);

    if (!node_exist(graph, vertex_num)) {
        printf("Node with num %ld is not exist\n", vertex_num);
        return;
    }

    size_t vertex_pos = find_position(graph, vertex_num);
    delete_node(graph->lists_[vertex_pos]);
    graph->lists_[vertex_pos] = nullptr;
    graph->size_--;

    // remove incident edges 
    // (go through all the vertices and find edges with removing node)
    for (size_t i = 0; i < graph->capacity_; ++i) {
        if (graph->lists_[i] != nullptr) {
            struct Node* tmp = graph->lists_[i]->next_;
            struct Node* tmp_prev = graph->lists_[i];
            while (tmp != nullptr) {
                if (tmp->vertex_ == vertex_num) {
                    tmp_prev->next_ = tmp->next_;
                    tmp->next_ = nullptr;
                    delete_node(tmp);
                    tmp = nullptr;
                    break;
                }

                tmp_prev = tmp;
                tmp = tmp->next_;
            }
        }
    }
}

void remove_edge(struct Graph* graph, const size_t vertex1, const size_t vertex2) {
    assert(graph); 
    assert(graph->lists_);

    if (!edge_exist(graph, vertex1, vertex2)) {
        printf("Edge between nodes 1 and 2 is not exist\n");
        return;
    }

    size_t vertex1_pos = find_position(graph, vertex1);
    struct Node* tmp = graph->lists_[vertex1_pos]->next_;
    struct Node* tmp_prev = graph->lists_[vertex1_pos];
    while (tmp->vertex_ != vertex2) {
        tmp_prev = tmp;
        tmp = tmp->next_; 
    }

    tmp_prev->next_ = tmp->next_;
    tmp->next_ = nullptr;
    delete_node(tmp);
}

void root(struct Graph* graph, const size_t vertex_num) {
    assert(graph != nullptr); 

    graph->root_vertice_ = vertex_num;
}

void print_graph(const struct Graph* graph) {
    assert(graph != nullptr);
    assert(graph->lists_);

    printf("Start print graph\n");
    for (size_t i = 0; i < graph->size_; i++) {
        bool new_line = false;
        struct Node* node = graph->lists_[i];
        if (node != nullptr) {
            printf("Incident edges to the vertex %ld: ", i + 1);
            new_line = true;
            node = node->next_; 
        }
        
        while (node != nullptr) {
            printf ("%ld ", node->vertex_);
            node = node->next_;
        }

        if (new_line) {
            printf("\n");
        }
    }
    printf("End print graph\n");
}

struct Stack* reverse_post_order(const struct Graph* graph) {
    assert(graph);
    assert(graph->lists_);

    struct Stack* stack = stack_cstr(graph->size_);
    size_t root_pos = find_position(graph, graph->root_vertice_);
    struct Node* root_node = graph->lists_[root_pos];
    dfs_walk(graph, stack, root_node, root_pos);
    print_reverse_stack(stack);
    stack_dstr(stack);
    return stack;
}

void dfs_walk(const struct Graph* graph, struct Stack* stack, struct Node* node, const size_t node_pos) {
    assert(graph);
    assert(stack);
    assert(graph->lists_);

    graph->lists_[node_pos]->colour = grey;
    struct Node* successor = node->next_;
    while (successor != nullptr) {
        size_t successor_pos = find_position(graph, successor->vertex_);
        if (graph->lists_[successor_pos]->colour == grey) {
            printf("Found loop: %ld -> %ld\n", node->vertex_, successor->vertex_);
        }
        
        if (graph->lists_[successor_pos]->colour == white) {
            dfs_walk(graph, stack, graph->lists_[successor_pos], successor_pos);
        }

        successor = successor->next_;
    }
    push(&stack, node->vertex_);
    graph->lists_[node_pos]->colour = black;
}