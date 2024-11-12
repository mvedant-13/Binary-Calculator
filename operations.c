#include "operations.h"

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

    while(str[i] != '\0') {
        append_digit(num, str[i] - '0');
        i++;
    }

    return num;
}

/* Basic Arithmetic Operations */
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

    if(cmp(a, b) == -1) {
        number *temp = a;
        a = b;
        b = temp;
        diff->sign = 1;
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
        if(d < 0 && trav_a != NULL) {
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

/* Token Operations */
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

    token **tokens = (token **)malloc(strlen(str) * sizeof(token *));
    if(tokens == NULL) {
        return NULL;
    }

    int i = 0;
    int j = 0;
    while(str[i] != '\0') {
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '(' || str[i] == ')') {
            if(str[i] == '(' && str[i + 1] == '-') {
                i = i + 2;
                int k = i;
                while(str[k] >= '0' && str[k] <= '9') {
                    k++;
                }
                char *value = (char *)malloc(k - i);
                if(value == NULL) {
                    return NULL;
                }
                value[0] = '-';
                strncpy(value + 1, str + i, k - i);
                value[k - i + 1] = '\0';
                tokens[j] = create_token(NUMBER, value);
                j++;
                i = k;
                i++;
                continue;
            }

            char *value = (char *)malloc(2);
            if(value == NULL) {
                return NULL;
            }
            value[0] = str[i];
            value[1] = '\0';

            if(str[i] == '(' || str[i] == ')') {
                tokens[j] = create_token(PARENTHESIS, value);
            }
            else {
                tokens[j] = create_token(OPERATOR, value);
            }
            j++;
            i++;
        }
        else if(str[i] >= '0' && str[i] <= '9') {
            int k = i;
            while(str[k] >= '0' && str[k] <= '9') {
                k++;
            }
            char *value = (char *)malloc(k - i - 1);
            if(value == NULL) {
                return NULL;
            }
            strncpy(value, str + i, k - i);
            value[k - i] = '\0';
            tokens[j] = create_token(NUMBER, value);
            j++;
            i = k;
        }
        else {
            i++;
        }
    }
    tokens[j] = NULL;

    return tokens;
}

void free_tokens(token **tokens) {
    if(tokens == NULL) {
        return;
    }

    int i = 0;
    while(tokens[i] != NULL) {
        free_token(tokens[i]);
        i++;
    }
    free(tokens);
}

/* Shunting Yard Algorithm */
int precedence(char *op) {
    if(strcmp(op, "+") == 0 || strcmp(op, "-") == 0) {
        return 1;
    }
    else if(strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%%") == 0) {
        return 2;
    }
    else {
        return 0;
    }
}

token **infix_to_postfix(token **infix, int size) {
    if(infix == NULL) {
        return NULL;
    }

    token **postfix = (token **)malloc(size * sizeof(token *));
    if(postfix == NULL) {
        return NULL;
    }

    stack *s = create_stack();
    if(s == NULL) {
        return NULL;
    }

    int i = 0;
    int j = 0;
    while(infix[i] != NULL) {
        if(infix[i]->type == NUMBER) {
            postfix[j] = infix[i];
            j++;
            i++;
        }
        else if(infix[i]->type == OPERATOR) {
            while(!is_empty(*s) && precedence(peek(*s)->value) >= precedence(infix[i]->value)) {
                postfix[j] = pop(s);
                j++;
            }
            push(s, infix[i]);
            i++;
        }
        else if(infix[i]->type == PARENTHESIS) {
            if(strcmp(infix[i]->value, "(") == 0) {
                push(s, infix[i]);
            }
            else {
                while(!is_empty(*s) && strcmp(peek(*s)->value, "(") != 0) {
                    postfix[j] = pop(s);
                    j++;
                }
                pop(s);
            }
            i++;
        }
    }

    while(!is_empty(*s)) {
        postfix[j] = pop(s);
        j++;
    }
    postfix[j] = NULL;

    free_stack(s);
    return postfix;
}

number *evaluate_postfix(token **postfix, int size) {
    if(postfix == NULL) {
        return NULL;
    }

    stack *s = create_stack();
    if(s == NULL) {
        return NULL;
    }

    int i = 0;
    while(postfix[i] != NULL) {
        if(postfix[i]->type == NUMBER) {
            push(s, postfix[i]);
        }
        else if(postfix[i]->type == OPERATOR) {
            number *b = str_to_number(pop(s)->value);
            number *a = str_to_number(pop(s)->value);
            number *result = NULL;
            if(strcmp(postfix[i]->value, "+") == 0) {
                result = add(a, b);
            }
            else if(strcmp(postfix[i]->value, "-") == 0) {
                result = subtract(a, b);
            }
            // else if(strcmp(postfix[i]->value, "*") == 0) {
            //     result = multiply(a, b);
            // }
            // else if(strcmp(postfix[i]->value, "/") == 0) {
            //     result = divide(a, b);
            // }
            // else if(strcmp(postfix[i]->value, "%%") == 0) {
            //     result = mod(a, b);
            // }
            push(s, create_token(NUMBER, number_to_str(result)));
            free_number(a);
            free_number(b);
            free_number(result);
        }
        i++;
    }

    number *result = str_to_number(pop(s)->value);
    free_stack(s);
    return result;
}

/* Helper Functions */
void getline(char **lineptr, size_t *n, FILE *stream) {
    if(lineptr == NULL || n == NULL) {
        return;
    }

    if(*lineptr == NULL) {
        *lineptr = (char *)malloc(100 * sizeof(char));
        if(*lineptr == NULL) {
            return;
        }
    }

    int i = 0;
    char c = fgetc(stream);
    while(c != '\n' && c != EOF) {
        if(i == *n) {
            *lineptr = (char *)realloc(*lineptr, 2 * (*n) * sizeof(char));
            if(*lineptr == NULL) {
                return;
            }
            *n *= 2;
        }
        (*lineptr)[i] = c;
        i++;
        c = fgetc(stream);
    }
    (*lineptr)[i] = '\0';

    if(c == EOF) {
        free(*lineptr);
        *lineptr = NULL;

        if(i == 0) {
            return;
        }
        *n = 0;
    }
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