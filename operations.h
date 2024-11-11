#include "stack.h"

/* Conversions */
number *str_to_number(char *str);
char *number_to_str(number *num);

/* Basic Arithmetic Operations */
number *add(number *a, number *b);
number *subtract(number *a, number *b);
number *multiply(number *a, number *b);
number *divide(number *a, number *b);
number *mod(number *a, number *b);

/* Token Operations */
token *create_token(token_type type, char *value);
void free_token(token *t);
token **tokenize(char *str);
void free_tokens(token **tokens);

/* Shunting Yard Algorithm */
int precedence(char *op);
token **infix_to_postfix(token **infix, int size);
number *evaluate_postfix(token **postfix, int size);

/* Helper Functions */
void getline(char **lineptr, size_t *n, FILE *stream);