#include "stack.h"
#include <stdlib.h>
#include <assert.h>

static void stack_resize(struct Stack** stack);

struct Stack* stack_cstr(size_t capacity) {
    // sizeof(*stack) - the size of type *stack 
    struct Stack* stack = (struct Stack* ) calloc(1, sizeof(*stack));
    // sizeof(*stack->ptr_on_stack_) - the size of type *(stack->ptr_on_stack_)
    stack->ptr_on_stack_ = (size_t* ) calloc(capacity, sizeof(*stack->ptr_on_stack_));
    assert(stack != nullptr);
    assert(stack->ptr_on_stack_ != nullptr);
    stack->size_ = 0;
    stack->capacity_ = capacity;
    return stack;
}

void stack_dstr(struct Stack* stack) {
    assert(stack);
    assert(stack->ptr_on_stack_);

    free(stack->ptr_on_stack_);
    free(stack);
}

static void stack_resize(struct Stack** stack) {
    assert(stack);
    assert((*stack)->ptr_on_stack_);

    size_t* new_ptr_on_stack = (size_t* ) calloc(STACK_RESIZE_COEFFICIENT * (*stack)->capacity_, sizeof((*stack)->ptr_on_stack_));
    assert(new_ptr_on_stack);
    for (size_t i = 0; i < (*stack)->capacity_; ++i) {
        new_ptr_on_stack[i] = (*stack)->ptr_on_stack_[i];
    }
    free((*stack)->ptr_on_stack_);
    (*stack)->ptr_on_stack_ = new_ptr_on_stack;
    (*stack)->capacity_ = STACK_RESIZE_COEFFICIENT * (*stack)->capacity_;
}

void push(struct Stack** stack, const int val) {
    assert(stack);
    assert((*stack)->ptr_on_stack_);  

    if ((*stack)->size_ == (*stack)->capacity_) {
        stack_resize(stack);
    }
    (*stack)->size_++;
    (*stack)->ptr_on_stack_[(*stack)->size_ - 1] = val;
}

void pop(struct Stack* stack) {
    assert(stack);
    assert(stack->ptr_on_stack_);

    if (stack->size_ != 0) {
        stack->ptr_on_stack_[stack->size_ - 1] = -1;
        stack->size_--;
    }
}

size_t top(struct Stack* stack) {
    assert(stack);
    assert(stack->ptr_on_stack_);

    if (stack->size_ == 0) {
        return 0;
    }
    return stack->ptr_on_stack_[stack->size_ - 1];
}

void print_stack(const struct Stack* stack) {
    assert(stack); 
    assert(stack->ptr_on_stack_);

    printf("\nStart print stack\n");
    for (size_t i = 0; i < stack->size_; ++i) {
        printf("%ld ", stack->ptr_on_stack_[i]);
    }
    printf("\nEnd print stack\n");
}

void print_reverse_stack(const struct Stack* stack) {
    assert(stack); 
    assert(stack->ptr_on_stack_);

    for (size_t i = 0; i < stack->size_; ++i) {
        printf("%ld ", stack->ptr_on_stack_[stack->size_ - i - 1]);
    }
    printf("\n");
}