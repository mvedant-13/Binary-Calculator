#include "list.h"

typedef struct stack_node {
    number *data;
    struct stack_node *next;
} stack_node;

typedef struct stack {
    stack_node *top;
    int size;
} stack;

typedef enum {
    NUMBER,
    OPERATOR,
    PARENTHESIS
} token_type;

typedef struct token {
    token_type type;
    char *value;
} token;

typedef struct token_stack_node {
    token *data;
    struct token_stack_node *next;
} token_stack_node;

typedef struct token_stack {
    token_stack_node *top;
    int size;
} token_stack;

/* Initialization & cleanup */
stack *create_stack();
void free_stack(stack *s);

/* Basic Stack Operations */
void push(stack *s, number *data);
number *pop(stack *s);
number *peek(stack s);
int is_empty(stack s);

/* Token Stack Operations */
token_stack *create_token_stack();
void push_token(token_stack *s, token *data);
token *pop_token(token_stack *s);
token *peek_token(token_stack s);
int is_empty_token(token_stack s);