#include "list.h"


/* Conversions */
number *str_to_number(char *str);
char *number_to_str(number *num);

/* Basic Arithmetic Operations */
number *add(number *a, number *b);
number *subtract(number *a, number *b);
number *multiply(number *a, number *b);
number *divide(number *a, number *b);