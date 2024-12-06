#include "operations.h"

int main() {
    char str[100];
    number *result;
    printf("Enter an expression (or 'q' to quit):\n");
    while(1) {
        fgets(str, 100, stdin);
        str[strlen(str) - 1] = '\0';
        
        if(strcmp(str, "q") == 0) {
            break;
        }

        if(strcmp(str, "clear") == 0) {
            free_variables();
            continue;
        }
        // printf("You entered: %s\n", str);

        token **infix = tokenize(str);
        // printf("Tokens:\n");
        // int i = 0;
        // while(infix[i] != NULL) {
        //     if(infix[i]->type == NUMBER) {
        //         printf("NUMBER: %s\n", infix[i]->value);
        //     }
        //     else if(infix[i]->type == VARIABLE) {
        //         printf("VARIABLE: %s\n", infix[i]->value);
        //     }
        //     else {
        //         printf("OPERATOR: %s\n", infix[i]->value);
        //     }
        //     i++;
        // }

        token **postfix = infix_to_postfix(infix, 10);
        // printf("Postfix:\n");
        // i = 0;
        // while(postfix[i] != NULL) {
        //     if(postfix[i]->type == NUMBER) {
        //         printf("NUMBER: %s\n", postfix[i]->value);
        //     }
        //     else if(postfix[i]->type == VARIABLE) {
        //         printf("VARIABLE: %s\n", postfix[i]->value);
        //     }
        //     else {
        //         printf("OPERATOR: %s\n", postfix[i]->value);
        //     }
        //     i++;
        // }
        
        result = evaluate_postfix(postfix, 10);
        if(result != NULL) {
            printf("Result: = %s\n", number_to_str(result));
        }
    }
    return 0;
}