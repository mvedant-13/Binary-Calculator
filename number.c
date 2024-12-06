#include "number.h"
variable *variables[TABLE_SIZE];

number *create_number() {
    number *num = (number *)malloc(sizeof(number));
    if(num == NULL) {
        return NULL;
    }
    num->head = NULL;
    num->tail = NULL;
    num->size = 0;
    num->sign = 0;
    num->scale = 0;
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
        if(num->scale == num->size - 1) {
            break;
        }        
        digit_node *temp = trav;
        trav = trav->next;
        free(temp);
        num->size--;
    }

    if(trav == NULL) {
        num->head = NULL;
        num->tail = NULL;
        num->scale = 0;
        append_digit(num, 0);
    }
    else {
        num->head = trav;
        trav->prev = NULL;
    }
}

void rem_trail_zero(number *num) {
    digit_node *trav = num->tail;
    while(trav != NULL && trav->digit == 0 && num->scale > 0) {
        digit_node *temp = trav;
        trav = trav->prev;
        free(temp);
        num->size--;
        num->scale--;
    }

    if(trav == NULL) {
        num->head = NULL;
        num->tail = NULL;
        num->scale = 0;
        append_digit(num, 0);
    }
    else {
        num->tail = trav;
        trav->next = NULL;
    }
}

void add_trail_zero(number *num, int count) {
    if(num == NULL) {
        return;
    }

    for(int i = 0; i < count; i++) {
        append_digit(num, 0);
    }

    num->scale = num->scale + count;
    num->size = num->size + count;
}

int is_zero(number *num) {
    rem_lead_zero(num);
    return num->head->digit == 0 && num->size == 1;
}

int cmp(number *a, number *b) {
    int c = 0;
    if(a == NULL || b == NULL) {
        return 0;
    }

    if(a->sign > b->sign) {
        return 1;
    }
    else if(a->sign < b->sign) {
        return -1;
    }

    if((a->size - a->scale) > (b->size - b->scale)) {
        return 1;
    }
    else if((a->size - a->scale) < (b->size - b->scale)) {
        return -1;
    }

    if(a->size > b->size) {
        add_trail_zero(b, a->size - b->size);
    }
    else if(a->size < b->size) {
        add_trail_zero(a, b->size - a->size);
    }
    digit_node *trav_a = a->head;
    digit_node *trav_b = b->head;
    while(trav_a != NULL) {
        if(trav_a->digit > trav_b->digit) {
            c = 1;
            break;
        }
        else if(trav_a->digit < trav_b->digit) {
            c = -1;
            break;
        }
        trav_a = trav_a->next;
        trav_b = trav_b->next;
    }
    rem_trail_zero(a);
    rem_trail_zero(b);
    return c;
}

/* Conversions */
char *number_to_str(number *num) {
    if(num == NULL) {
        return NULL;
    }

    rem_lead_zero(num);
    rem_trail_zero(num);

    char *str = (char *)malloc((num->size + 2) * sizeof(char));
    if(str == NULL) {
        return NULL;
    }

    int i = 0;
    if(num->sign == 1) {
        str[i] = '-';
        i++;
    }

    digit_node *trav = num->head;
    while(trav != NULL) {
        if((num->scale > 0) && (i == num->size - num->scale + num->sign)) {
            // printf("i: %d\n", i);
            // printf("num->size: %d\n", num->size);
            // printf("num->scale: %d\n", num->scale);
            str[i] = '.';
            i++;
        }
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
        if(str[i] == '.') {
            num->scale = strlen(str) - i - 1;
            i++;
            continue;
        }
        append_digit(num, str[i] - '0');
        i++;
    }

    return num;
}

int number_to_int(number *num) {
    if(num == NULL) {
        return 0;
    }

    int n = 0;
    digit_node *trav = num->head;
    while(trav != NULL) {
        n = n* 10 + trav->digit;
        trav = trav->next;
    }

    return n;
}

number *int_to_number(int n) {
    number *num = create_number();
    if(n < 0) {
        num->sign = 1;
        n = -n;
    }

    while(n > 0) {
        prepend_digit(num, n % 10);
        n = n / 10;
    }

    return num;
}

float number_to_float(number *num) {
    if(num == NULL) {
        return 0.0;
    }

    float f = 0.0;
    digit_node *trav = num->head;
    while(trav != NULL) {
        f = f * 10 + trav->digit;
        trav = trav->next;
    }

    return f / pow(10, num->scale);
}

number *float_to_number(float f) {
    number *num = create_number();
    if(f < 0) {
        num->sign = 1;
        f = -f;
    }

    int n = f;
    float d = f - n;
    while(n > 0) {
        prepend_digit(num, n % 10);
        n = n / 10;
    }

    if(num->size == 0) {
        append_digit(num, 0);
    }

    while(d > 0 && num->scale < SCALE + 1) {
        d = d * 10;
        append_digit(num, d);
        d = d - (int)d;
        num->scale++;
    }
    // printf(" Scale %d\n", num->scale);
    if(num->scale > SCALE) {
        return round_num(num);
    }
    return num;
}

number *round_num(number *num) {
    // printf("%s\n", number_to_str(num));
    if(num == NULL) {
        return NULL;
    }

    int carry;
    if(num->tail->digit >= 5)  {
        carry = 1;
    }
    else {
        carry = 0;
        return num;
    }
    // printf("SCALE %d\n", num->scale);
    // num->scale = num->scale - 1;
    // num->size = num->size - 1;
    num->tail->digit = 0;
    rem_trail_zero(num);
    // printf("scale %d\n", num->scale);
    // printf("%d\n", num->size);
    // printf("%s\n", number_to_str(num));
    digit_node *trav = num->tail;
    while(trav != num->head && carry == 1) {
        int d = trav->digit + carry;
        // printf("d: %d\n", d);
        if(d >= 10) {
            d = d % 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
        trav->digit = d;
        // printf("d: %d\n", d);
        trav = trav->prev;
    }
    return num;
}

/* Hash Table Operations */
int hash(char *name) {
    int hash = 0;
    for(int i = 0; name[i] != '\0'; i++) {
        hash = (hash + name[i]) % TABLE_SIZE;
    }
    return hash;
}

variable *create_variable(char *name, number *value) {
    variable *var = (variable *)malloc(sizeof(variable));
    if(var == NULL) {
        return NULL;
    }

    var->name = (char *)malloc(strlen(name) * sizeof(char));
    if(var->name == NULL) {
        free(var);
        return NULL;
    }

    strcpy(var->name, name);
    var->value = value;
    return var;
}

void free_variable(variable *var) {
    if(var == NULL) {
        return;
    }

    free(var->name);
    free_number(var->value);
    free(var);
}

void insert_variable(char *name, number *value) {
    int index = hash(name);
    variable *var = create_variable(name, value);
    if(var == NULL) {
        return;
    }

    variables[index] = var;
    // printf("Variable %s inserted\n", name);
}

number *lookup_variable(char *name) {
    int index = hash(name);
    variable *trav = variables[index];
    if((trav != NULL) && (strcmp(trav->name, name) == 0)) {
        return trav->value;
    }
    // printf("Variable %s not found\n", name);
    return NULL;
}

void free_variables() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        free_variable(variables[i]);
        variables[i] = NULL;
    }
}