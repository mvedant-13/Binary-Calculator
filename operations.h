#include "list.h"

/* Tokenizer */
typedef enum {
    NUMBER,
    OPERATOR,
    PARENTHESIS
} token_type;

typedef struct token {
    token_type type;
    char *value;
} token;

/* Stack */
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

/* Token Operations */
token *create_token(token_type type, char *value);
void free_token(token *t);
token **tokenize(char *str);
void free_tokens(token **tokens);

/* Basic Arithmetic Operations */
number *add(number *a, number *b);
number *subtract(number *a, number *b);
number *multiply(number *a, number *b);
number *divide(number *a, number *b);
number *mod(number *a, number *b);

/* Shunting Yard Algorithm */
int precedence(char *op);
token **infix_to_postfix(token **infix, int size);
number *evaluate_postfix(token **postfix, int size);

/* Helper Functions */
void getline(char **lineptr, size_t *n, FILE *stream);