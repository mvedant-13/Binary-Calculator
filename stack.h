#include "list.h"

typedef enum {
    NUMBER,
    OPERATOR,
    PARENTHESIS
} token_type;

typedef struct token {
    token_type type;
    char *value;
} token;

typedef struct stack_node {
    token *data;
    struct stack_node *next;
} stack_node;

typedef struct stack {
    stack_node *top;
    int size;
} stack;

/* Initialization & cleanup */
stack *create_stack();
void free_stack(stack *s);

/* Basic Stack Operations */
void push(stack *s, token *data);
token *pop(stack *s);
token *peek(stack s);
int is_empty(stack s);