#include "list.h"

typedef struct stack_node {
    number *data;
    struct stack_node *next;
} stack_node;

typedef struct stack {
    stack_node *top;
} stack;

/* Initialization & cleanup */
stack *create_stack();
void free_stack(stack *s);

/* Basic Stack Operations */
void push(stack *s, number *data);
number *pop(stack *s);
number *peek(stack s);
int is_empty(stack s);