#include "stack.h"

stack *create_stack() {
    stack *s = (stack *)malloc(sizeof(stack));
    if(s == NULL) {
        return NULL;
    }
    s->top = NULL;
    s->size = 0;
    return s;
}

void free_stack(stack *s) {
    if(s == NULL) {
        return;
    }

    while(!is_empty(*s)) {
        stack_node *temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
    free(s);
}

void push(stack *s, number *data) {
    stack_node *nn = (stack_node *)malloc(sizeof(stack_node));
    if(nn == NULL) {
        return;
    }
    nn->data = data;
    nn->next = s->top;
    s->top = nn;
    s->size++;
}

number *pop(stack *s) {
    if(is_empty(*s)) {
        return NULL;
    }

    stack_node *temp = s->top;
    s->top = s->top->next;
    number *data = temp->data;
    free(temp);
    s->size--;
    return data;
}

number *peek(stack s) {
    if(is_empty(s)) {
        return NULL;
    }

    return s.top->data;
}

int is_empty(stack s) {
    if(s.top == NULL) {
        return 1;
    }
    return 0;
}

token_stack *create_token_stack() {
    token_stack *s = (token_stack *)malloc(sizeof(token_stack));
    if(s == NULL) {
        return NULL;
    }
    s->top = NULL;
    s->size = 0;
    return s;
}

void free_token_stack(token_stack *s) {
    if(s == NULL) {
        return;
    }

    while(!is_empty_token(*s)) {
        token_stack_node *temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
    free(s);
}

void push_token(token_stack *s, token *data) {
    token_stack_node *nn = (token_stack_node *)malloc(sizeof(token_stack_node));
    if(nn == NULL) {
        return;
    }
    nn->data = data;
    nn->next = s->top;
    s->top = nn;
    s->size++;
}

token *pop_token(token_stack *s) {
    if(is_empty_token(*s)) {
        return NULL;
    }

    token_stack_node *temp = s->top;
    s->top = s->top->next;
    token *data = temp->data;
    free(temp);
    s->size--;
    return data;
}

token *peek_token(token_stack s) {
    if(is_empty_token(s)) {
        return NULL;
    }

    return s.top->data;
}

int is_empty_token(token_stack s) {
    if(s.top == NULL) {
        return 1;
    }
    return 0;
}