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
} number;

/* Initialization & cleanup */
number *create_number(char *str);
void free_number(number *num);

/* Helper Functions */
void append_digit(number *num, int digit);
void prepend_digit(number *num, int digit);
void rem_lead_zero(number *num);
int is_zero(number *num);
int compare(number *a, number *b);  /* returns 1 if a > b, 0 if a == b, -1 if a < b */