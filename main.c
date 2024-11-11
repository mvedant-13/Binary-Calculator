#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

int main() {
    number *a = str_to_number("123456789");
    number *b = str_to_number("987654321");
    number *c = add(a, b);
    number *d = subtract(a, b);
    // number *e = multiply(a, b);
    // number *f = divide(a, b);

    char *str_a = number_to_str(a);
    char *str_b = number_to_str(b);
    char *str_c = number_to_str(c);
    char *str_d = number_to_str(d);
    // char *str_e = number_to_str(e);
    // char *str_f = number_to_str(f);

    printf("a = %s\n", str_a);
    printf("b = %s\n", str_b);
    printf("a + b = %s\n", str_c);
    printf("a - b = %s\n", str_d);
    // printf("a * b = %s\n", str_e);
    // printf("a / b = %s\n", str_f);

    free(str_a);
    free(str_b);
    free(str_c);
    free(str_d);
    // free(str_e);
    // free(str_f);

    free_number(a);
    free_number(b);
    free_number(c);
    free_number(d);
    // free_number(e);
    // free_number(f);

    return 0;
}