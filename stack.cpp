#include "stack.h"
#include <stdlib.h>
#include <assert.h>

struct Stack* stack_cstr(size_t capacity) {
    struct Stack* stack = (struct Stack* ) calloc(1, sizeof(*stack));
    stack->ptr_on_stack_ = (size_t* ) calloc(capacity, sizeof(*stack->ptr_on_stack_));
    stack->size_ = 0;
    stack->capacity_ = capacity;
    return stack;
}

void stack_dstr(struct Stack* stack) {
    assert(stack != nullptr);
    free(stack->ptr_on_stack_);
    free(stack);
}

void stack_resize(struct Stack** stack) {
    assert(stack != nullptr);
    struct Stack* new_stack = stack_cstr(STACK_RESIZE_COEFFICIENT * (*stack)->capacity_);
    for (size_t i = 0; i < (*stack)->capacity_; ++i) {
        new_stack->ptr_on_stack_[i] = (*stack)->ptr_on_stack_[i];
    }
    new_stack->size_ = (*stack)->size_;
    stack_dstr(*stack);
    *stack = new_stack;
}

void push(struct Stack** stack, const int val) {
    assert(stack != nullptr);
    if ((*stack)->size_ == (*stack)->capacity_)
        stack_resize(stack);
    (*stack)->size_++;
    (*stack)->ptr_on_stack_[(*stack)->size_ - 1] = val;
}

void pop(struct Stack* stack) {
    assert(stack != nullptr);
    if(stack->size_ != 0) {
        stack->ptr_on_stack_[stack->size_ - 1] = -1;
        stack->size_--;
    }
}

size_t top(struct Stack* stack) {
    assert(stack != nullptr);
    if (stack->size_ == 0)
        return 0;
    return stack->ptr_on_stack_[stack->size_ - 1];
}

void print_stack(const struct Stack* stack) {
    assert(stack != nullptr); 

    printf("\nStart print stack\n");
    for(size_t i = 0; i < stack->size_; ++i) {
        printf("%ld ", stack->ptr_on_stack_[i]);
    }
    printf("\nEnd print stack\n");
}

void print_reverse_stack(const struct Stack* stack) {
    assert(stack != nullptr); 
    for(int i = stack->size_ - 1; i >= 0; --i) {
        printf("%ld ", stack->ptr_on_stack_[i]);
    }
    printf("\n");
}