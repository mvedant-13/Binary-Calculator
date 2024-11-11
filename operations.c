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
    if(a == NULL || b == NULL) {
        return NULL;
    }

    number *sum = (number *)malloc(sizeof(number));
    if(sum == NULL) {
        return NULL;
    }
    sum->head = NULL;
    sum->tail = NULL;
    sum->size = 0;
    sum->sign = 0;

    if(a->sign == b->sign) {
        sum->sign = a->sign;
    }
    else {
        if(a->sign == 1) {
            a->sign = 0;
            return subtract(b, a);
        }
        else {
            b->sign = 0;
            return subtract(a, b);
        }
    }

    digit_node *trav_a = a->tail;
    digit_node *trav_b = b->tail;
    int carry = 0;
    while(trav_a != NULL || trav_b != NULL) {
        int a_digit = 0;
        int b_digit = 0;
        if(trav_a != NULL) {
            a_digit = trav_a->digit;
            trav_a = trav_a->prev;
        }
        if(trav_b != NULL) {
            b_digit = trav_b->digit;
            trav_b = trav_b->prev;
        }

        int s = a_digit + b_digit + carry;
        carry = s / 10;
        prepend_digit(sum, s % 10);
    }
    if(carry != 0) {
        prepend_digit(sum, carry);
    }

    rem_lead_zero(sum);
    return sum;
}

number *subtract(number *a, number *b) {
    if(a == NULL || b == NULL) {
        return NULL;
    }

    number *diff = (number *)malloc(sizeof(number));
    if(diff == NULL) {
        return NULL;
    }
    diff->head = NULL;
    diff->tail = NULL;
    diff->size = 0;
    diff->sign = 0;

    if(a->sign == b->sign) {
        if(a->sign == 1) {
            a->sign = 0;
            b->sign = 0;
            return subtract(b, a);
        }
    }
    else {
        if(a->sign == 1) {
            b->sign = 1;
            return add(a, b);
        }
        else {
            b->sign = 0;
            return add(a, b);
        }
    }

    digit_node *trav_a = a->tail;
    digit_node *trav_b = b->tail;
    int borrow = 0;
    while(trav_a != NULL || trav_b != NULL) {
        int a_digit = 0;
        int b_digit = 0;
        if(trav_a != NULL) {
            a_digit = trav_a->digit;
            trav_a = trav_a->prev;
        }
        if(trav_b != NULL) {
            b_digit = trav_b->digit;
            trav_b = trav_b->prev;
        }

        int d = a_digit - b_digit - borrow;
        if(d < 0) {
            d += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        prepend_digit(diff, d);
    }

    if(borrow != 0) {
        diff->sign = 1;
    }

    rem_lead_zero(diff);;
    return diff;
}

token *create_token(token_type type, char *value) {
    token *t = (token *)malloc(sizeof(token));
    if(t == NULL) {
        return NULL;
    }

    t->type = type;
    t->value = value;
    return t;
}

void free_token(token *t) {
    if(t == NULL) {
        return;
    }

    free(t->value);
    free(t);
}

token **tokenize(char *str) {
    if(str == NULL) {
        return NULL;
    }

    token_stack *s = create_token_stack();
    if(s == NULL) {
        return NULL;
    }

    token **tokens = (token **)malloc(sizeof(token *));
    if(tokens == NULL) {
        return NULL;
    }

    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == ' ') {
            i++;
            continue;
        }

        if(str[i] >= '0' && str[i] <= '9') {
            int j = i;
            while(str[j] >= '0' && str[j] <= '9') {
                j++;
            }
            char *num = (char *)malloc(j - i + 1);
            if(num == NULL) {
                return NULL;
            }
            int k = 0;
            while(i < j) {
                num[k] = str[i];
                i++;
                k++;
            }
            num[k] = '\0';
            tokens = (token **)realloc(tokens, (s->size + 1) * sizeof(token *));
            tokens[s->size] = create_token(NUMBER, num);
            push_token(s, tokens[s->size]);

            free(num);
            continue;   
        }

        char *op = (char *)malloc(2);
        if(op == NULL) {
            return NULL;
        }
        op[0] = str[i];
        op[1] = '\0';
        tokens = (token **)realloc(tokens, (s->size + 1) * sizeof(token *));
        tokens[s->size] = create_token(OPERATOR, op);
        push_token(s, tokens[s->size]);

        i++;
        free(op);
    }

    free_token_stack(s);
    return tokens;
}