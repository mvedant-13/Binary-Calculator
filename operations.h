#include "number.h"

/* Tokenizer */
typedef enum {
    NUMBER,
    OPERATOR,
    PARENTHESIS,
    FUNCTION,
    VARIABLE
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
int is_operator(char op);
int is_trigo(char *str);

/* Basic Arithmetic Operations */
number *add(number *a, number *b);
number *subtract(number *a, number *b);
number *multiply(number *a, number *b);
number *divide(number *a, number *b);
number *modulo(number *a, number *b);
number *power(number *a, number *b);

/* Trigonometric Operations */
number *sine(number *a);
number *cosine(number *a);
number *tangent(number *a);
number *cosecant(number *a);
number *secant(number *a);
number *cotangent(number *a);

/* Logarithmic functions */
number *logarithm(number *a);

/* Shunting Yard Algorithm */
int precedence(char *op);
token **infix_to_postfix(token **infix, int size);
number *evaluate_postfix(token **postfix, int size);