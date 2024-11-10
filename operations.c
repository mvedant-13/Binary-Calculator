#include "operations.h"

char *number_to_str(number *num) {
    if(num == NULL) {
        return NULL;
    }

    digit_node *trav = num->head;
    char *str = (char *)malloc(num->size + 2);
    if(str == NULL) {
        return NULL;
    }

    int i = 0;
    if(num->sign == 1) {
        str[i] = '-';
        i++;
    }

    while(trav != NULL) {
        str[i] = trav->digit + '0';
        i++;
        trav = trav->next;
    }
    str[i] = '\0';

    return str;
}

number *add(number *a, number *b) {
    
}