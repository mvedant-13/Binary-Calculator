#include "list.h"

number *create_number(char *str) {
    if(str == NULL) {
        return NULL;
    }

    number *num = (number *)malloc(sizeof(number));
    if(num == NULL) {
        return NULL;
    }
    num->head = NULL;
    num->tail = NULL;
    num->size = 0;
    num->sign = 0;

    int i = 0;
    if(str[i] == '-') {
        num->sign = 1;
        i++;
    }
    else if(str[i] == '+'){
        num->sign = 0;
        i++;
    }

    for(; str[i] != '\0'; i++) {
        if(str[i] < '0' || str[i] > '9') {
            free_number(num);
            return NULL;
        }
        append_digit(num, str[i] - '0');
    }

    rem_lead_zero(num);
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