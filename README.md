# Calculator
bc command of linux <br>
DSA mini project <br>

<b> Features: </b> <br>
<b> 1. Basic Arithmetic Operations </b> <br>
Supports the four fundamental arithmetic operations: Addition (+), Subtraction (-), Multiplication (*), and Division (/). <br>
<b> 2. Exponentiation </b> <br>
^ operator allows raising a number to the power of another, for performing exponential calculations. <br>
<b> 3. Binary Operations </b> <br> 
Bitwise Shift: << (left shift) and >> (right shift) for binary manipulations. <br>
Bitwise XOR: ^ operator performs bitwise XOR (distinct from exponentiation). <br>
<b> 4. High Precision and Unlimited Number Handling </b> <br>
Supports high-precision arithmetic to handle large integers and floating-point numbers. This feature is crucial for applications requiring exact calculations. <br>
<b> 5. Variables and Assignment </b> <br>
Users can assign values to variables (e.g., x = 5) and use these variables in expressions throughout a session. Variable values are stored and accessible for reuse. <br>
<b> 6. Mathematical Functions </b> <br>
Trigonometric Functions: Includes sine (sin), cosine (cos), and tangent (tan) functions, with results depending on the defined precision (scale). <br>
<b> 7. Configurable Precision (Scale) </b> <br>
Users can set the precision (or “scale”) for decimal results, allowing control over the number of decimal places for division and trigonometric calculations. Example: scale = 10. <br>
<b> 8. Built-in Constants </b> <br>
Pi (π): Provides a built-in constant for π, which is useful for trigonometric calculations. <br>
// printf("num->size: %d\n", num->size);
    // printf("num->scale: %d\n", num->scale);
    while(trav != NULL) {
        if(num->scale > 0 && ((i + num->sign) == (num->size - num->scale))) {
            str[i] = '.';
            i++;
        }
        str[i] = trav->digit + '0';
        i++;
        trav = trav->next;
    }
    str[i] = '\0';
    if(num == NULL) {
        return NULL;
    }

    digit_node *trav = num->head;
    char *str = (char *)malloc(num->size + 3);
    if(str == NULL) {
        return NULL;
    }

    int i = 0;
    if(num->sign == 1) {
        str[i] = '-';
        i++;
    }

    

    return str;