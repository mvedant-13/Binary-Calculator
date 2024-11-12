#include <stdio.h>

int main() {
    int a, b;
    printf("Size of int: %llu\n", sizeof(int));
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    printf("Sum: %d\n", a + b);
    return 0;
}