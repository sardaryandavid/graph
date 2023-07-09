#include <gtest/gtest.h>
#include "graph.h"
#include "stack.h"

TEST(node_exist_test, handles_positive_input) {
    struct Graph* graph = create_graph(10);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    ASSERT_TRUE(node_exist(graph, 2));
    delete_graph(graph);
}

TEST(node_exist_test, handles_unreal_node) {
    struct Graph* graph = create_graph(10);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    remove_node(graph, 2);
    ASSERT_FALSE(node_exist(graph, 2));
    delete_graph(graph);
}

TEST(node_exist_test, handles_wrong_vertices_order) {
    struct Graph* graph = create_graph(10);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_node(&graph, 4);
    remove_node(graph, 2);
    ASSERT_TRUE(node_exist(graph, 4));
    delete_graph(graph);
}

TEST(edge_exist_test, handles_direct_edge) {
    struct Graph* graph = create_graph(10);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 1);
    add_edge(graph, 1, 3);

    ASSERT_TRUE(edge_exist(graph, 1, 2));
    ASSERT_TRUE(edge_exist(graph, 2, 1));
    ASSERT_TRUE(edge_exist(graph, 1, 3));
    ASSERT_FALSE(edge_exist(graph, 3, 1));
    delete_graph(graph);
}

TEST(add_node_test, handles_not_existed_node) {
    struct Graph* graph = create_graph(10);
    ASSERT_FALSE(node_exist(graph, 1)); 
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    ASSERT_TRUE(node_exist(graph, 1));
    delete_graph(graph);
}

TEST(add_node_test, handles_deleted_node) {
    struct Graph* graph = create_graph(10);
    ASSERT_FALSE(node_exist(graph, 1)); 
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    remove_node(graph, 2);
    ASSERT_FALSE(node_exist(graph, 2));
    delete_graph(graph);
}

TEST(add_node_test, handles_add_the_same_nodes) {
    struct Graph* graph = create_graph(10);
    ASSERT_FALSE(node_exist(graph, 1)); 
    add_node(&graph, 1);
    add_node(&graph, 1);
    add_node(&graph, 1);
    ASSERT_TRUE(node_exist(graph, 1));
    delete_graph(graph);
}

TEST(add_edge, handles_not_existed_node) {
    struct Graph* graph = create_graph(10);
    ASSERT_FALSE(node_exist(graph, 1)); 
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 1);
    ASSERT_TRUE(edge_exist(graph, 1, 2));
    ASSERT_TRUE(edge_exist(graph, 2, 1));
    ASSERT_TRUE(edge_exist(graph, 1, 3));
    ASSERT_FALSE(edge_exist(graph, 3, 1));
    delete_graph(graph);
}

TEST(add_edge_test, handles_add_the_same_nodes) {
    struct Graph* graph = create_graph(10);
    ASSERT_FALSE(node_exist(graph, 1)); 
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 2);
    ASSERT_TRUE(edge_exist(graph, 1, 2));
    delete_graph(graph);
}

TEST(find_position_test, handles_existed_vertice) {
    struct Graph* graph = create_graph(10);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_node(&graph, 4);
    add_node(&graph, 5);
    remove_node(graph, 3);
    ASSERT_TRUE(find_position(graph, 2) == 1);
    ASSERT_TRUE(find_position(graph, 5) == 4);
    delete_graph(graph);
}

TEST(remove_node_test, delete_existed_node) {
    struct Graph* graph = create_graph(10);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 1);
    add_edge(graph, 1, 3);
    remove_node(graph, 3);
    ASSERT_FALSE(node_exist(graph, 3));
    ASSERT_FALSE(edge_exist(graph, 1, 3));
    delete_graph(graph);      
}

TEST(remove_node_test, delete_node_with_loop_node) {
    struct Graph* graph = create_graph(10);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_node(&graph, 4);
    add_node(&graph, 5);
    add_node(&graph, 6);
    add_node(&graph, 7);
    add_node(&graph, 7);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 4);
    add_edge(graph, 4, 5);
    add_edge(graph, 5, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 3, 6);
    add_edge(graph, 6, 7);
    add_edge(graph, 4, 6);
    add_edge(graph, 7, 3);

    ASSERT_TRUE(node_exist(graph, 1));
    ASSERT_TRUE(node_exist(graph, 2));
    ASSERT_TRUE(node_exist(graph, 3));
    ASSERT_TRUE(node_exist(graph, 4));
    ASSERT_TRUE(node_exist(graph, 6));
    ASSERT_TRUE(node_exist(graph, 7));
    ASSERT_TRUE(edge_exist(graph, 1, 2));
    ASSERT_TRUE(edge_exist(graph, 2, 4));
    ASSERT_TRUE(edge_exist(graph, 1, 3));
    ASSERT_TRUE(edge_exist(graph, 3, 6));
    ASSERT_TRUE(edge_exist(graph, 6, 7));
    ASSERT_TRUE(edge_exist(graph, 4, 6));
    ASSERT_TRUE(edge_exist(graph, 7, 3));
    ASSERT_TRUE(edge_exist(graph, 5, 2));
    ASSERT_TRUE(edge_exist(graph, 4, 5));

    remove_node(graph, 5);
    ASSERT_TRUE(node_exist(graph, 1));
    ASSERT_TRUE(node_exist(graph, 2));
    ASSERT_TRUE(node_exist(graph, 3));
    ASSERT_TRUE(node_exist(graph, 4));
    ASSERT_TRUE(node_exist(graph, 6));
    ASSERT_TRUE(node_exist(graph, 7));
    ASSERT_TRUE(edge_exist(graph, 1, 2));
    ASSERT_TRUE(edge_exist(graph, 2, 4));
    ASSERT_TRUE(edge_exist(graph, 1, 3));
    ASSERT_TRUE(edge_exist(graph, 3, 6));
    ASSERT_TRUE(edge_exist(graph, 6, 7));
    ASSERT_TRUE(edge_exist(graph, 4, 6));
    ASSERT_TRUE(edge_exist(graph, 7, 3));
    ASSERT_FALSE(edge_exist(graph, 5, 2));
    ASSERT_FALSE(edge_exist(graph, 4, 5));
    print_graph(graph);
    delete_graph(graph); 
}

TEST(remove_node_test, delete_not_existed_node) {
    struct Graph* graph = create_graph(10);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 1);
    remove_node(graph, 3);
    ASSERT_FALSE(node_exist(graph, 3));
    delete_graph(graph);
}

TEST(remove_edge_test, delete_existed_edge) {
    struct Graph* graph = create_graph(10);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 1);
    add_edge(graph, 1, 3);
    remove_edge(graph, 1, 2);
    ASSERT_FALSE(edge_exist(graph, 1, 2));
    ASSERT_TRUE(edge_exist(graph, 2, 1));
    ASSERT_TRUE(edge_exist(graph, 1, 3));
    ASSERT_FALSE(edge_exist(graph, 3, 1));
    delete_graph(graph);   
}

TEST(remove_edge_test, delete_not_existed_edge) {
    struct Graph* graph = create_graph(10);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 1);
    remove_edge(graph, 1, 3);
    ASSERT_TRUE(edge_exist(graph, 1, 2));
    ASSERT_TRUE(edge_exist(graph, 2, 1));
    ASSERT_FALSE(edge_exist(graph, 1, 3));
    ASSERT_FALSE(edge_exist(graph, 3, 1));
    delete_graph(graph);   
}

TEST(resize_graph_test, resize_with_small_data_amount) {
    struct Graph* graph = create_graph(5);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 1);
    add_edge(graph, 3, 1);
    add_node(&graph, 4); 
    add_node(&graph, 5); 
    add_node(&graph, 6);
    add_node(&graph, 7);
    add_node(&graph, 8);
    add_edge(graph, 7, 8);
    add_edge(graph, 8, 6);
    add_edge(graph, 1, 6);

    ASSERT_TRUE(node_exist(graph, 1));
    ASSERT_TRUE(node_exist(graph, 2));
    ASSERT_TRUE(node_exist(graph, 3));
    ASSERT_TRUE(node_exist(graph, 4));
    ASSERT_TRUE(node_exist(graph, 5));
    ASSERT_TRUE(node_exist(graph, 6));
    ASSERT_TRUE(edge_exist(graph, 1, 2));
    ASSERT_TRUE(edge_exist(graph, 2, 1));
    ASSERT_TRUE(edge_exist(graph, 3, 1));
    ASSERT_TRUE(edge_exist(graph, 7, 8));
    ASSERT_TRUE(edge_exist(graph, 8, 6));
    ASSERT_TRUE(edge_exist(graph, 1, 6));

    delete_graph(graph); 
}

TEST(stack_push_test, handle_size_less_capacity) {
    struct Stack* stack = stack_cstr(10);
    push(&stack, 2);
    push(&stack, 3);
    push(&stack, 5);

    ASSERT_TRUE(stack->size_ == 3);
    ASSERT_TRUE(top(stack) == 5);
    pop(stack);
    ASSERT_TRUE(top(stack) == 3);
    pop(stack);
    ASSERT_TRUE(top(stack) == 2);
    stack_dstr(stack);
}

TEST(stack_push_test, handle_size_more_capacity) {
    struct Stack* stack = stack_cstr(5);
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);
    push(&stack, 50);
    push(&stack, 60);

    ASSERT_TRUE(stack->size_ == 6);
    ASSERT_TRUE(top(stack) == 60);
    pop(stack);
    ASSERT_TRUE(top(stack) == 50);
    pop(stack);
    ASSERT_TRUE(top(stack) == 40);
    pop(stack);
    ASSERT_TRUE(top(stack) == 30);
    pop(stack);
    ASSERT_TRUE(top(stack) == 20);
    pop(stack);
    ASSERT_TRUE(top(stack) == 10);
    stack_dstr(stack);
}

TEST(stack_pop_test, handle_positive_size) {
    struct Stack* stack = stack_cstr(5);
    push(&stack, 15);
    push(&stack, 24);
    push(&stack, 17);
    pop(stack);
    ASSERT_TRUE(stack->size_ == 2);
    pop(stack);
    ASSERT_TRUE(top(stack) == 15);
    ASSERT_TRUE(stack->size_ == 1); 
    stack_dstr(stack);
}

TEST(stack_pop_test, handle_zero_size) {
    struct Stack* stack = stack_cstr(5);
    push(&stack, 15);
    push(&stack, 24);
    push(&stack, 17);
    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack);
    ASSERT_TRUE(stack->size_ == 0);
    stack_dstr(stack);
}

TEST(reverse_post_order_test, handle_example_test) {
    struct Graph* graph = create_graph(5);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_node(&graph, 4);
    add_node(&graph, 5);
    add_node(&graph, 6);
    add_node(&graph, 7);
    add_node(&graph, 7);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 4);
    add_edge(graph, 4, 5);
    add_edge(graph, 5, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 3, 6);
    add_edge(graph, 6, 7);
    add_edge(graph, 4, 6);
    add_edge(graph, 7, 3);
    print_graph(graph);
    root(graph, 1);
    reverse_post_order(graph);
    delete_graph(graph);
}

TEST(reverse_post_order_test, handle_remove_loop_test) {
    struct Graph* graph = create_graph(5);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_node(&graph, 4);
    add_node(&graph, 5);
    add_node(&graph, 6);
    add_node(&graph, 7);
    add_node(&graph, 7);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 4);
    add_edge(graph, 4, 5);
    add_edge(graph, 5, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 3, 6);
    add_edge(graph, 6, 7);
    add_edge(graph, 4, 6);
    add_edge(graph, 7, 3);
    root(graph, 1);
    remove_node(graph, 5);
    reverse_post_order(graph);
    delete_graph(graph);
}

TEST(reverse_post_order_test, handle_root_from_the_middle_test) {
    struct Graph* graph = create_graph(5);
    add_node(&graph, 1);
    add_node(&graph, 2);
    add_node(&graph, 3);
    add_node(&graph, 4);
    add_node(&graph, 5);
    add_node(&graph, 6);
    add_node(&graph, 7);
    add_node(&graph, 7);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 4);
    add_edge(graph, 4, 5);
    add_edge(graph, 5, 2);
    add_edge(graph, 3, 1);
    add_edge(graph, 3, 6);
    add_edge(graph, 6, 7);
    add_edge(graph, 4, 6);
    add_edge(graph, 7, 3);
    root(graph, 4);
    reverse_post_order(graph);
    delete_graph(graph);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}