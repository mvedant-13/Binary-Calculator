#include "list.h"

number *create_number() {
    number *num = (number *)malloc(sizeof(number));
    if(num == NULL) {
        return NULL;
    }
    num->head = NULL;
    num->tail = NULL;
    num->size = 0;
    num->sign = 0;
    return num;
}

void free_number(number *num) {
    if(num == NULL) {
        return;
    }

    digit_node *trav = num->head;
    while(trav != NULL) {
        digit_node *temp = trav;
        trav = trav->next;
        free(temp);
    }
    free(num);
}

void append_digit(number *num, int digit) {
    digit_node *nn = (digit_node *)malloc(sizeof(digit_node));
    if(nn == NULL) {
        return;
    }
    nn->digit = digit;
    nn->next = NULL;
    nn->prev = NULL;

    if(num->head == NULL) {
        num->head = nn;
        num->tail = nn;
    }
    else {
        num->tail->next = nn;
        nn->prev = num->tail;
        num->tail = nn;
    }
    num->size++;
}

void prepend_digit(number *num, int digit) {
    digit_node *nn = (digit_node *)malloc(sizeof(digit_node));
    if(nn == NULL) {
        return;
    }
    nn->digit = digit;
    nn->prev = NULL;
    nn->next = NULL;

    if(num->head == NULL) {
        num->head = nn;
        num->tail = nn;
    }
    else {
        nn->next = num->head;
        num->head->prev = nn;
        num->head = nn;
    }
    num->size++;
}

void rem_lead_zero(number *num) {
    digit_node *trav = num->head;
    while(trav != NULL && trav->digit == 0) {
        digit_node *temp = trav;
        trav = trav->next;
        free(temp);
        num->size--;
    }

    if(trav == NULL) {
        num->head = NULL;
        num->tail = NULL;
        num->size = 1;
        append_digit(num, 0);
    }
    else {
        num->head = trav;
        trav->prev = NULL;
    }
}

int is_zero(number *num) {
    digit_node *trav = num->head;
    while(trav != NULL) {
        if(trav->digit != 0) {
            return 0;
        }
        trav = trav->next;
    }
    return 1;
}

int cmp(number *a, number *b) {
    if(a == NULL || b == NULL) {
        return 0;
    }

    if(a->sign > b->sign) {
        return 1;
    }
    else if(a->sign < b->sign) {
        return -1;
    }

    if(a->size > b->size) {
        return 1;
    }
    else if(a->size < b->size) {
        return -1;
    }

    digit_node *trav_a = a->head;
    digit_node *trav_b = b->head;
    while(trav_a != NULL) {
        if(trav_a->digit > trav_b->digit) {
            return 1;
        }
        else if(trav_a->digit < trav_b->digit) {
            return -1;
        }
        trav_a = trav_a->next;
        trav_b = trav_b->next;
    }
    return 0;
}

/* Conversions */
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

number *str_to_number(char *str) {
    if(str == NULL) {
        return NULL;
    }

    number *num = create_number();

    int i = 0;
    if(str[i] == '-') {
        num->sign = 1;
        i++;
    }

    while(str[i] != '\0') {
        append_digit(num, str[i] - '0');
        i++;
    }

    return num;
}