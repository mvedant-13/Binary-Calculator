#include "operations.h"

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

void push(stack *s, token *data) {
    stack_node *nn = (stack_node *)malloc(sizeof(stack_node));
    if(nn == NULL) {
        return;
    }
    nn->data = data;
    nn->next = s->top;
    s->top = nn;
    s->size++;
}

token *pop(stack *s) {
    if(is_empty(*s)) {
        return NULL;
    }

    stack_node *temp = s->top;
    s->top = s->top->next;
    token *data = temp->data;
    free(temp);
    s->size--;
    return data;
}

token *peek(stack s) {
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
        if(is_operator(str[i]) || str[i] == '(' ||  str[i] == ')') {
            if(str[i] == '(' && str[i + 1] == '-') {
                i = i + 2;
                int k = i;
                while((str[k] >= '0' && str[k] <= '9') || str[k] == '.') {
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
                // printf("Operator: %s\n", value);
                tokens[j] = create_token(OPERATOR, value);
            }
            j++;
            i++;
        }
        else if(str[i] >= '0' && str[i] <= '9') {
            int k = i;
            while((str[k] >= '0' && str[k] <= '9') || str[k] == '.') {
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
        else if(str[i] >= 'a' && str[i] <= 'z') {
            if(strncmp(str + i, "pi", 2) == 0) {
                char *value = (char *)malloc(3);
                if(value == NULL) {
                    return NULL;
                }
                strncpy(value, str + i, 2);
                value[2] = '\0';
                tokens[j] = create_token(FUNCTION, value);
                j++;
                i = i + 2;
                continue;
            }
            else if(is_trigo(&str[i])) {
                char *value = (char *)malloc(4);
                if(value == NULL) {
                    return NULL;
                }
                strncpy(value, str + i, 3);
                value[3] = '\0';
                tokens[j] = create_token(FUNCTION, value);
                j++;
                i = i + 3;
                continue;
            }

            int k = i;
            while(str[k] >= 'a' && str[k] <= 'z') {
                k++;
            }
            char *value = (char *)malloc(k - i);
            if(value == NULL) {
                return NULL;
            }
            strncpy(value, str + i, k - i);
            value[k - i] = '\0';
            // printf("Variable: %s\n", value);
            tokens[j] = create_token(VARIABLE, value);
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

int is_operator(char op) {
    if(op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '=' || op == '%') {
        return 1;
    }
    return 0;
}

int is_trigo(char *str) {
    if(strncmp(str, "sin", 3) == 0 || strncmp(str, "cos", 3) == 0 || strncmp(str, "tan", 3) == 0 || strncmp(str, "csc", 3) == 0 || strncmp(str, "sec", 3) == 0 || strncmp(str, "cot", 3) == 0) {
        return 1;
    }
    return 0;
}

/* Basic Arithmetic Operations */
number *add(number *a, number *b) {
    if(a == NULL || b == NULL) {
        return NULL;
    }

    // printf("a: %s\n", number_to_str(a));
    // printf("b: %s\n", number_to_str(b));

    number *sum = create_number();

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

    if(a->scale > b->scale) {
        sum->scale = a->scale;
        add_trail_zero(b, a->scale - b->scale);
    }
    else {
        sum->scale = b->scale;
        add_trail_zero(a, b->scale - a->scale);
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
    rem_trail_zero(sum);
    rem_trail_zero(a);
    rem_trail_zero(b);
    return sum;
}

number *subtract(number *a, number *b) {
    if(a == NULL || b == NULL) {
        return NULL;
    }

    number *diff = create_number();

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
    else if(cmp(a, b) == 0) {
        append_digit(diff, 0);
        return diff;
    }

    if(a->scale > b->scale) {
        diff->scale = a->scale;
        add_trail_zero(b, a->scale - b->scale);
    }
    else {
        diff->scale = b->scale;
        add_trail_zero(a, b->scale - a->scale);
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

    rem_lead_zero(diff);
    rem_trail_zero(diff);
    rem_trail_zero(a);
    rem_trail_zero(b);

    if(is_zero(diff)) {
        diff->sign = 0;
    }
    return diff;
}

number *multiply(number *a, number *b) {
    if(a == NULL || b == NULL) {
        return NULL;
    }

    number *prod = create_number();

    digit_node *trav_a = a->tail;
    digit_node *trav_b = b->tail;
    int i = 0;
    while(trav_b != NULL) {
        number *temp = create_number();
        int carry = 0;

        while(trav_a != NULL) {
            int p = trav_a->digit * trav_b->digit + carry;
            carry = p / 10;
            prepend_digit(temp, p % 10);
            trav_a = trav_a->prev;
        }
        if(carry != 0) {
            prepend_digit(temp, carry);
        }
        for(int j = 0; j < i; j++) {
            append_digit(temp, 0);
        }
        // printf("temp: %s\n", number_to_str(temp));
        prod = add(prod, temp);
        free_number(temp);
        trav_a = a->tail;
        trav_b = trav_b->prev;
        i++;
    }

    if(a->sign == b->sign) {
        prod->sign = 0;
    }
    else {
        prod->sign = 1;
    }

    prod->scale = a->scale + b->scale;
    rem_trail_zero(prod);
    rem_lead_zero(prod);
    return prod;
}

number *divide(number *a, number *b) {
    // printf("a: %s\n", number_to_str(a));
    // printf("b: %s\n", number_to_str(b));
    if(a == NULL || b == NULL) {
        return NULL;
    }

    number *quot = create_number();

    if(is_zero(b)) {
        return NULL;
    }

    if(a->sign == b->sign) {
        quot->sign = 0;
    }
    else {
        quot->sign = 1;
    }
    a->sign = 0;
    b->sign = 0;

    number *temp_a = a;
    number *temp_b = b;
    if(a->scale > b->scale) {
        a = multiply(a, power(int_to_number(10), int_to_number(temp_a->scale)));
        b = multiply(b, power(int_to_number(10), int_to_number(temp_a->scale)));
        // printf("a: %s\n", number_to_str(a));
        // printf("b: %s\n", number_to_str(b));
    }
    else {
        a = multiply(a, power(int_to_number(10), int_to_number(temp_b->scale)));
        b = multiply(b, power(int_to_number(10), int_to_number(temp_b->scale)));
    }

    number *temp = create_number();
    digit_node *trav = a->head;
    while(trav != NULL) {
        append_digit(temp, trav->digit);
        rem_lead_zero(temp);
        int q = 0;
        while(cmp(temp, b) != -1) {
            temp = subtract(temp, b);
            // printf("temp: %s\n", number_to_str(temp));
            q++;
        }
        append_digit(quot, q);
        trav = trav->next;
    }

    while((quot->scale < SCALE) && !is_zero(temp)) {
        if(is_zero(quot)) {
            append_digit(quot, 0);
        }

        append_digit(temp, 0);
        int q = 0;
        while(cmp(temp, b) != -1) {
            temp = subtract(temp, b);
            q++;
        }
        append_digit(quot, q);
        quot->scale++;
    }

    free_number(temp);
    rem_lead_zero(quot);
    rem_trail_zero(quot);
    
    a = temp_a;
    b = temp_b;
    return quot;
}

number *modulo(number *a, number *b) {
    if(a == NULL || b == NULL) {
        return NULL;
    }

    if(is_zero(b)) {
        return NULL;
    }

    number *temp_a = a;
    number *temp_b = b;
    if(a->scale > b->scale) {
        a = multiply(a, power(int_to_number(10), int_to_number(temp_a->scale)));
        b = multiply(b, power(int_to_number(10), int_to_number(temp_a->scale)));
    }
    else {
        a = multiply(a, power(int_to_number(10), int_to_number(temp_b->scale)));
        b = multiply(b, power(int_to_number(10), int_to_number(temp_b->scale)));
    }

    number *mod = create_number();
    digit_node *trav = a->head;
    while(trav != NULL) {
        append_digit(mod, trav->digit);
        rem_lead_zero(mod);
        while(cmp(mod, b) != -1) {
            mod = subtract(mod, b);
        }
        // printf("temp: %s\n", number_to_str(mod));
        trav = trav->next;
    }
    // printf("temp: %s\n", number_to_str(mod));

    rem_lead_zero(mod);
    rem_trail_zero(mod);

    // printf("mod: %s\n", number_to_str(mod));
    a = temp_a;
    b = temp_b;
    return mod;
}

number *power(number *a, number *b) {
    if(a == NULL || b == NULL) {
        return NULL;
    }

    number *pow = create_number();
    append_digit(pow, 1);

    number *i = create_number();
    append_digit(i, 0);

    while(cmp(i, b) == -1) {
        pow = multiply(pow, a);
        i = add(i, int_to_number(1));
    }

    free_number(i);
    return pow;
}

/* Trigonometric functions */
number *sine(number *a) {
    if(a == NULL) {
        return NULL;
    }

    number *temp = modulo(a, int_to_number(360));
    float f = number_to_float(temp);
    free_number(temp);

    f = f * PI / 180;
    f = sin(f);
    // if(f < 0.0000001) {
    //     f = 0;
    // }
    // if(a->sign == 1) {
    //     f = -f;
    // }
    // printf("f: %f\n", f);
    return float_to_number(f);
}

number *cosine(number *a) {
    if(a == NULL) {
        return NULL;
    }

    number *temp = modulo(a, float_to_number(360));
    float f = number_to_float(temp);
    free_number(temp);

    f = f * PI / 180;
    f = cos(f);
    // if(f < 0.0000001) {
    //     f = 0;
    // }
    return float_to_number(f);
}

number *tangent(number *a) {
    if(a == NULL) {
        return NULL;
    }

    number *temp = modulo(a, float_to_number(360));
    float f = number_to_float(temp);
    free_number(temp);

    f = f * PI / 180;
    f = tan(f);
    // if(f < 0.0000001) {
    //     f = 0;
    // }
    return float_to_number(f);
}

number *cosecant(number *a) {
    if(a == NULL) {
        return NULL;
    }

    number *temp = sine(a);
    if(temp == NULL) {
        return NULL;
    }

    number *csc = divide(int_to_number(1), temp);
    free_number(temp);
    return csc;
}

number *secant(number *a) {
    if(a == NULL) {
        return NULL;
    }

    number *temp = cosine(a);
    if(temp == NULL) {
        return NULL;
    }

    number *sec = divide(int_to_number(1), temp);
    free_number(temp);
    return sec;
}

number *cotangent(number *a) {
    if(a == NULL) {
        return NULL;
    }

    number *temp = tangent(a);
    if(temp == NULL) {
        return NULL;
    }

    number *cot = divide(int_to_number(1), temp);
    free_number(temp);
    return cot;
}

/* Logarithmic functions */
number *logarithm(number *a) {
    if(a == NULL) {
        return NULL;
    }

    if(cmp(a, int_to_number(0)) <= 0) {
        return NULL;
    }

    number *ln = int_to_number(0);
    number *num = subtract(a, int_to_number(1));
    number *den = add(a, int_to_number(1));
    number *i = int_to_number(1);

    while(cmp(i, int_to_number(100)) == -1) {
        // printf("i: %s\n", number_to_str(i));
        number *temp = divide(num, den);
        temp = power(temp, i);
        temp = divide(temp, i);
        ln = add(ln, temp);
        // printf("ln: %s\n", number_to_str(ln));
        free_number(temp);
        i = add(i, int_to_number(2));
    }

    free_number(num);
    free_number(den);
    free_number(i);
    return multiply(ln, int_to_number(2));
}

/* Shunting Yard Algorithm */
int precedence(char *op) {
    if(strcmp(op, "+") == 0 || strcmp(op, "-") == 0) {
        return 2;
    }
    else if(strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        return 3;
    }
    else if(strcmp(op, "^") == 0) {
        return 4;
    }
    else if(strcmp(op, "=") == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

token **infix_to_postfix(token **infix, int size) {
    if(infix == NULL) {
        return NULL;
    }

    // int m = 0;
    // while(infix[m] != NULL) {
    //     printf("Token: %s\n", infix[m]->value);
    //     m++;
    // }

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
            // printf("Number push: %s\n", infix[i]->value);
            postfix[j] = infix[i];
            j++;
            i++;
        }
        else if(infix[i]->type == VARIABLE) {
            // printf("Variable push: %s\n", infix[i]->value);
            postfix[j] = infix[i];
            j++;
            i++;
        }
        else if(infix[i]->type == OPERATOR) {
            while(!is_empty(*s) && precedence(peek(*s)->value) >= precedence(infix[i]->value)) {
                postfix[j] = pop(s);
                j++;
            }
            // printf("Operator push: %s\n", infix[i]->value);
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
        else if(infix[i]->type == FUNCTION) {
            push(s, infix[i]);
            i++;
        }
    }

    while(!is_empty(*s)) {
        postfix[j] = pop(s);
        j++;
        // printf("Pop\n");
    }
    postfix[j] = NULL;

    free_stack(s);
    return postfix;
}

number *evaluate_postfix(token **postfix, int size) {
    if(postfix == NULL) {
        return NULL;
    }

    // int m = 0;
    // while(postfix[m] != NULL) {
    //     printf("Token: %s\n", postfix[m]->value);
    //     m++;
    // }

    stack *s = create_stack();
    if(s == NULL) {
        return NULL;
    }

    int i = 0;
    while(postfix[i] != NULL) {
        if(postfix[i]->type == NUMBER) {
            // printf("Number Push : %s\n", postfix[i]->value);
            push(s, postfix[i]);
        }
        else if(postfix[i]->type == VARIABLE) {
            number *value = lookup_variable(postfix[i]->value);
            // printf("Variable: %s\n", postfix[i]->value);
            if(value != NULL) {
                push(s, create_token(NUMBER, number_to_str(value)));
            }
            else {
                push(s, postfix[i]);
            }
        }
        else if(strcmp(postfix[i]->value, "=") == 0) {
            token *val = pop(s);
            token *var = pop(s);
            // printf("Variable %s set to %s\n", var->value, val->value);
            insert_variable(var->value, str_to_number(val->value));
            return NULL;
        }
        else if(postfix[i]->type == OPERATOR) {
            number *b = str_to_number(pop(s)->value);
            number *a = str_to_number(pop(s)->value);
            number *result = NULL;
            // printf("Operator: %s\n", postfix[i]->value);
            if(strcmp(postfix[i]->value, "+") == 0) {
                // printf("Addition\n");
                result = add(a, b);
            }
            else if(strcmp(postfix[i]->value, "-") == 0) {
                result = subtract(a, b);
            }
            else if(strcmp(postfix[i]->value, "*") == 0) {
                result = multiply(a, b);
            }
            else if(strcmp(postfix[i]->value, "/") == 0) {
                result = divide(a, b);
            }
            else if(strcmp(postfix[i]->value, "%") == 0) {
                // printf("Modulo\n");
                result = modulo(a, b);
            }
            else if(strcmp(postfix[i]->value, "^") == 0) {
                result = power(a, b);
            }
            push(s, create_token(NUMBER, number_to_str(result)));
            free_number(a);
            free_number(b);
            free_number(result);
        }
        else if(postfix[i]->type == FUNCTION) {
            number *a = str_to_number(pop(s)->value);
            number *result = NULL;
            if(strcmp(postfix[i]->value, "ln") == 0) {
                // printf("Logarithm\n");
                result = logarithm(a);
            }
            else if(strcmp(postfix[i]->value, "sin") == 0) {
                result = sine(a);
            }
            else if(strcmp(postfix[i]->value, "cos") == 0) {
                result = cosine(a);
            }
            else if(strcmp(postfix[i]->value, "tan") == 0) {
                result = tangent(a);
            }
            else if(strcmp(postfix[i]->value, "csc") == 0) {
                result = cosecant(a);
            }
            else if(strcmp(postfix[i]->value, "sec") == 0) {
                result = secant(a);
            }
            else if(strcmp(postfix[i]->value, "cot") == 0) {
                result = cotangent(a);
            }
            push(s, create_token(NUMBER, number_to_str(result)));
            free_number(a);
            free_number(result);
        }
        i++;
    }

    if(peek(*s)->type == VARIABLE) {
        number *value = lookup_variable(peek(*s)->value);
        if(value != NULL) {
            pop(s);
            push(s, create_token(NUMBER, number_to_str(value)));
        }
    }
    number *result = str_to_number(pop(s)->value);
    free_stack(s);
    return result;
}