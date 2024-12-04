#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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