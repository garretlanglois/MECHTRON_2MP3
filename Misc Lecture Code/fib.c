#include <stdio.h>

int fib(int n) {

    int current = 1, previous = 0, next;

    for (int i = 1; i<=n; i++) {
        next = current + previous;
        previous = current;
        current = next;
    }

    return current;

}

int main(void) {

    int fib_to_calc = 5;

    int value = fib(fib_to_calc);

    printf("The value is of fib %d is %d", fib_to_calc, value);

}