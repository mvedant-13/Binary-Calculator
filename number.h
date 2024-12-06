#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 26
#define SCALE 10

/* Structure to represent a number */
typedef struct digit_node {
    int digit;
    struct digit_node *next;
    struct digit_node *prev;
} digit_node;

typedef struct number {
    digit_node *head;
    digit_node *tail;
    int size;
    int sign;      /* 0 for positive & 1 for negative */
    int scale;     /* Number of digits after the decimal point */
} number;

/* Hash table to store variables */
typedef struct variable {
    char *name;
    number *value;
} variable;

extern variable *variables[TABLE_SIZE];

/* Initialization & cleanup */
number *create_number();
void free_number(number *num);

/* Helper Functions */
void append_digit(number *num, int digit);
void prepend_digit(number *num, int digit);
void rem_lead_zero(number *num);
void rem_trail_zero(number *num);
void add_trail_zero(number *num, int count);
int is_zero(number *num);
int cmp(number *a, number *b);

/* Conversions */
number *str_to_number(char *str);
char *number_to_str(number *num);
int number_to_int(number *num);
number *int_to_number(int n);

/* Hash Table Operations */
int hash(char *name);
variable *create_variable(char *name, number *value);
void free_variable(variable *var);
void insert_variable(char *name, number *value);
number *lookup_variable(char *name);
void free_variables();