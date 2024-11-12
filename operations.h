#include "stack.h"

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