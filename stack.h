#ifndef STACK_H
#define STACK_H

#include <stdio.h>
const size_t STACK_RESIZE_COEFFICIENT = 2;

struct Stack {
  size_t* ptr_on_stack_ = nullptr;

  size_t size_;
  size_t capacity_;
};

struct Stack* stack_cstr(size_t capacity);
void stack_dstr(struct Stack* stack);
void stack_resize(struct Stack** stack);
void print_stack(const struct Stack* stack);
void print_reverse_stack(const struct Stack* stack);
void push(struct Stack** stack, const int val);
void pop(struct Stack* stack);
size_t top(struct Stack* stack);


#endif